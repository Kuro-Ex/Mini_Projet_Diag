#include "mux.h"
#include <QDebug>
#include <QString>
#include <QList>
#include <QPair>

Mux::Mux() {
    dwCardsCount = 0;
    wCard = 0;
}

tMuxStatus Mux::rechercherCartes() {
    tMuxStatus status = MuxCountCards(&dwCardsCount);
    return status;
}

tMuxStatus Mux::initDriverCarte() {
    tMuxStatus status;

    if (wCard >= dwCardsCount) {
        qDebug() << "Erreur : Numéro de carte invalide (" << wCard << "). Doit être < " << dwCardsCount;
        return STATUS_ERR_PARAM;
    }

    status = MuxInit(wCard);
    if (status != STATUS_OK) {
        qDebug() << "Erreur MuxInit pour la carte " << wCard << " : " << status;
        return status;
    }
    qDebug() << "Driver initialisé pour la carte " << wCard;
    return status;
}

// Méthode pour ouvrir la communication avec la carte
tMuxStatus Mux::ouvrirComCarte() {
    tMuxStatus status;

    // Initialisation du driver pour la carte sélectionnée
    status = initDriverCarte();
    if (status != STATUS_OK) {
        return status;
    }


    // Configuration du mode d’utilisation
    hMuxConfigMode.eMuxMode = MODE_APPLI;
    hMuxConfigMode.wBusInterface = 0;

    // Ouverture carte
    status = MuxOpen(wCard, &hMuxConfigMode);
    if (status == STATUS_OK) {
        qDebug() << "Driver MUX ouvert avec succès pour la carte " << wCard << ".";
        carteOuverte = true;
    } else {
        qDebug() << "Erreur MuxOpen pour la carte " << wCard << " : " << status;
    }
     return status;
}

tMuxStatus Mux::fermerComCarte() {
    tMuxStatus status = STATUS_OK;

    if (dwCardsCount > 0) {
        status = MuxClose(wCard);
        if (status == STATUS_OK) {
            qDebug() << "Communication avec la carte " << wCard << " fermée.";
            carteOuverte = false;
        } else {
            qDebug() << "Erreur MuxClose pour la carte " << wCard << " : " << status;
        }
    } else {
        status = STATUS_ERR_NO_DEVICE;
        qDebug() << "Aucune carte à fermer.";
    }
    return status;
}

tMuxStatus Mux::recupererDescriptionsCartes(QList<CarteInfo>& listeCartes) {

    listeCartes.clear();

    tMuxStatus status = rechercherCartes();
    if (status != STATUS_OK) {
        return status;
    }

    if (dwCardsCount == 0) {
        qDebug() << "Aucune carte disponible.";
        return STATUS_OK;
    }

    for (unsigned long i = 0; i < dwCardsCount; ++i) {

        CarteInfo info;
        info.index = static_cast<unsigned short>(i);

        // --- INITIALISATION DE LA CARTE ---
        status = MuxInit(i);
        if (status != STATUS_OK) {
            info.description = QString("Carte %1 (Erreur init %2)").arg(i).arg(status);
            listeCartes.append(info);
            continue;
        }

        // --- OUVERTURE TEMPORAIRE ---
        tMuxConfigMode cfg;
        cfg.eMuxMode = MODE_APPLI;
        cfg.wBusInterface = 0;

        status = MuxOpen(i, &cfg);

        if (status == 2) { // Erreur spécifique à ignorer
            qDebug() << "Carte" << i << "ignorée (Erreur 2)";
            continue; // Ne pas ajouter cette carte dans la liste
        }

        if (status != STATUS_OK) { // Autres erreurs
            info.description = QString("Carte %1 (Erreur open %2)").arg(i).arg(status);
            listeCartes.append(info);
            continue;
        }

        // --- NOM DE LA CARTE ---
        char descBuffer[255]{0};
        QString cardName = "Unknown";
        tMuxStatus descStatus = MuxGetDescription(i, descBuffer);

        if (descStatus == STATUS_OK) {
            cardName = QString::fromLocal8Bit(descBuffer);
        }

        // --- INFORMATION (NUMÉRO DE SÉRIE) ---
        tMuxInformations infoStruct{};
        tMuxStatus infoStatus = MuxGetInformations(i, &infoStruct);

        QString serialStr = "SN?";
        if (infoStatus == STATUS_OK) {
            serialStr = QString("SN%1").arg(infoStruct.szSerialNumber);
        }

        // --- FERMETURE DE LA CARTE ---
        MuxClose(i);

        // --- FORMAT FINAL ---
        info.description = QString("%1 (%2)").arg(cardName).arg(serialStr);

        listeCartes.append(info);
    }

    return STATUS_OK;
}



Mux::~Mux(){

}
