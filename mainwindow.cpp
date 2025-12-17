#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLibrary>
#include <QLibrary>
#include <QMessageBox>

#include <QComboBox>
#include <QDebug>
#include <QVariant>
#include <QTimer>

/* =======================================================
 * CONSTRUCTEUR / DESTRUCTEUR
 * ======================================================= */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // --- UI générale ---
    ui->setupUi(this);
    this->setFixedSize(1127, 647);
    this->setWindowTitle(QString::fromUtf8("T.E.T.O – Testeur Électronique de Tableau de bord Opérationnel"));
    this->statusBar()->showMessage("Développé par RAKOTOARIMANANA Rakotondrainibe Enrique Tantely - v1.0");
    this->setWindowIcon(QIcon(":/img/build/tetoIcon.png"));

    // --- Initialisation des composants ---
    mux         = new Mux();
    can         = new CAN(mux);
    tcpClient   = new TCPSocketClient();
    udpClient   = new DatagramSocketClient(1500);
    modelCan    = new QStandardItemModel(this);
    timermsg    = new QTimer(this);
    timerTrames = new QTimer(this);

    m_remoteMode = false;

    // --- Vue CAN ---
    ui->listView->setModel(modelCan);

    // --- Timers ---
    connect(timermsg,   &QTimer::timeout, this, &MainWindow::recevoir);
    connect(timerTrames, &QTimer::timeout, this, &MainWindow::envoyerTrameSuivante);

    // --- Mode par défaut : local ---
    m_modeConnexion = ModeConnexion::Local;
    if (ui->radioLocal)
        ui->radioLocal->setChecked(true);

    // --- Chargement de la bibliothèque MuxDLL ---
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

    // --- Tableau de bord désactivé par défaut ---
    setTableauEnabled(false);
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

/* =======================================================
 * INITIALISATION DES CARTES MUX
 * ======================================================= */

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

/* =======================================================
 * CONNEXION / RAFRAICHISSEMENT CAN
 * ======================================================= */

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
        resetVoyants(); // reset des icons et des voyants avant le debut du diagnostic
        sendIdent(0x168);
        sendIdent(0x128);
        timermsg->start(100);   // lecture périodique toutes les 100 ms
    }

    if (stCan == STATUS_OK) {
        setTableauEnabled(true);
        startTrameLoop(50); // 50ms
    } else {
        setTableauEnabled(false);
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

}

/* =======================================================
 * RÉCEPTION TRAMES (TIMERS)
 * ======================================================= */

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

/* =======================================================
 * UI TABLEAU DE BORD (BOUTONS / SLIDERS)
 * ======================================================= */

void MainWindow::on_btnVoyantsOn_clicked()
{
    if (!can) return;

    // État interne IHM
    m_clignoGaucheOn = true;
    m_clignoDroiteOn = true;
    m_brouilAr       = true;
    m_brouilAv       = true;
    m_Crois          = true;
    m_Route          = true;
    m_Pos            = true;

    m_service     = true;
    m_frpk        = true;
    m_abs         = true;
    m_alerteHuile = true;
    m_esp         = true;
    m_secPassDef  = true;
    m_airBagArr   = true;
    m_airBag      = true;
    m_stop        = true;

    // Refresh icônes
    etatVoyants();

    // CAN
    can->setClignoGauche(true);
    can->setClignoDroite(true);
    can->setfeuxBrouilAR(true);
    can->setfeuxBrouilAV(true);
    can->setfeuxCrois(true);
    can->setfeuxRoute(true);
    can->setfeuxPos(true);

    can->setService(true);
    can->setFrpk(true);
    can->setAbs(true);
    can->setAlerteHuile(true);
    can->setESPI(true);
    can->setSecPassDef(true);
    can->setAirBagArr(true);
    can->setAirBag(true);
    can->setStop(true);

    // 4) Envoi trames
    sendIdent(0x168);
    sendIdent(0x128);
}

