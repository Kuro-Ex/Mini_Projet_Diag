#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLibrary>
#include <QLibrary>
#include <QMessageBox>
#include <QComboBox>
#include <QDebug>
#include <QVariant>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromUtf8("T.E.T.O – Testeur Électronique de Tableau de bord Opérationnel"));
    this->statusBar()->showMessage("Développé par RAKOTOARIMANANA Enrique");
    this->setWindowIcon(QIcon(":/img/build/tetoIcon.png"));

    mux             = new Mux();
    can             = new CAN(mux);
    modelCan        = new QStandardItemModel(this);
    timermsg        = new QTimer(this);
    timerTrames     = new QTimer(this);
    tcpClient       = new TCPSocketClient();

    m_remoteMode    = false;

    ui->listView->setModel(modelCan);

    connect(timermsg,   &QTimer::timeout, this, &MainWindow::recevoir);
    connect(timerTrames,&QTimer::timeout, this, &MainWindow::envoyerTrameSuivante);

    // Mode par défaut : local
    m_modeConnexion = ModeConnexion::Local;
    if (ui->radioLocal)
        ui->radioLocal->setChecked(true);

    // Chargement dynamique de la bibliothèque MuxDLL
    QLibrary *lib = new QLibrary("MuxDLL");
    if (!lib->load()) {
        QMessageBox::critical(this, "Erreur", "Impossible de charger MuxDLL !");
        return;
    }


    // --- recherche des cartes ---
    tMuxStatus status = mux->rechercherCartes();
    if (status != STATUS_OK) {
        QMessageBox::warning(this, "Erreur", "Aucune carte détectée !");
        return;
    }

    qDebug() << "Nombre de cartes détectées :" << mux->dwCardsCount;

    initialiserComboCartes();

}

MainWindow::~MainWindow()
{
    // Ferme la communication proprement avant de quitter
    if (mux) {
        mux->fermerComCarte();
        delete mux;
    }
    delete ui;
}

// --- méthode pour peupler le combo box ---
void MainWindow::initialiserComboCartes()
{
    // Utilise la méthode de votre classe Mux
    QList<CarteInfo> listeCartes;
    tMuxStatus status = mux->recupererDescriptionsCartes(listeCartes);

    if (status == STATUS_OK) {
        QComboBox* combo = ui->comboBoxCartes;
        combo->clear(); // Vide le combo avant d'ajouter les éléments

        if (listeCartes.isEmpty()) {
            combo->addItem("Aucune carte disponible");
            combo->setEnabled(false);
            ui->nbCartes->setText("Nombre de cartes libres : 0");

        } else {
            combo->setEnabled(true);
            for (const auto& info : listeCartes) {
                // Le texte affiché est la description, la donnée associée est l'index
                combo->addItem(info.description, QVariant(info.index));
            }
            // Mettre à jour le label nbCarte avec le nombre de cartes trouvées
            ui->nbCartes->setText("Nombre de cartes libres : " + QString::number(listeCartes.size()));
        }
    } else {
        QMessageBox::warning(this, "Erreur",
                             QString("Impossible de récupérer la liste des cartes : Code %1").arg(status));
        // Gérer l'erreur : désactiver le combo, afficher un message, etc.
        ui->comboBoxCartes->clear();
        ui->comboBoxCartes->addItem("Erreur de récupération");
        ui->comboBoxCartes->setEnabled(false);

        // En cas d'erreur : 0 carte
        ui->nbCartes->setText("Nombre de cartes libres : 0");
    }
}

