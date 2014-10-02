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
#ifndef ENTRY_H
#define ENTRY_H
#include <QtWidgets>
#include <QMainWindow>
#include <QAction>
#include <QToolBar>
#include <QIcon>
#include <QMessageBox>
#include <QDebug>
#include "virtualdevice.h"
#include "virtualcan.h"
#include <QMap>

typedef QMap<QString,VirtualDevice*> map_virtual_device_t;
// ====================== [ ICON RESOURCES ] =======================
#define mRES_DIR   ":/res/"   /* Base Directory */
#define mICON_SAVE  mRES_DIR "isave.bmp"
#define mICON_PARAI mRES_DIR "iParai.png"
class Entry : public QMainWindow
{
    Q_OBJECT
private:
    map_virtual_device_t map_virtual_device;
    QMenu* menuBSW /* Basic Software Modules*/;
    QMenu* menuVD  /* Virtual Device */;
public:
    explicit Entry(QWidget *parent = 0);
    ~Entry();

    void registerVirtualDevice(VirtualDevice* virtualDevice);

signals:

protected:
    void timerEvent(QTimerEvent *Event);
private slots:
    void save(void);
    void open(void);
private:
    void createMenuAndToolbar(void);
    void createToolbar(void);

};

#endif // ENTRY_H
