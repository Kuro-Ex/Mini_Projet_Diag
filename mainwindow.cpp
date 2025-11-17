#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLibrary>
#include <QLibrary>
#include <QMessageBox>
#include <QComboBox> // Pour accéder au combo box
#include <QDebug>
#include <QVariant>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mux = new Mux(); //initialisation de la classe mux
    can = new CAN(mux);

    modelCan = new QStandardItemModel(this);
    ui->listView->setModel(modelCan);

    timermsg = new QTimer(this);
    connect(timermsg, &QTimer::timeout,
            this, &MainWindow::recevoir);

    initialiserComboCartes();
    initialiserComboTrames();

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
    mux->ouvrirComCarte();

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
            ui->nbCartes->setText("Nombre de cartes libres : "+QString::number(listeCartes.size()));
        }
    } else {
        QMessageBox::warning(this, "Erreur", QString("Impossible de récupérer la liste des cartes : Code %1").arg(status));
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
        QMessageBox::critical(this, "Erreur", QString("Impossible d'ouvrir la carte %1 (code %2)").arg(indexCarte).arg(status));
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

    // --- Affichage dans le label "information" ---
    ui->information->setText(
        QString("Carte connectée : %1\nN° de série : %2")
            .arg(cardName, serialNumber)
        );

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
}

// --- Insertion des trames dans le combobox ---
void MainWindow::initialiserComboTrames()
{
    ui->comboBoxTrames->clear();

    ui->comboBoxTrames->addItem("0x0F6 ", QVariant(0x0F6));
    ui->comboBoxTrames->addItem("0x036 ", QVariant(0x036));
    ui->comboBoxTrames->addItem("0x168 ", QVariant(0x168));
    ui->comboBoxTrames->addItem("0x128 ", QVariant(0x128));
    ui->comboBoxTrames->addItem("0x0B6 ", QVariant(0x0B6));
    ui->comboBoxTrames->addItem("0x161 ", QVariant(0x161));

    ui->comboBoxTrames->setCurrentIndex(0);
}

// --- Envoie des trames ---
void MainWindow::on_EnvoyerTrames_clicked()
{
    int index = ui->comboBoxTrames->currentIndex();

    if (index < 0) {
        QMessageBox::warning(this, "CAN", "Aucune trame sélectionnée.");
        return;
    }

    QVariant data = ui->comboBoxTrames->itemData(index);

    if (!data.isValid()) {
        QMessageBox::warning(this, "CAN", "Index invalide dans comboBoxTrames.");
        return;
    }

    unsigned long ident = data.toUInt();

    tMuxStatus status = can->envoieMsgPeriodique(ident);

    if (status == STATUS_OK) {
        ui->informationTrames->setText(
            QString("Trame 0x%1 envoyée !")
                .arg(ident, 0, 16).toUpper()
            );
    } else {
        ui->informationTrames->setText(
            QString("Erreur envoi trame 0x%1").arg(ident, 0, 16).toUpper()
            );
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

    QModelIndex lastIndex = modelCan->index(rowCount - 1, 0);
    if (lastIndex.isValid()) {
        ui->listView->scrollTo(lastIndex);
    }
}
