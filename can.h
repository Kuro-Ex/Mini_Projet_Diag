#ifndef CAN_H
#define CAN_H

#include "mux.h"
#include "refmux.h"
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QStandardItemModel>


class CAN
{
public:
    CAN(Mux *m);
    tMuxStatus configurerBus();
    tMuxStatus envoieMsgPeriodique(unsigned long ident);
    void recevoirMsg();
    void recevoirMsg(QStandardItemModel *model);
    unsigned short wCard, wBus;

    Mux *mux;
};

#endif // CAN_H
