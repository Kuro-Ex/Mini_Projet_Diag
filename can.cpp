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

// --- envoie de messages ---
tMuxStatus CAN::envoieMsgPeriodique(unsigned long ident)
{
    tCanMsg msg{};
    msg.wHandleMsg  = 0;
    msg.dwIdent     = ident;
    msg.eTypeId     = CAN_ID_STD;
    msg.dwMask      = 0x000;
    msg.eService    = CAN_SVC_TRANSMIT_DATA;
    msg.lPeriod     = 100;
    msg.dwReserved1 = 0;
    msg.dwReserved2 = 0;
    msg.wDataLen    = 8;

    switch (ident) {

        // ---------- 0x0F6 : clé + T° eau (et autres, mais on s'en sert pour T°) ----------
    case 0x0F6:
    {
        // Octet 0 : on garde une valeur simple (contact + moteur tournant par ex.)
        msg.bData[0] = 0xC8; // tu peux raffiner plus tard si besoin

        // Octet 1 : température eau avec offset -40
        int rawTemp = tempEau + 40;      // Physique = raw - 40
        if (rawTemp < 0)   rawTemp = 0;
        if (rawTemp > 255) rawTemp = 255;
        msg.bData[1] = static_cast<unsigned char>(rawTemp);

        msg.bData[2] = 0x00;
        msg.bData[3] = 0x00;
        msg.bData[4] = 0x00;
        msg.bData[5] = 0x00;
        msg.bData[6] = 0x00;
        msg.bData[7] = 0x00;
        break;
    }

        // ---------- 0x036 : inchangé ----------
    case 0x036:
        msg.bData[0] = 0x00;
        msg.bData[1] = 0x00;
        msg.bData[2] = 0x00;
        msg.bData[3] = 0x3D;
        msg.bData[4] = 0x01;
        msg.bData[5] = 0x00;
        msg.bData[6] = 0x00;
        msg.bData[7] = 0x00;
        break;

        // ---------- 0x168 : voyants d’alertes ----------
    case 0x168:
        if (voyantsOn) {
            // Alerte T huile + T eau
            msg.bData[0] = 0x03;
            msg.bData[1] = 0x00;
            msg.bData[2] = 0x00;
            msg.bData[3] = 0xFF;  // DEF divers
            msg.bData[4] = 0xFF;
            msg.bData[5] = 0xFF;
        } else {
            msg.bData[0] = 0x00;
            msg.bData[1] = 0x00;
            msg.bData[2] = 0x00;
            msg.bData[3] = 0x00;
            msg.bData[4] = 0x00;
            msg.bData[5] = 0x00;
        }
        msg.bData[6] = 0x00;
        msg.bData[7] = 0x00;
        break;

        // ---------- 0x128 : voyants + BVA + modes ----------
    case 0x128:
    {
        if (voyantsOn) {
            // Tous les voyants allumés
            msg.bData[0] = 0xE0;  // FRPK / AL_essence / Pre_chauff
            msg.bData[1] = 0xE0;  // Service / Stop / ABS
            msg.bData[2] = 0xE0;  // ESPI / ESRA / WARNING
            msg.bData[3] = 0x01;  // pied frein
            msg.bData[4] = 0x7F;  // tous feux
        } else {
            msg.bData[0] = 0x00;
            msg.bData[1] = 0x00;
            msg.bData[2] = 0x00;
            msg.bData[3] = 0x00;
            msg.bData[4] = 0x00;
        }

        // Octet 5 : combine actif
        msg.bData[5] = 0x80;

        // --- BVA : octet 6 ---
        unsigned char rapVal = 0;
        switch (rapportBVA) {
        case 0: rapVal = 0; break;  // P
        case 1: rapVal = 1; break;  // R
        case 2: rapVal = 2; break;  // N
        case 3: rapVal = 3; break;  // D
        case 4: rapVal = 8; break;  // 2nd
        case 5: rapVal = 9; break;  // 1er
        default: rapVal = 0; break;
        }
        msg.bData[6] = rapVal;

        // --- Mode conduite : octet 7 ---
        unsigned char modeVal = 0;
        switch (modeConduite) {
        case 0: modeVal = 0; break; // auto normal
        case 1: modeVal = 1; break; // auto + sport
        case 2: modeVal = 6; break; // auto + neige
        default: modeVal = 0; break;
        }
        msg.bData[7] = modeVal;
        break;
    }

        // ---------- 0x0B6 : micromoteurs compte-tour + vitesse ----------
    case 0x0B6:
    {
        // régime moteur : facteur 0,125 -> raw = tr/min / 0,125 = tr/min * 8
        unsigned int rawRpm = static_cast<unsigned int>(regimeMoteur * 8);
        msg.bData[0] = static_cast<unsigned char>(rawRpm & 0xFF);
        msg.bData[1] = static_cast<unsigned char>((rawRpm >> 8) & 0xFF);

        // vitesse véhicule : facteur 0,01 -> raw = km/h * 100
        unsigned int rawV = static_cast<unsigned int>(vitesse * 100);
        msg.bData[2] = static_cast<unsigned char>(rawV & 0xFF);
        msg.bData[3] = static_cast<unsigned char>((rawV >> 8) & 0xFF);

        msg.bData[4] = 0x00;
        msg.bData[5] = 0x00;
        msg.bData[6] = 0x00;
        msg.bData[7] = 0x00;
        break;
    }

        // ---------- 0x161 : micromoteur jauge essence ----------
    case 0x161:
        msg.bData[0] = 0x00;
        msg.bData[1] = 0x00;
        msg.bData[2] = 0x00;
        msg.bData[3] = static_cast<unsigned char>(jaugeEssence); // 0..100
        msg.bData[4] = 0x00;
        msg.bData[5] = 0x00;
        msg.bData[6] = 0x00;
        msg.bData[7] = 0x00;
        break;

    default:
        QMessageBox::warning(nullptr, "Erreur CAN",
                             QString("ID 0x%1 non géré.").arg(ident, 0, 16).toUpper());
        return STATUS_ERR_PARAM;
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
    if (trmin > 8000) trmin = 8000;
    regimeMoteur = trmin;
}

void CAN::setVitesse(int kmh)
{
    if (kmh < 0) kmh = 0;
    if (kmh > 250) kmh = 250;
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
    if (idx > 5) idx = 5;
    rapportBVA = idx;
}

void CAN::setModeConduiteIndex(int idx)
{
    if (idx < 0) idx = 0;
    if (idx > 2) idx = 2;
    modeConduite = idx;
}