void MainWindow::on_connection_clicked()
{
    int indexCombo = ui->comboBoxCartes->currentIndex();

    mux->ouvrirComCarte();

    if (indexCombo < 0) {
        QMessageBox::warning(this, "Erreur", "Aucune carte sélectionnée !");
        return;
    }

    QVariant data = ui->comboBoxCartes->itemData(indexCombo);
    if (!data.isValid()) {
        QMessageBox::warning(this, "Erreur", "Sélection invalide.");
        return;
    }

    unsigned short indexCarte = data.toUInt();

    qDebug() << "=== Carte sélectionnée ===";
    qDebug() << "Index combo:" << indexCombo;
    qDebug() << "Index carte:" << indexCarte;
    qDebug() << "Nombre total de cartes détectées:" << mux->dwCardsCount;

    // -- Si une carte est déjà ouverte, la fermer ---
    if (mux->carteOuverte) {
        qDebug() << "Fermeture de la carte précédente...";
        mux->fermerComCarte();
    }

    // --- Mettre à jour la carte sélectionnée ---
    mux->wCard = indexCarte;

    // --- Ouvrir la nouvelle carte ---
    tMuxStatus status = mux->ouvrirComCarte();
    if (status != STATUS_OK) {
        QMessageBox::critical(this, "Erreur",QString("Impossible d'ouvrir la carte %1 (code %2)").arg(indexCarte).arg(status));
        return;
    }

    // --- Récupération de la description de la carte ---
    char descBuffer[255]{0};
    tMuxStatus descStatus = MuxGetDescription(indexCarte, descBuffer);
    QString cardName;
    if (descStatus == STATUS_OK) {
        cardName = QString::fromLocal8Bit(descBuffer);
        qDebug() << "Description:" << cardName;
    } else {
        cardName = "Carte inconnue";
        qDebug() << "Erreur récupération description:" << descStatus;
    }

    // --- Récupération du numéro de série ---
    tMuxInformations infoStruct{};
    tMuxStatus infoStatus = MuxGetInformations(indexCarte, &infoStruct);
    QString serialNumber;
    if (infoStatus == STATUS_OK) {
        serialNumber = QString::fromLatin1(infoStruct.szSerialNumber);
        qDebug() << "Numéro de série:" << serialNumber;
    } else {
        serialNumber = "N° série inconnu";
        qDebug() << "Erreur récupération infos carte:" << infoStatus;
    }

    QString infoText = QString("Carte connectée : %1\nN° de série : %2")
                           .arg(cardName)
                           .arg(serialNumber);

    ui->information->setText(infoText);


    // Affichage du mode MUX configuré (log seulement)
    qDebug() << "Mode MUX:" << mux->hMuxConfigMode.eMuxMode
             << "Interface bus:" << mux->hMuxConfigMode.wBusInterface;

    // --- Reconfigurer le CAN sur la nouvelle carte ---
    tMuxStatus stCan = can->configurerBus();
    if (stCan == STATUS_OK) {
        // Si un timer existait déjà, on peut le relancer proprement
        timermsg->start(100);   // lecture périodique toutes les 100 ms
    }
}

// --- btn pour raffraichir la detection des cartes ---
void MainWindow::on_refresh_clicked()
{
    qDebug() << "Rafraîchissement des cartes MUX...";

    // Fermer la carte si une carte était déjà ouverte
    if (mux->carteOuverte) {
        mux->fermerComCarte();
    }

    // Relancer la détection et remplir le combo box
    initialiserComboCartes();

    timerTrames->stop();
}

// --- Envoie des trames ---
void MainWindow::on_EnvoyerTrames_clicked()
{
    if (!mux || !mux->carteOuverte) {
        QMessageBox::warning(this, "CAN", "Aucune carte ouverte !");
        return;
    }

    indexTrame = 0;          // recommence à la première trame
    timerTrames->start(100);
}

void MainWindow::on_StopTrames_clicked()
{
    timerTrames->stop();
}

// --- envoie périodique des trames ---
void MainWindow::envoyerTrameSuivante()
{
    if (indexTrame >= tramesPSA.size())
        indexTrame = 0;  // boucle infinie

    unsigned long ident = tramesPSA[indexTrame];
    indexTrame++;

    if (!can) return;

    if (m_modeConnexion == ModeConnexion::Local) {
        // Envoi sur le bus CAN physique
        can->envoieMsgPeriodique(ident);
    } else {
        // Envoi au tableau de bord distant via TCP
        envoyerTrameTCP(ident);
    }
}