void MainWindow::on_btnVoyantsOff_clicked()
{
    if (!can) return;

    m_clignoGaucheOn = false;
    m_clignoDroiteOn = false;
    m_brouilAr       = false;
    m_brouilAv       = false;
    m_Crois          = false;
    m_Route          = false;
    m_Pos            = false;

    m_service     = false;
    m_frpk        = false;
    m_abs         = false;
    m_alerteHuile = false;
    m_esp         = false;
    m_secPassDef  = false;
    m_airBagArr   = false;
    m_airBag      = false;
    m_stop        = false;

    etatVoyants();

    can->setClignoGauche(false);
    can->setClignoDroite(false);
    can->setfeuxBrouilAR(false);
    can->setfeuxBrouilAV(false);
    can->setfeuxCrois(false);
    can->setfeuxRoute(false);
    can->setfeuxPos(false);

    can->setService(false);
    can->setFrpk(false);
    can->setAbs(false);
    can->setAlerteHuile(false);
    can->setESPI(false);
    can->setSecPassDef(false);
    can->setAirBagArr(false);
    can->setAirBag(false);
    can->setStop(false);

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
    can->setRapportBVAIndex(value);

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

    ui->labelRapportBVA->setText("Rapport BVA : " + rapportTxt);
    sendIdent(0x128);
}

