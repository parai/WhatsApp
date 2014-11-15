#include "ardevice.h"

arDevice::arDevice(QString name,QWidget *parent) :
    QMainWindow(parent)
{
    this->name = name;

    this->setWindowTitle(name);
}

arDevice::~arDevice()
{
    qDebug() << "~arDevice(" << name << ")";
}
