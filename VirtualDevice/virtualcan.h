#ifndef VIRTUALCAN_H
#define VIRTUALCAN_H
#include "virtualdevice.h"
#include <QObject>
#include <QGridLayout>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QFileDialog>
#include <QMessageBox>
#include "ocdevice.h"
#include "Os.h"
#include "Can.h"
using namespace autosar;
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

class VirtualCan : public VirtualDevice
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
    explicit VirtualCan(unsigned long channelNumber,QWidget *parent=0);
    ~VirtualCan();
    void SendMessage(PduIdType swHandle,OcMessage *msg);
    static class VirtualCan* GetInstance(void);
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

#endif // VIRTUALCAN_H