void MainWindow::on_sliderModeBVA_valueChanged(int value)
{
    if (!can) return;
    can->setModeConduiteIndex(value);

    QString modeTxt;

    switch (value) {
    case 0: modeTxt = "Auto";                break;
    case 1: modeTxt = "Auto + Sport";        break;
    case 2: modeTxt = "Séquentiel";          break;
    case 3: modeTxt = "Séquentiel + Sport";  break;
    case 4: modeTxt = "Auto + Neige";        break;
    default: modeTxt = "?";                  break;
    }

    ui->labelModeBVA->setText("Mode BVA : " + modeTxt);
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

void MainWindow::on_feuxPositionnement_clicked()
{
    m_Pos = !m_Pos;
    ui->feuxPositionnement->setIcon(QIcon(m_Pos ? ":/img/build/feuxPosOn.png"
                                                : ":/img/build/feuxPosOff.png"));
    if (!can) return;
    can->setfeuxPos(m_Pos);
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

/* =======================================================
 * MODES DE CONNEXION (RADIOBUTTONS)
 * ======================================================= */

// --- passage en mode local ---
void MainWindow::on_radioLocal_toggled(bool checked)
{
    if (!checked) return;
    // activation des bouttons refresh, connection et de la combocartes
    ui->connection->setEnabled(true);
    ui->refresh->setEnabled(true);
    ui->comboBoxCartes->setEnabled(true);

    m_modeConnexion = ModeConnexion::Local;
    setTableauEnabled(isLocalReady());
    qDebug() << "[MODE] Passage en mode LOCAL (bus CAN)";
}

// --- passage en mode TCP(distant) ---
void MainWindow::on_radioTCP_toggled(bool checked)
{
    if (!checked) return;

    // desactivation des bouttons refresh, connection et de la combocartes
    ui->connection->setEnabled(false);
    ui->refresh->setEnabled(false);
    ui->comboBoxCartes->setEnabled(false);

    if (!tcpClient) {
        QMessageBox::warning(this, "TCP", "Client TCP non initialisé");
        ui->radioLocal->setChecked(true);
        return;
        setTableauEnabled(isLocalReady());
    }

    if (!tcpClient->connecter()) {
        QMessageBox::warning(this, "TCP", "Impossible de se connecter au tableau de bord distant.");
        ui->radioLocal->setChecked(true);
        return;
        setTableauEnabled(isLocalReady());
    }

    m_modeConnexion = ModeConnexion::TCP;
    setTableauEnabled(true);
    startTrameLoop(50);
    qDebug() << "[MODE] Passage en mode TCP (distant)";
}

// --- passage en mode UDP(distant) ---
void MainWindow::on_radioUDP_toggled(bool checked)
{
    if (!checked) return;

    // desactivation des bouttons refresh, connection et de la combocartes
    ui->connection->setEnabled(false);
    ui->refresh->setEnabled(false);
    ui->comboBoxCartes->setEnabled(false);

    if (!udpClient) {
        QMessageBox::warning(this, "UDP", "Client UDP non initialisé");
        ui->radioLocal->setChecked(true);
        return;
        setTableauEnabled(isLocalReady());
    }

    m_modeConnexion = ModeConnexion::UDP;
    setTableauEnabled(true);
    startTrameLoop(50);
    qDebug() << "[MODE] Passage en mode UDP ";
}

/* =======================================================
 * ENVOI TRAMES TCP / UDP + ROUTAGE
 * ======================================================= */

// --- envoie des trames en tcp ---
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

// --- envoie des trames en udp ---
bool MainWindow::sendIdentUDP(unsigned long ident)
{
    if (!udpClient || !can) return false;

    can_frame frame{};
    if (!can->buildFrame(ident, frame)) {
        qDebug() << "[UDP] ID non géré:" << Qt::hex << ident;
        return false;
    }

    long sent = udpClient->writeDatagram(&frame, (long)sizeof(can_frame), "172.16.230.208");
    if (sent != (long)sizeof(can_frame)) {
        qDebug() << "[UDP] Envoi incomplet:" << sent;
        return false;
    }

    return true;
}

// --- envoie des trames en udp ---
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

// --- envoie des trames a la suite ---
void MainWindow::envoyerTrameSuivante()
{
    if (tramesPSA.isEmpty()) return;

    // Si on est en local et que la carte n’est plus ok, on stop
    if (m_modeConnexion == ModeConnexion::Local && !isLocalReady()) {
        stopTrameLoop();
        return;
    }

    unsigned long id = tramesPSA[m_trameIndex];
    sendIdent(id);

    m_trameIndex = (m_trameIndex + 1) % tramesPSA.size();
}

// --- gestion de l'envoie des trames en continu ---
void MainWindow::startTrameLoop(int periodMs)
{
    if (!timerTrames) return;

    // Sécurité: local => carte obligatoire
    if (m_modeConnexion == ModeConnexion::Local && !isLocalReady()) {
        return;
    }

    m_trameIndex = 0;
    timerTrames->start(periodMs);

}

void MainWindow::stopTrameLoop()
{
    if (!timerTrames) return;
    timerTrames->stop();
}


/* =======================================================
 * UTILITAIRES UI
 * ======================================================= */

bool MainWindow::isLocalReady() const
{
    return (mux && mux->carteOuverte);
}

void MainWindow::setTableauEnabled(bool enabled)
{
    // Sliders
    ui->sliderRegime->setEnabled(enabled);
    ui->sliderVitesse->setEnabled(enabled);
    ui->sliderEssence->setEnabled(enabled);
    ui->sliderTempEau->setEnabled(enabled);
    ui->sliderRapportBVA->setEnabled(enabled);
    ui->sliderModeBVA->setEnabled(enabled);
    ui->sliderLuminosite->setEnabled(enabled);

    // Boutons / voyants
    ui->btnVoyantsOn->setEnabled(enabled);
    ui->btnVoyantsOff->setEnabled(enabled);

    ui->clignotantGauche->setEnabled(enabled);
    ui->clignotantDroite->setEnabled(enabled);

    ui->feuxBrouillardAr->setEnabled(enabled);
    ui->feuxBrouillardAv->setEnabled(enabled);
    ui->feuxCroisement->setEnabled(enabled);
    ui->feuxDeRoute->setEnabled(enabled);

    ui->service->setEnabled(enabled);
    ui->Frpk->setEnabled(enabled);
    ui->abs->setEnabled(enabled);
    ui->AlerteHuile->setEnabled(enabled);
    ui->esp->setEnabled(enabled);
    ui->secPassDef->setEnabled(enabled);
    ui->AirBagArr->setEnabled(enabled);
    ui->AirBag->setEnabled(enabled);
    ui->stop->setEnabled(enabled);

    startTrameLoop(50); // 50ms = fluide sans saturer (ajuste si besoin)
}

void MainWindow::etatVoyants()
{
    // Clignotants
    ui->clignotantGauche->setIcon(QIcon(m_clignoGaucheOn ? ":/img/build/cliggOn.png"
                                                         : ":/img/build/cliggOff.png"));
    ui->clignotantDroite->setIcon(QIcon(m_clignoDroiteOn ? ":/img/build/cligdOn.png"
                                                         : ":/img/build/cligd.png"));

    // Feux
    ui->feuxBrouillardAr->setIcon(QIcon(m_brouilAr ? ":/img/build/FeuxBrouillardAROn.png"
                                                   : ":/img/build/FeuxBrouillardAROff.png"));
    ui->feuxBrouillardAv->setIcon(QIcon(m_brouilAv ? ":/img/build/feuxBrouillardAVOn.png"
                                                   : ":/img/build/FeuxCroisementOff.png"));
    ui->feuxCroisement->setIcon(QIcon(m_Crois ? ":/img/build/FeuxCroisementOn.png"
                                              : ":/img/build/FeuxCroisementOff.png"));
    ui->feuxDeRoute->setIcon(QIcon(m_Route ? ":/img/build/feuxDeRouteOn.png"
                                           : ":/img/build/FeuxDeRouteOff.png"));
    ui->feuxPositionnement->setIcon(QIcon(m_Pos ? ":/img/build/feuxPosOn.png"
                                                : ":/img/build/feuxPosOff.png"));

    // Voyants “alertes”
    ui->service->setIcon(QIcon(m_service ? ":/img/build/warningOn.png"
                                         : ":/img/build/warningOff.png"));
    ui->Frpk->setIcon(QIcon(m_frpk ? ":/img/build/frpkOn.png"
                                   : ":/img/build/frpkOff.png"));
    ui->abs->setIcon(QIcon(m_abs ? ":/img/build/ABSOn.png"
                                 : ":/img/build/ABSOff.png"));
    ui->AlerteHuile->setIcon(QIcon(m_alerteHuile ? ":/img/build/AlerteHuileOn.png"
                                                 : ":/img/build/AlerteHuile.png"));
    ui->esp->setIcon(QIcon(m_esp ? ":/img/build/ESPON.png"
                                 : ":/img/build/ESPOff.png"));
    ui->secPassDef->setIcon(QIcon(m_secPassDef ? ":/img/build/motDeffOn.png"
                                               : ":/img/build/motDeffOff.png"));
    ui->AirBagArr->setIcon(QIcon(m_airBagArr ? ":/img/build/airbagArrOn.png"
                                             : ":/img/build/airbagArrOff.png"));
    ui->AirBag->setIcon(QIcon(m_airBag ? ":/img/build/airbagOn.png"
                                       : ":/img/build/airbagOff.png"));
    ui->stop->setIcon(QIcon(m_stop ? ":/img/build/stopOn.png"
                                   : ":/img/build/stopOff.png"));
}

void MainWindow::resetVoyants()
{
    // --- États IHM ---
    m_clignoGaucheOn = false;
    m_clignoDroiteOn = false;
    m_brouilAr       = false;
    m_brouilAv       = false;
    m_Crois          = false;
    m_Route          = false;
    m_Pos            = false;

    m_service     = false;
    m_frpk        = false;
    m_abs         = false;
    m_alerteHuile = false;
    m_esp         = false;
    m_secPassDef  = false;
    m_airBagArr   = false;
    m_airBag      = false;
    m_stop        = false;

    // --- CAN ---
    if (can) {
        can->setVoyantsAll(false);
        can->setClignoGauche(false);
        can->setClignoDroite(false);
        can->setfeuxBrouilAR(false);
        can->setfeuxBrouilAV(false);
        can->setfeuxCrois(false);
        can->setfeuxRoute(false);
        can->setfeuxPos(false);

        can->setService(false);
        can->setFrpk(false);
        can->setAbs(false);
        can->setAlerteHuile(false);
        can->setESPI(false);
        can->setSecPassDef(false);
        can->setAirBagArr(false);
        can->setAirBag(false);
        can->setStop(false);
    }

    // --- Mise à jour visuelle ---
    etatVoyants();
}

