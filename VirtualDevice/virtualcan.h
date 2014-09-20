#ifndef VIRTUALCAN_H
#define VIRTUALCAN_H
#include "virtualdevice.h"
class VirtualCan : public VirtualDevice
{
private:
    int channelNumber;
public:
    explicit VirtualCan(QWidget *parent=0);

private:
    void createChannels(void);
};

#endif // VIRTUALCAN_H
