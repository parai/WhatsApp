/**
 * WhatsApp - the open source AUTOSAR platform https://github.com/parai
 *
 * Copyright (C) 2014  WhatsApp <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */
#ifndef ARCAN_H
#define ARCAN_H
/* ============================ [ INCLUDES  ] ====================================================== */
#include "ardevice.h"
#include "ocdevice.h"
#include "Os.h"
#include "Can.h"
/* ============================ [ MACROS    ] ====================================================== */
using namespace autosar;

/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ CLASS     ] ====================================================== */
class SimulationCan : public OcDevice
{
    Q_OBJECT
private:
    unsigned long canCardId;
    unsigned long rxMsgIndex;
    unsigned long txMsgIndex;
    TickType  osTick;
    TickType  prevMsgTimeStamp;
    QList<OcMessage*> rxMsgList;
    QList<OcMessage*> txMsgList;
public:
    explicit SimulationCan(unsigned long canCardId);
    ~SimulationCan();
    void clear(void);
private:

public:
    OcStatus startup();
    OcStatus shutdown();
    OcStatus sendMessage(const OcMessage &msg);
    OcStatus receivedMessage();
    OcStatus internalGetMessage(OcMessage *msg);
    int getBaudRate();
    OcStatus setBaudRate(int baud);
    void registerRxMsg(OcMessage *msg);
    void registerTxMsg(OcMessage *msg);
};

class arCan : public arDevice
{
    Q_OBJECT
private:
    unsigned long channelNumber;
    QList<SimulationCan*> simulationCanList;
    QPushButton* btnPlayPause;
    QPushButton* btnHexlDeci;
    QPushButton* btnAbsRelTime;
    QPushButton* btnLoadTrace;
    QPushButton* btnStop;
    QComboBox*   cbBus;
    QLineEdit*   leId;
    QLineEdit*   leData;
    QTableWidget* tableTrace;
    QList<PduIdType> swHandle;
    QList<int>       timerId;
public:
    explicit arCan(QString name,unsigned long channelNumber,QWidget *parent=0);
    ~arCan();
    void WriteMessage(PduIdType swHandle,OcMessage *msg);
private slots:
    void on_play_pause(void);
    void on_stop(void);
    void on_clear_trace(void);
    void on_save_trace(void);
    void on_load_trace(void);
    void on_hexl_decimal(void);
    void on_abs_rel_time(void);
    void on_messageReceived(OcMessage *, const QTime &);
    void on_trigger_tx(void);
private:
    void createGui(void);
    OcMessage* entry2msg(QRegularExpressionMatch match);
    void putMsg(OcMessage*);
    void clear(void);

    void timerEvent(QTimerEvent * Event);
};
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#endif /* ARCAN_H */
