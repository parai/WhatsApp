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
class VirtualCan : public VirtualDevice
{
    Q_OBJECT
private:
    int channelNumber;

    QPushButton* btnPlayPause;
    QPushButton* btnHexlDeci;
    QPushButton* btnAbsRelTime;

    QTableWidget* tableTrace;
public:
    explicit VirtualCan(QWidget *parent=0);
private slots:
    void play_pause(void);
    void stop(void);
    void clear_trace(void);
    void load_trace(void);
    void hexl_decimal(void);
    void abs_rel_time(void);
private:
    void createChannels(void);
};

#endif // VIRTUALCAN_H
