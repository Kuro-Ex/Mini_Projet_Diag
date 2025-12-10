#include "can.h"
#include "refmux.h"


CAN::CAN(Mux *m) {
    mux = m;
    initTramesDefaut();
}

// État par défaut de la simulation
void CAN::initTramesDefaut()
{
    voyantsOn    = false;
    regimeMoteur = 0;
    vitesse      = 0;
    jaugeEssence = 0;
    tempEau      = 20;
    rapportBVA   = 0;  // P
    modeConduite = 0;  // Normal
    luminosite   = 0;  // rétro-éclairage minimum au démarrage

}

tMuxStatus CAN::configurerBus(){

    if (!mux->carteOuverte) {
        QMessageBox::critical(nullptr, "Erreur CAN", "Carte non ouverte !");
        return STATUS_ERR_NO_DEVICE;
    }

    // --- configuration du mode opératoire ---
    tCanOper hCanOper{};
    hCanOper.eCanOperMode = CAN_OPER_ANA_FIFO;  // Mode FIFO
    hCanOper.wFifoSize = 200;

    tMuxStatus status = CanConfigOper(mux->wCard, mux->hMuxConfigMode.wBusInterface, &hCanOper);
    if (status != STATUS_OK) {
        QMessageBox::critical(nullptr, "Erreur CAN", QString("CanConfigOper échoué (%1)").arg(status));
        return status;
    }

    // --- configuration des paramètres supplémentaires ---
    tCanParam hCanParam{};
    hCanParam.dwFiltIdent = 0x000;
    hCanParam.eTypeId = CAN_ID_STD;
    hCanParam.dwFiltMask = 0x000;
    hCanParam.eAckEnable = CAN_TRUE;
    hCanParam.eRxAll = CAN_TRUE;
    hCanParam.wSpecialModes = 0x000;

    status = CanConfigParam(mux->wCard, mux->hMuxConfigMode.wBusInterface, &hCanParam);
    if (status != STATUS_OK) {
        QMessageBox::critical(nullptr, "Erreur CAN", QString("CanConfigParam échoué (%1)").arg(status));
        return status;
    }

    // --- Configuration à 500 kb/s (High Speed) ---
    tCanBus hCanBus{};
    hCanBus.wBRP = 4;   //1->500 kbit/s 2->250 kbit/s   4->125 kbit/s
    hCanBus.wTSEG1 = 12;
    hCanBus.wTSEG2 = 3;
    hCanBus.wSJW = 1;
    hCanBus.wSPL = 1;

    status = CanConfigBus(mux->wCard, mux->hMuxConfigMode.wBusInterface, &hCanBus);
    if (status != STATUS_OK) {
        QMessageBox::critical(nullptr, "Erreur CAN", QString("CanConfigBus échoué (%1)").arg(status));
        return status;
    }

    // --- activation du Bus ---
    status = CanActivate(mux->wCard, mux->hMuxConfigMode.wBusInterface);
    if (status == STATUS_OK) {
        QMessageBox::information(nullptr, "Activation CAN", "Le bus CAN a été activé avec succès !");
    } else {
        QMessageBox::critical(nullptr, "Erreur CAN",QString("Échec de l'activation du bus CAN.\nCode d'erreur : %1").arg(status));
    }

    return status;
}

