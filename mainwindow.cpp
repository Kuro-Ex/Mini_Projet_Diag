#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLibrary>
#include <QLibrary>
#include <QMessageBox>
#include <QComboBox>
#include <QDebug>
#include <QVariant>
#include <QTimer>
#include <cstring>


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
    udpClient       = new DatagramSocketClient(1500);

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

// --- boutton de connexion a la 6c6l ---
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
    if (m_modeConnexion == ModeConnexion::Local) {
        if (!mux || !mux->carteOuverte) {
            QMessageBox::warning(this, "CAN", "Aucune carte ouverte !");
            return;
        }
    } else {
        if (!tcpClient || !tcpClient->connecter()) {
            QMessageBox::warning(this, "TCP", "Connexion TCP impossible !");
            return;
        }
    }

    indexTrame = 0;
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
        indexTrame = 0;

    unsigned long ident = tramesPSA[indexTrame];
    indexTrame++;

    if (!can) return;

    if (m_modeConnexion == ModeConnexion::TCP) {
        sendIdentTCP(ident);
    } else if (m_modeConnexion == ModeConnexion::UDP) {
        sendIdentUDP(ident);
    } else {
        can->envoieMsgPeriodique(ident);
    }
}

// --- reception des messages ---
void MainWindow::recevoir()
{
    if (!can || !modelCan)
        return;

    can->recevoirMsg(modelCan);

    int rowCount = modelCan->rowCount();
    if (rowCount <= 0)
        return;
}

// --- gestion des btn et sliders pour le tableau de bord ---
void MainWindow::on_btnVoyantsOn_clicked()
{
    if (!can) return;
    can->setVoyantsAll(true);

    if (tcpClient->connecter()|| udpClient){
    sendIdent(0x168);
    sendIdent(0x128);
    }
}

void MainWindow::on_btnVoyantsOff_clicked()
{
    if (!can) return;
    can->setVoyantsAll(false);

    sendIdent(0x168);
    sendIdent(0x128);
}

void MainWindow::on_sliderRegime_valueChanged(int value)
{
    if (!can) return;
    can->setRegimeMoteur(value);
    ui->labelRegime->setText(QString("Régime : %1 tr/min ").arg(value));

    sendIdent(0x0B6);
}

void MainWindow::on_sliderVitesse_valueChanged(int value)
{
    if (!can) return;
    can->setVitesse(value);
    ui->labelVitesse->setText(QString("Vitesse : %1 km/h").arg(value));

    sendIdent(0x0B6);
}

void MainWindow::on_sliderEssence_valueChanged(int value)
{
    if (!can) return;
    can->setJaugeEssence(value);
    ui->labelEssence->setText(QString("Essence : %1 %").arg(value));

    sendIdent(0x161);
}

void MainWindow::on_sliderTempEau_valueChanged(int value)
{
    if (!can) return;
    can->setTempEau(value);
    ui->labelTempEau->setText(QString("TempEau : %1 °C").arg(value));

    sendIdent(0x0F6);
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
    sendIdent(0x128);
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
    sendIdent(0x128);
}


void MainWindow::on_sliderLuminosite_valueChanged(int value)
{
    if (!can) return;
    can->setLuminosite(value);
        ui->labelLuminosite->setText(QString("Luminosité : %1 %").arg(value));
    sendIdent(0x036);
}

void MainWindow::on_clignotantGauche_clicked()
{
    m_clignoGaucheOn = !m_clignoGaucheOn;
    ui->clignotantGauche->setIcon(QIcon(m_clignoGaucheOn ? ":/img/build/cliggOn.png"
                                                         : ":/img/build/cliggOff.png"));
    if (!can) return;
    can->setClignoGauche(m_clignoGaucheOn);
    sendIdent(0x128);
}

void MainWindow::on_clignotantDroite_clicked()
{
    m_clignoDroiteOn = !m_clignoDroiteOn;
    ui->clignotantDroite->setIcon(QIcon(m_clignoDroiteOn ? ":/img/build/cligdOn.png"
                                                         : ":/img/build/cligd.png"));
    if (!can) return;
    can->setClignoDroite(m_clignoDroiteOn);
    sendIdent(0x128);
}

void MainWindow::on_feuxBrouillardAr_clicked()
{
    m_brouilAr = !m_brouilAr;

    ui->feuxBrouillardAr->setIcon(QIcon(m_brouilAr
                                            ? ":/img/build/FeuxBrouillardAROn.png"
                                            : ":/img/build/FeuxBrouillardAROff.png"));

    if (!can) return;
    can->setfeuxBrouilAR(m_brouilAr);

    sendIdent(0x128);
}

void MainWindow::on_feuxBrouillardAv_clicked()
{
    m_brouilAv = !m_brouilAv;

    ui->feuxBrouillardAv->setIcon(QIcon(m_brouilAv
                                            ? ":/img/build/feuxBrouillardAVOn.png"
                                            : ":/img/build/FeuxCroisementOff.png"));

    if (!can) return;
    can->setfeuxBrouilAV(m_brouilAv);

    sendIdent(0x128);
}

void MainWindow::on_feuxCroisement_clicked()
{
    m_Crois = !m_Crois;

    ui->feuxCroisement->setIcon(QIcon(m_Crois
                                          ? ":/img/build/FeuxCroisementOn.png"
                                          : ":/img/build/FeuxCroisementOff.png"));

    if (!can) return;
    can->setfeuxCrois(m_Crois);

    sendIdent(0x128);
}