void MainWindow::envoyerTrameTCP(unsigned long ident)
{
    if (!tcpClient) return;

    // Assure que la connexion est établie
    if (!tcpClient->connecter()) {
        QMessageBox::warning(this, "TCP", "Connexion TCP échouée");
        // on repasse en local pour ne pas rester dans un état incohérent
        m_modeConnexion = ModeConnexion::Local;
        if (ui->radioLocal) ui->radioLocal->setChecked(true);
        return;
    }

    if (!can) return;

    can_frame frame{};
    if (!can->buildFrame(ident, frame)) {
        qDebug() << "[TCP] ID non géré pour buildFrame :"
                 << QString("0x%1").arg(ident, 0, 16);
        return;
    }

    long sent = tcpClient->writeData(&frame, sizeof(frame));
    if (sent != sizeof(frame)) {
        QMessageBox::warning(this, "TCP", "Erreur lors de l'envoi de la trame TCP");
        qDebug() << "[TCP] Erreur envoi ID"
                 << QString("0x%1").arg(ident, 0, 16)
                 << "sent =" << sent;
    } else {
        qDebug() << "[TCP] Trame envoyée ID"
                 << QString("0x%1").arg(ident, 0, 16)
                 << " (" << sent << " octets)";
    }
}

// --- reception des messages ---
void MainWindow::recevoir()
{
    if (!can || !modelCan)
        return;

    can->recevoirMsg(modelCan);

    // Auto-scroll uniquement s'il y a au moins une ligne
    int rowCount = modelCan->rowCount();
    if (rowCount <= 0)
        return;
}

// --- gestion des btn et sliders pour le tableau de bord ---
void MainWindow::on_btnVoyantsOn_clicked()
{
    if (!can || !mux || !mux->carteOuverte)
        return;

    can->setVoyantsAll(true);
}

void MainWindow::on_btnVoyantsOff_clicked()
{
    if (!can || !mux || !mux->carteOuverte)
        return;

    can->setVoyantsAll(false);
}

void MainWindow::on_sliderRegime_valueChanged(int value)
{
    if (!can) return;
    can->setRegimeMoteur(value);   // 0..8191 tr/min
    ui->labelRegime->setText(QString("Régime : %1 tr/min ").arg(value));
}

void MainWindow::on_sliderVitesse_valueChanged(int value)
{
    if (!can) return;
    can->setVitesse(value);        // 0..250 km/h
    ui->labelVitesse->setText(QString("Vitesse : %1 km/h").arg(value));
}

void MainWindow::on_sliderEssence_valueChanged(int value)
{
    if (!can) return;
    can->setJaugeEssence(value);   // 0..100 %
    ui->labelEssence->setText(QString("Essence : %1 %").arg(value));
}

void MainWindow::on_sliderTempEau_valueChanged(int value)
{
    if (!can) return;
    can->setTempEau(value);        //0..210°C
    ui->labelTempEau->setText(QString("TempEau : %1 °C").arg(value));
}

void MainWindow::on_sliderRapportBVA_valueChanged(int value)
{
    if (!can) return;
    can->setRapportBVAIndex(value); // 0..9

    QString rapportTxt;

    switch (value) {
    case 0: rapportTxt = "P";      break;
    case 1: rapportTxt = "R";      break;
    case 2: rapportTxt = "N";      break;
    case 3: rapportTxt = "D";      break;
    case 4: rapportTxt = "1ère";   break;
    case 5: rapportTxt = "2nde";   break;
    case 6: rapportTxt = "3ème";   break;
    case 7: rapportTxt = "4ème";   break;
    case 8: rapportTxt = "5ème";   break;
    case 9: rapportTxt = "6ème";   break;
    default: rapportTxt = "?";     break;
    }

    ui->labelRapportBVA->setText("Rapport : " + rapportTxt);
}

void MainWindow::on_sliderModeBVA_valueChanged(int value)
{
    if (!can) return;
    can->setModeConduiteIndex(value); // 0..4

    QString modeTxt;

    switch (value) {
    case 0: modeTxt = "Auto";                break;
    case 1: modeTxt = "Auto + Sport";        break;
    case 2: modeTxt = "Séquentiel";          break;
    case 3: modeTxt = "Séquentiel + Sport";  break;
    case 4: modeTxt = "Auto + Neige";        break;
    default: modeTxt = "?";                  break;
    }

    ui->labelModeBVA->setText("Mode : " + modeTxt);
}


void MainWindow::on_sliderLuminosite_valueChanged(int value)
{
    if (!can) return;
    can->setLuminosite(value);
}

