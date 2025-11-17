#ifndef MUX_H
#define MUX_H

#include "refmux.h" // Inclure le header fourni
#include <QString>
#include <QList>
#include <QPair>

// Structure pour stocker les informations d'une carte
struct CarteInfo {
    unsigned short index;
    QString description;

};

class Mux {
public:
    Mux();
    ~Mux();

    tMuxStatus rechercherCartes();
    tMuxStatus initDriverCarte();
    tMuxStatus ouvrirComCarte();
    tMuxStatus fermerComCarte();

    // Nouvelle méthode pour récupérer les descriptions
    tMuxStatus recupererDescriptionsCartes(QList<CarteInfo>& listeCartes);
    unsigned long getNombreCartes() const { return dwCardsCount; }

    unsigned short wCard;
    unsigned long dwCardsCount;
    tMuxConfigMode hMuxConfigMode;

    bool carteOuverte = false;

private:

};

#endif // MUX_H
