#include "can.h"
#include "refmux.h"

CAN::CAN(Mux *m) {
    mux = m;
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
    hCanBus.wBRP = 1;   //1->500 kbit/s 2->250 kbit/s   3->125 kbit/s
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

void CAN::envoieMsgPeriodique(){
    // --- Configuration de la periode ---
    tCanPeriodicMsg hCanPeriodic{};
    hCanPeriodic.wOffset = 0;
    hCanPeriodic.wParam = 1;

    //  -- Configuration du format des msg ---
    tCanMsg msgCan{};
    msgCan.wHandleMsg = 0;
    msgCan.dwIdent = 0x100;
    msgCan.eTypeId = CAN_ID_STD;
    msgCan.dwMask = 0x000;
    msgCan.eService = CAN_SVC_TRANSMIT_DATA;
    msgCan.lPeriod = 100;// Période d’envoi en ms
    msgCan.dwReserved1 = 0x000;
    msgCan.dwReserved2 = 0x000;
    msgCan.wDataLen = 8;
    msgCan.bData[0] = 0x11;
    msgCan.bData[1] = 0x22;
    msgCan.bData[2] = 0x33;
    msgCan.bData[3] = 0x44;
    msgCan.bData[4] = 0x55;
    msgCan.bData[5] = 0x66;
    msgCan.bData[6] = 0x77;
    msgCan.bData[7] = 0x88;
}

void CAN::recevoirMsg(){

}
