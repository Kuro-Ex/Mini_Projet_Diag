#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLibrary>
#include <QLibrary>
#include <QMessageBox>
#include <QComboBox> // Pour accéder au combo box
#include <QDebug>
#include <QVariant>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mux = new Mux(); //initialisation de la classe mux
    can = new CAN(mux);

    initialiserComboCartes();

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

// --- Configuration bus can ---
void MainWindow::configurerBusCAN(){

}

// --- Nouvelle méthode pour peupler le combo box ---
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
        } else {
            combo->setEnabled(true);
            for (const auto& info : listeCartes) {
                // Le texte affiché est la description, la donnée associée est l'index
                combo->addItem(info.description, QVariant(info.index));
            }
        }
    } else {
        QMessageBox::warning(this, "Erreur", QString("Impossible de récupérer la liste des cartes : Code %1").arg(status));
        // Gérer l'erreur : désactiver le combo, afficher un message, etc.
        ui->comboBoxCartes->clear();
        ui->comboBoxCartes->addItem("Erreur de récupération");
        ui->comboBoxCartes->setEnabled(false);
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

    // -- SI une carte est déjà ouverte, la fermer ---
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

    // --- Affichage des infos de la carte ---
    char descBuffer[255]{0};
    tMuxStatus descStatus = MuxGetDescription(indexCarte, descBuffer);
    if (descStatus == STATUS_OK) {
        qDebug() << "Description:" << QString::fromLocal8Bit(descBuffer);
    } else {
        qDebug() << "Erreur récupération description:" << descStatus;
    }

    // Récupération du numéro de série uniquement
    tMuxInformations infoStruct{};
    tMuxStatus infoStatus = MuxGetInformations(indexCarte, &infoStruct);
    if (infoStatus == STATUS_OK) {
        qDebug() << "Numéro de série:" << infoStruct.szSerialNumber;
    } else {
        qDebug() << "Erreur récupération infos carte:" << infoStatus;
    }

    // Affichage du mode MUX configuré
    qDebug() << "Mode MUX:" << mux->hMuxConfigMode.eMuxMode
             << "Interface bus:" << mux->hMuxConfigMode.wBusInterface;

    // --- Reconfigurer le CAN sur la nouvelle carte ---
    can->configurerBus();
}



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