void MainWindow::on_clignotantGauche_clicked()
{
    // on inverse l'état
    m_clignoGaucheOn = !m_clignoGaucheOn;

    // on met la bonne icône
    if (m_clignoGaucheOn) {
        ui->clignotantGauche->setIcon(QIcon(":/img/build/cliggOn.png"));
    } else {
        ui->clignotantGauche->setIcon(QIcon(":/img/build/cliggOff.png"));
    }

    // on informe la couche CAN
    if (can) {
        can->setClignoGauche(m_clignoGaucheOn);
    }
}

void MainWindow::on_clignotantDroite_clicked()
{
    // on inverse l'état
    m_clignoDroiteOn = !m_clignoDroiteOn;

    // on met la bonne icône
    if (m_clignoDroiteOn) {
        ui->clignotantDroite->setIcon(QIcon(":/img/build/cligdOn.png"));
    } else {
        ui->clignotantDroite->setIcon(QIcon(":/img/build/cligd.png"));
    }

    // on informe la couche CAN
    if (can) {
        can->setClignoDroite(m_clignoDroiteOn);
    }
}

void MainWindow::on_feuxBrouillardAr_clicked()
{
    // on inverse l'état
    m_brouilAr = !m_brouilAr;

    // on met la bonne icône
    if (m_brouilAr) {
        ui->feuxBrouillardAr->setIcon(QIcon(":/img/build/FeuxBrouillardAROn.png"));
    } else {
        ui->feuxBrouillardAr->setIcon(QIcon(":/img/build/FeuxBrouillardAROff.png"));
    }

    // on informe la couche CAN
    if (can) {
        can->setfeuxBrouilAR(m_brouilAr);
    }
}

void MainWindow::on_feuxBrouillardAv_clicked()
{
    // on inverse l'état
    m_brouilAv = !m_brouilAv;

    // on met la bonne icône
    if (m_brouilAv) {
        ui->feuxBrouillardAv->setIcon(QIcon(":/img/build/feuxBrouillardAVOn.png"));
    } else {
        ui->feuxBrouillardAv->setIcon(QIcon(":/img/build/FeuxCroisementOff.png"));
    }

    // on informe la couche CAN
    if (can) {
        can->setfeuxBrouilAV(m_brouilAv);
    }
}

void MainWindow::on_feuxCroisement_clicked()
{
    // on inverse l'état
    m_Crois = !m_Crois;

    // on met la bonne icône
    if (m_Crois) {
        ui->feuxCroisement->setIcon(QIcon(":/img/build/FeuxCroisementOn.png"));
    } else {
        ui->feuxCroisement->setIcon(QIcon(":/img/build/FeuxCroisementOff.png"));
    }

    // on informe la couche CAN
    if (can) {
        can->setfeuxCrois(m_Crois);
    }
}

void MainWindow::on_feuxDeRoute_clicked()
{
    // on inverse l'état
    m_Route = !m_Route;

    // on met la bonne icône
    if (m_Route) {
        ui->feuxDeRoute->setIcon(QIcon(":/img/build/feuxDeRouteOn.png"));
    } else {
        ui->feuxDeRoute->setIcon(QIcon(":/img/build/FeuxDeRouteOff.png"));
    }

    // on informe la couche CAN
    if (can) {
        can->setfeuxRoute(m_Route);
    }
}

void MainWindow::on_service_clicked(){

    // on inverse l'état
    m_service = !m_service;

    // on met la bonne icône
    if (m_service) {
        ui->service->setIcon(QIcon(":/img/build/warningOn.png"));
    } else {
        ui->service->setIcon(QIcon(":/img/build/warningOff.png"));
    }

    // on informe la couche CAN
    if (can) {
        can->setService(m_service);
    }
}

void MainWindow::on_Frpk_clicked()
{
    // on inverse l'état
    m_frpk = !m_frpk;

    // on met la bonne icône
    if (m_frpk) {
        ui->Frpk->setIcon(QIcon(":/img/build/frpkOn.png"));
    } else {
        ui->Frpk->setIcon(QIcon(":/img/build/frpkOff.png"));
    }

    // on informe la couche CAN
    if (can) {
        can->setFrpk(m_frpk);
    }
}