bool CAN::buildFrame(unsigned long ident, can_frame &frame)
{
    frame.can_id  = ident;
    frame.can_dlc = 8;

    for (int i = 0; i < 8; ++i)
        frame.data[i] = 0x00;

    switch (ident) {

    case 0x0F6:
    {
        frame.data[0] = 0xC8;

        int rawTemp = tempEau + 40;
        if (rawTemp < 0)   rawTemp = 0;
        if (rawTemp > 255) rawTemp = 255;
        frame.data[1] = static_cast<unsigned char>(rawTemp);
        break;
    }

    case 0x036:
    {
        unsigned char lum = static_cast<unsigned char>(luminosite & 0x0F);
        frame.data[3] = static_cast<unsigned char>(0x30 | lum);
        frame.data[4] = 0x01;
        break;
    }

    case 0x168:
    {
        unsigned char oct0 = 0x00;
        unsigned char oct3 = 0x00;
        unsigned char oct4 = 0x00;

        if (voyantsOn) {
            oct0           |= 0x03;
            oct3           |= 0xFF;
            frame.data[4]  = 0xEF;
            frame.data[5]  = 0xFF;
        }

        if (abs)        oct3 |= 0x20;
        if (airbag)     oct4 |= 0x20;
        if (secPassDef) oct4 |= 0x10;

        frame.data[0] = oct0;
        frame.data[3] = oct3;
        frame.data[4] = oct4;
        break;
    }

    case 0x128:
    {
        unsigned char oct0 = 0x00;
        unsigned char oct1 = 0x00;
        unsigned char oct2 = 0x00;
        unsigned char oct4 = 0x00;

        if (voyantsOn) {
            oct0 = 0xE0;
            oct1 = 0xFF;
            frame.data[3] = 0xE0;
            oct4 = 0xFF;
        }

        if (frpk)        oct0 |= 0x20;
        if (alerteHuile) oct0 |= 0x10;
        if (airBagArr)   oct0 |= 0x80;

        if (service)     oct1 |= 0x80;
        if (stop)        oct1 |= 0x40;

        if (espI)        oct2 |= 0x10;

        if (clignoGauche) oct4 |= 0x02;
        if (clignoDroite) oct4 |= 0x04;
        if (feuxBrouilAR) oct4 |= 0x08;
        if (feuxBrouilAV) oct4 |= 0x10;
        if (feuxRoute)    oct4 |= 0x20;
        if (feuxCrois)    oct4 |= 0x40;
        if (feuxPos)      oct4 |= 0x80;

        frame.data[0] = oct0;
        frame.data[1] = oct1;
        frame.data[2] = oct2;
        frame.data[4] = oct4;
        frame.data[5] = 0x80;

        unsigned char rapVal = 0;
        switch (rapportBVA) {
        case 0: rapVal = 0x00; break;
        case 1: rapVal = 0x10; break;
        case 2: rapVal = 0x20; break;
        case 3: rapVal = 0x30; break;
        case 4: rapVal = 0x90; break;
        case 5: rapVal = 0x80; break;
        case 6: rapVal = 0x70; break;
        case 7: rapVal = 0x60; break;
        case 8: rapVal = 0x50; break;
        case 9: rapVal = 0x40; break;
        default: rapVal = 0x00; break;
        }
        frame.data[6] = rapVal;

        unsigned char modeVal = 0;
        switch (modeConduite) {
        case 0: modeVal = 0x00; break;
        case 1: modeVal = 0x20; break;
        case 2: modeVal = 0x40; break;
        case 3: modeVal = 0x50; break;
        case 4: modeVal = 0x60; break;
        default: modeVal = 0x00; break;
        }
        frame.data[7] = modeVal;
        break;
    }

    case 0x0B6:
    {
        unsigned int rawRpm = static_cast<unsigned int>(regimeMoteur / 0.125);
        frame.data[0] = static_cast<unsigned char>((rawRpm >> 8) & 0xFF);
        frame.data[1] = static_cast<unsigned char>( rawRpm       & 0xFF);

        unsigned int rawV = static_cast<unsigned int>(vitesse / 0.01);
        frame.data[2] = static_cast<unsigned char>((rawV >> 8) & 0xFF);
        frame.data[3] = static_cast<unsigned char>( rawV       & 0xFF);
        break;
    }

    case 0x161:
    {
        frame.data[3] = static_cast<unsigned char>(jaugeEssence);
        break;
    }

    default:
        return false;
    }

    return true;
}
// --- envoie de messages ---
tMuxStatus CAN::envoieMsgPeriodique(unsigned long ident)
{
    if (!mux || !mux->carteOuverte) {
        QMessageBox::critical(nullptr, "Erreur CAN", "Carte non ouverte !");
        return STATUS_ERR_NO_DEVICE;
    }

    can_frame frame{};
    if (!buildFrame(ident, frame)) {
        QMessageBox::warning(nullptr, "Erreur CAN",
                             QString("ID 0x%1 non géré.").arg(ident, 0, 16).toUpper());
        return STATUS_ERR_PARAM;
    }

    tCanMsg msg{};
    msg.wHandleMsg  = 0;
    msg.dwIdent     = frame.can_id;
    msg.eTypeId     = CAN_ID_STD;
    msg.dwMask      = 0x000;
    msg.eService    = CAN_SVC_TRANSMIT_DATA;
    msg.lPeriod     = 100;
    msg.dwReserved1 = 0;
    msg.dwReserved2 = 0;
    msg.wDataLen    = frame.can_dlc;

    for (int i = 0; i < frame.can_dlc && i < 8; ++i) {
        msg.bData[i] = frame.data[i];
    }

    tMuxStatus status = CanSendMsg(mux->wCard, mux->hMuxConfigMode.wBusInterface, &msg);
    if (status != STATUS_OK) {
        QMessageBox::critical(
            nullptr,
            "Erreur CAN",
            QString("Échec CanSendMsg (ID 0x%1, code %2)")
                .arg(ident, 0, 16).toUpper()
                .arg(status)
            );
    }
    return status;
}

