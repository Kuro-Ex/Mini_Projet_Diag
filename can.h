#ifndef CAN_H
#define CAN_H

#include "mux.h"
#include "refmux.h"
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QStandardItemModel>
#include <QtGlobal>   // pour quint8


class CAN
{
public:
    CAN(Mux *m);
    tMuxStatus configurerBus();
    tMuxStatus envoieMsgPeriodique(unsigned long ident);
    void recevoirMsg();
    void recevoirMsg(QStandardItemModel *model);

    // ---------- SIMULATION : SETTERS ----------
    // Voyants du combiné
    void setVoyantsAll(bool on);

    // Micromoteurs
    void setRegimeMoteur(int trmin);     // compte-tour
    void setVitesse(int kmh);            // compteur
    void setJaugeEssence(int pourcent);  // 0..100%
    void setTempEau(int degC);           // °C

    // BVA + modes
    void setRapportBVAIndex(int idx);    // slider états P/R/N/D/2/1
    void setModeConduiteIndex(int idx);  // slider états Normal/Sport/Hiver

private:
         // ---------- ETAT COURANT ----------
    bool voyantsOn = false;

    int regimeMoteur = 0;   // tr/min
    int vitesse = 0;        // km/h
    int jaugeEssence = 0;   // %
    int tempEau = 20;       // °C

    int rapportBVA = 0;     // indice slider 0..5
    int modeConduite = 0;   // indice slider 0..2

    void initTramesDefaut();
    Mux *mux;
};

#endif // CAN_H
