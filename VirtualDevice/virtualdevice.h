#ifndef VIRTUALDEVICE_H
#define VIRTUALDEVICE_H

#include <QMainWindow>
#include <QDebug>

class VirtualDevice : public QMainWindow
{
    Q_OBJECT
private:
    QString name;
public:
    explicit VirtualDevice(QString name,QWidget *parent = 0);
    virtual ~VirtualDevice();
    QString Name(void) { return this->name; }

signals:

private slots:
    virtual void wakeup(void) {
        if(!this->isVisible())
        {
            this->show();
        }
    }
};

#endif // VIRTUALDEVICE_H