void MainWindow::on_feuxDeRoute_clicked()
{
    m_Route = !m_Route;

    ui->feuxDeRoute->setIcon(QIcon(m_Route
                                       ? ":/img/build/feuxDeRouteOn.png"
                                       : ":/img/build/FeuxDeRouteOff.png"));

    if (!can) return;
    can->setfeuxRoute(m_Route);

    sendIdent(0x128);
}

void MainWindow::on_service_clicked()
{
    m_service = !m_service;
    ui->service->setIcon(QIcon(m_service ? ":/img/build/warningOn.png"
                                         : ":/img/build/warningOff.png"));
    if (!can) return;
    can->setService(m_service);
    sendIdent(0x128);
}

void MainWindow::on_Frpk_clicked()
{
    m_frpk = !m_frpk;

    ui->Frpk->setIcon(QIcon(m_frpk
                                ? ":/img/build/frpkOn.png"
                                : ":/img/build/frpkOff.png"));

    if (!can) return;
    can->setFrpk(m_frpk);

    sendIdent(0x128);
}

void MainWindow::on_abs_clicked()
{
    m_abs = !m_abs;
    ui->abs->setIcon(QIcon(m_abs ? ":/img/build/ABSOn.png"
                                 : ":/img/build/ABSOff.png"));
    if (!can) return;
    can->setAbs(m_abs);
    sendIdent(0x168);
}

void MainWindow::on_AlerteHuile_clicked()
{
    m_alerteHuile = !m_alerteHuile;

    ui->AlerteHuile->setIcon(QIcon(m_alerteHuile
                                       ? ":/img/build/AlerteHuileOn.png"
                                       : ":/img/build/AlerteHuile.png"));

    if (!can) return;
    can->setAlerteHuile(m_alerteHuile);

    sendIdent(0x128);
}

void MainWindow::on_esp_clicked()
{
    m_esp = !m_esp;

    ui->esp->setIcon(QIcon(m_esp
                               ? ":/img/build/ESPON.png"
                               : ":/img/build/ESPOff.png"));

    if (!can) return;
    can->setESPI(m_esp);

    sendIdent(0x128);
}

void MainWindow::on_secPassDef_clicked()
{
    m_secPassDef = !m_secPassDef;
    ui->secPassDef->setIcon(QIcon(m_secPassDef ? ":/img/build/motDeffOn.png"
                                               : ":/img/build/motDeffOff.png"));
    if (!can) return;
    can->setSecPassDef(m_secPassDef);
    sendIdent(0x168);
}

void MainWindow::on_AirBagArr_clicked()
{
    m_airBagArr = !m_airBagArr;

    ui->AirBagArr->setIcon(QIcon(m_airBagArr
                                     ? ":/img/build/airbagArrOn.png"
                                     : ":/img/build/airbagArrOff.png"));

    if (!can) return;
    can->setAirBagArr(m_airBagArr);

    sendIdent(0x128);
}

void MainWindow::on_AirBag_clicked()
{
    m_airBag = !m_airBag;
    ui->AirBag->setIcon(QIcon(m_airBag ? ":/img/build/airbagOn.png"
                                       : ":/img/build/airbagOff.png"));
    if (!can) return;
    can->setAirBag(m_airBag);
    sendIdent(0x168);
}


void MainWindow::on_stop_clicked()
{
    m_stop = !m_stop;
    ui->stop->setIcon(QIcon(m_stop ? ":/img/build/stopOn.png"
                                   : ":/img/build/stopOff.png"));
    if (!can) return;
    can->setStop(m_stop);
    sendIdent(0x128);
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

void MainWindow::on_radioUDP_toggled(bool checked)
{
    if (!checked) return;

    if (!udpClient) {
        QMessageBox::warning(this, "UDP", "Client UDP non initialisé");
        ui->radioLocal->setChecked(true);
        return;
    }

    m_modeConnexion = ModeConnexion::UDP;
    qDebug() << "[MODE] Passage en mode UDP ";
}

bool MainWindow::sendIdentTCP(unsigned long ident)
{
    if (!tcpClient || !can) return false;

    if (!tcpClient->connecter()) {
        qDebug() << "[TCP] Connexion impossible";
        return false;
    }

    can_frame frame{};
    if (!can->buildFrame(ident, frame)) {
        qDebug() << "[TCP] ID non géré:" << Qt::hex << ident;
        return false;
    }

    long sent = tcpClient->writeData(&frame, (long)sizeof(can_frame));
    if (sent != (long)sizeof(can_frame)) {
        qDebug() << "[TCP] Envoi incomplet:" << sent;
        return false;
    }

    return true;
}

bool MainWindow::sendIdentUDP(unsigned long ident)
{
    if (!udpClient || !can) return false;

    can_frame frame{};
    if (!can->buildFrame(ident, frame)) {
        qDebug() << "[UDP] ID non géré:" << Qt::hex << ident;
        return false;
    }

    long sent = udpClient->write_datagram(&frame, (long)sizeof(can_frame), "172.16.230.208");
    if (sent != (long)sizeof(can_frame)) {
        qDebug() << "[UDP] Envoi incomplet:" << sent;
        return false;
    }

    return true;
}

void MainWindow::sendIdent(unsigned long ident)
{
    if (!can) return;

    if (m_modeConnexion == ModeConnexion::TCP) {
        sendIdentTCP(ident);
    }
    else if (m_modeConnexion == ModeConnexion::UDP) {
        sendIdentUDP(ident);
    }
    else {
        if (!mux || !mux->carteOuverte) return;
        can->envoieMsgPeriodique(ident);
    }
}

