#include "virtualdevice.h"

VirtualDevice::VirtualDevice(QString name,QWidget *parent) :
    QMainWindow(parent)
{
    this->name = name;

    this->setWindowTitle(name);
}

VirtualDevice::~VirtualDevice()
{
    qDebug() << "~VirtualDevice(" << name << ")";
}