// --- reception de messages ---
void CAN::recevoirMsg(QStandardItemModel *model)
{
    if (!mux || !mux->carteOuverte || !model) {
        return;
    }

    unsigned short wCount = 0;   // Nombre d'évènements CAN présents dans la FIFO
    unsigned short wMax   = 0;   // Capacité maximale de la FIFO

    tMuxStatus st = CanGetFifoRxLevel(mux->wCard,mux->hMuxConfigMode.wBusInterface,0, &wCount, &wMax);  // 0 = FIFO globale

    if (st != STATUS_OK || wCount == 0) {
        return;
    }

    for (unsigned short i = 0; i < wCount; ++i) {

        tCanEvent evt{};
        st = CanGetEvent(
            mux->wCard,
            mux->hMuxConfigMode.wBusInterface,
            &evt
            );

        if (st != STATUS_OK) {
            qDebug() << "[CAN RX] Erreur CanGetEvent, code =" << st;
            break;
        }

        bool isMsgType =
            (evt.eTypeEvent == EVENT_CAN_MSGRX)  ||
            (evt.eTypeEvent == EVENT_CAN_MSGTX);

        if (!isMsgType) {
            continue;
        }

        bool isDataSvc =
            (evt.eService == CAN_SVC_RECEIVE_DATA)  ||
            (evt.eService == CAN_SVC_TRANSMIT_DATA);

        if (!isDataSvc) {
            continue;
        }

        // Conversion du timestamp en HH:MM:SS.mmm
        double time_ms = evt.dwTimeStamp / 10.0;
        int total_ms   = static_cast<int>(time_ms);

        int heures  = total_ms / 3600000;
        int reste   = total_ms % 3600000;
        int minutes = reste / 60000;
        reste       = reste % 60000;
        int secondes = reste / 1000;
        int ms       = reste % 1000;

        QString timeStr = QString("%1:%2:%3.%4")
                              .arg(heures,  2, 10, QLatin1Char('0'))
                              .arg(minutes, 2, 10, QLatin1Char('0'))
                              .arg(secondes,2, 10, QLatin1Char('0'))
                              .arg(ms,      3, 10, QLatin1Char('0'));

        // Données hexadécimales
        QString dataStr;
        int dataLen = qMin<int>(evt.wDataLen, 8); // sécurité

        for (int b = 0; b < dataLen; ++b) {
            dataStr += QString("%1 ")
                           .arg(evt.bData[b], 2, 16, QLatin1Char('0'))
                           .toUpper();
        }

        // Ligne affichée dans la ListView
        QString line = QString("%1   ID:0x%2   Lg:%3   Data:%4   Type:%5   Svc:%6")
                           .arg(timeStr)
                           .arg(evt.dwIdent, 0, 16).toUpper()
                           .arg(dataLen)
                           .arg(dataStr.trimmed())
                           .arg(evt.eTypeEvent)
                           .arg(evt.eService);

        QStandardItem *item = new QStandardItem(line);
        model->appendRow(item);

        //limite le nombre de lignes pour éviter de saturer la RAM
        const int maxRows = 2000;
        if (model->rowCount() > maxRows) {
            model->removeRow(0);
        }
    }
}

// ---------- SETTERS SIMULATION ----------

void CAN::setVoyantsAll(bool on)
{
    voyantsOn = on;
}

void CAN::setRegimeMoteur(int trmin)
{
    if (trmin < 0) trmin = 0;
    if (trmin > 7000) trmin = 7000;
    regimeMoteur = trmin;
}

void CAN::setVitesse(int kmh)
{
    if (kmh < 0) kmh = 0;
    if (kmh > 220) kmh = 220;
    vitesse = kmh;
}

void CAN::setJaugeEssence(int pourcent)
{
    if (pourcent < 0) pourcent = 0;
    if (pourcent > 100) pourcent = 100;
    jaugeEssence = pourcent;
}

void CAN::setTempEau(int degC)
{
    if (degC < -40) degC = -40;
    if (degC > 210) degC = 210;
    tempEau = degC;
}

void CAN::setRapportBVAIndex(int idx)
{
    if (idx < 0) idx = 0;
    if (idx > 10) idx = 10;
    rapportBVA = idx;
}

void CAN::setModeConduiteIndex(int idx)
{
    if (idx < 0) idx = 0;
    if (idx > 5) idx = 5;
    modeConduite = idx;
}

void CAN::setLuminosite(int value)
{
    if (value < 0)  value = 0;
    if (value > 15) value = 15;
    luminosite = value;
}

void CAN::setClignoGauche(bool on)
{
    clignoGauche = on;
}

void CAN::setClignoDroite(bool on)
{
    clignoDroite = on;
}

void CAN::setfeuxBrouilAR(bool on)
{
    feuxBrouilAR = on;
}
void CAN::setfeuxBrouilAV(bool on)
{
    feuxBrouilAV = on;
}
void CAN::setfeuxRoute(bool on)
{
    feuxRoute = on;
}

void CAN::setfeuxCrois(bool on)
{
    feuxCrois = on;
}

void CAN::setfeuxPos(bool on)
{
    feuxPos = on;
}

void CAN::setService(bool on)
{
    service = on;
}

void CAN::setFrpk(bool on){
    frpk = on;
}

void CAN::setAbs(bool on){
    abs = on;
}

void CAN::setAlerteHuile(bool on){
    alerteHuile = on;
}

void CAN::setESPI(bool on){
    espI = on;
}

void CAN::setSecPassDef(bool on){
    secPassDef = on;
}


void CAN::setAirBagArr(bool on){
    airBagArr = on;
}

void CAN::setAirBag(bool on){
    airbag = on;
}
void CAN::setStop(bool on){
    stop = on;
}
