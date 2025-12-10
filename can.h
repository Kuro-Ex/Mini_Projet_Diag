#ifndef CAN_H
#define CAN_H

#include "mux.h"
#include "refmux.h"
#include "canframe.h"

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
    bool buildFrame(unsigned long ident, can_frame &frame);

    // ---------- SIMULATION : SETTERS ----------
    // Voyants du combiné
    void setVoyantsAll(bool on);

    // Micromoteurs
    void setRegimeMoteur(int trmin);     // compte-tour
    void setVitesse(int kmh);            // compteur
    void setJaugeEssence(int pourcent);  // 0..100%
    void setTempEau(int degC);           // °C
    void setLuminosite(int value);

    // BVA + modes
    void setRapportBVAIndex(int idx);    // slider états P/R/N/D/2/1
    void setModeConduiteIndex(int idx);  // slider états Normal/Sport/Hiver

    void setClignoGauche(bool on); //btn clignotant gauche
    void setClignoDroite(bool on); //btn clignotant droite
    void setfeuxBrouilAV(bool on);
    void setfeuxBrouilAR(bool on);
    void setfeuxRoute(bool on);
    void setfeuxCrois(bool on);
    void setfeuxPos(bool on);
    void setService(bool on);
    void setFrpk(bool on);
    void setAbs(bool on);
    void setAlerteHuile(bool on);
    void setESPI(bool on);
    void setSecPassDef(bool on);
    void setAirBagArr(bool on);
    void setAirBag(bool on);
    void setStop(bool on);

private:
         // ---------- ETAT COURANT ----------
    bool voyantsOn = false;
    bool clignoGauche = false;
    bool clignoDroite = false;
    bool feuxBrouilAV = false;
    bool feuxBrouilAR = false;
    bool feuxRoute = false;
    bool feuxCrois = false;
    bool feuxPos = false;
    bool service = false;
    bool moteur = false;
    bool frpk = false;
    bool abs = false;
    bool alerteHuile = false;
    bool espI = false;
    bool secPassDef = false;
    bool airBagArr = false;
    bool airbag = false;
    bool stop = false;

    int regimeMoteur = 0;   // tr/min
    int vitesse = 0;        // km/h
    int jaugeEssence = 0;   // %
    int tempEau = 20;       // °C
    int rapportBVA = 0;     // indice slider 0..5
    int modeConduite = 0;   // indice slider 0..2
    int  luminosite     = 0;   // 0..15 pour le rétro-éclairage

    void initTramesDefaut();
    Mux *mux;
};

#endif // CAN_H
