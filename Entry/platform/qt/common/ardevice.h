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
#ifndef ARDEVICE_H
#define ARDEVICE_H
/* ============================ [ INCLUDES  ] ====================================================== */
#include <QMainWindow>
#include <QDebug>
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ CLASS     ] ====================================================== */
/* basic devices for QT platform, both for real devices and simulation devices. */
class arDevice : public QMainWindow
{
    Q_OBJECT
private:
    QString name;
public:
    explicit arDevice(QString name,QWidget *parent = 0);
    virtual ~arDevice();
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
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */


#endif // DEVICE_H