void MainWindow::on_abs_clicked()
{
    // on inverse l'état
    m_abs = !m_abs;

    // on met la bonne icône
    if (m_abs) {
        ui->abs->setIcon(QIcon(":/img/build/ABSOn.png"));
    } else {
        ui->abs->setIcon(QIcon(":/img/build/ABSOff.png"));
    }

    // on informe la couche CAN
    if (can) {
        can->setAbs(m_abs);
    }
}
void MainWindow::on_AlerteHuile_clicked()
{
    // on inverse l'état
    m_alerteHuile = !m_alerteHuile;

    // on met la bonne icône
    if (m_alerteHuile) {
        ui->AlerteHuile->setIcon(QIcon(":/img/build/AlerteHuileOn.png"));
    } else {
        ui->AlerteHuile->setIcon(QIcon(":/img/build/AlerteHuile.png"));
    }

    // on informe la couche CAN
    if (can) {
        can->setAlerteHuile(m_alerteHuile);
    }
}


void MainWindow::on_esp_clicked()
{
    // on inverse l'état
    m_esp = !m_esp;

    // on met la bonne icône
    if (m_esp) {
        ui->esp->setIcon(QIcon(":/img/build/ESPON.png"));
    } else {
        ui->esp->setIcon(QIcon(":/img/build/ESPOff.png"));
    }

    // on informe la couche CAN
    if (can) {
        can->setESPI(m_esp);
    }
}


void MainWindow::on_secPassDef_clicked()
{
    // on inverse l'état
    m_secPassDef = !m_secPassDef;

    // on met la bonne icône
    if (m_secPassDef) {
        ui->secPassDef->setIcon(QIcon(":/img/build/motDeffOn.png"));
    } else {
        ui->secPassDef->setIcon(QIcon(":/img/build/motDeffOff.png"));
    }

    // on informe la couche CAN
    if (can) {
        can->setSecPassDef(m_secPassDef);
    }
}

void MainWindow::on_AirBagArr_clicked()
{
    // on inverse l'état
    m_airBagArr = !m_airBagArr;

    // on met la bonne icône
    if (m_airBagArr) {
        ui->AirBagArr->setIcon(QIcon(":/img/build/airbagArrOn.png"));
    } else {
        ui->AirBagArr->setIcon(QIcon(":/img/build/airbagArrOff.png"));
    }

    // on informe la couche CAN
    if (can) {
        can->setAirBagArr(m_airBagArr);
    }
}

void MainWindow::on_AirBag_clicked()
{
    // on inverse l'état
    m_airBag = !m_airBag;

    // on met la bonne icône
    if (m_airBag) {
        ui->AirBag->setIcon(QIcon(":/img/build/airbagOn.png"));
    } else {
        ui->AirBag->setIcon(QIcon(":/img/build/airbagOff.png"));
    }

    // on informe la couche CAN
    if (can) {
        can->setAirBag(m_airBag);
    }
}
void MainWindow::on_stop_clicked()
{
    // on inverse l'état
    m_stop = !m_stop;

    // on met la bonne icône
    if (m_stop) {
        ui->stop->setIcon(QIcon(":/img/build/stopOn.png"));
    } else {
        ui->stop->setIcon(QIcon(":/img/build/stopOff.png"));
    }

    // on informe la couche CAN
    if (can) {
        can->setStop(m_stop);
    }
}

void MainWindow::on_radioLocal_toggled(bool checked)
{
    if (!checked) return;
    m_modeConnexion = ModeConnexion::Local;
    qDebug() << "[MODE] Passage en mode LOCAL (bus CAN)";
}

void MainWindow::on_radioTCP_toggled(bool checked)
{
    if (!checked) return;

    if (!tcpClient) {
        QMessageBox::warning(this, "TCP", "Client TCP non initialisé");
        ui->radioLocal->setChecked(true);
        return;
    }

    if (!tcpClient->connecter()) {
        QMessageBox::warning(this, "TCP", "Impossible de se connecter au tableau de bord distant.");
        ui->radioLocal->setChecked(true);
        return;
    }

    m_modeConnexion = ModeConnexion::TCP;
    qDebug() << "[MODE] Passage en mode TCP (distant)";
}
