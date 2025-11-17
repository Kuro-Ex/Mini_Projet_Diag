#ifndef CAN_H
#define CAN_H

#include "mux.h"
#include "refmux.h"
#include <QDebug>
#include <QMessageBox>

class CAN
{
public:
    CAN(Mux *m);
    tMuxStatus configurerBus();
    void envoieMsgPeriodique();
    void recevoirMsg();
    unsigned short wCard, wBus;

    Mux *mux;
};

#endif // CAN_H
