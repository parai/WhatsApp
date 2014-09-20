#ifndef VIRTUALDEVICE_H
#define VIRTUALDEVICE_H

#include <QMainWindow>

class VirtualDevice : public QMainWindow
{
    Q_OBJECT
private:
    QString name;
public:
    explicit VirtualDevice(QString name,QWidget *parent = 0);

    QString Name(void) { return this->name; }

signals:

public slots:
    virtual void wakeup(void) {
        if(!this->isVisible())
        {
            this->show();
        }
    }

};

#endif // VIRTUALDEVICE_H
