#ifndef VIRTUALCAN_H
#define VIRTUALCAN_H
#include "virtualdevice.h"
#include <QObject>
#include <QGridLayout>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QFileDialog>
#include "ocdevice.h"
class SimulationCan : public OcDevice
{
    Q_OBJECT
private:
    unsigned long canCardId;
    QList<OcMessage*> rxMsgList;
    QList<OcMessage*> txMsgList;
public:
    explicit SimulationCan(unsigned long canCardId);
    ~SimulationCan();
private:

public:
    OcStatus startup();
    OcStatus shutdown();
    OcStatus sendMessage(const OcMessage &msg);
    OcStatus receivedMessage();
    OcStatus internalGetMessage(OcMessage *msg);
    int getBaudRate();
    OcStatus setBaudRate(int baud);
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

    QTableWidget* tableTrace;
public:
    explicit VirtualCan(unsigned long channelNumber,QWidget *parent=0);
    ~VirtualCan();
private slots:
    void play_pause(void);
    void stop(void);
    void clear_trace(void);
    void load_trace(void);
    void hexl_decimal(void);
    void abs_rel_time(void);
private:
    void createGui(void);
};

#endif // VIRTUALCAN_H
