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
#include "entry.h"
#include "Os.h"
#include "EcuM.h"
using namespace autosar;

Entry::Entry(QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowTitle("WhatsApp ( parai@foxmail.com )");
    this->setWindowIcon(QIcon(mICON_PARAI));
    this->createMenuAndToolbar();
    this->startTimer(1);

    this->setGeometry(25,30,600,20);

    // example ...
    VirtualDevice* device = new VirtualCan(4,this);
    registerVirtualDevice(device);
    device->setVisible(true);

    EcuM_Init();
}

Entry::~Entry()
{
    qDebug()<<"~Entry()";

    map_virtual_device.clear(); // this in charge to destroy VirtualDevice
}

void Entry::registerVirtualDevice(VirtualDevice* virtualDevice)
{
    if (map_virtual_device.contains(virtualDevice->Name()))
    {
        qDebug() << "System error: Virtual device " << virtualDevice->Name() << " re-registeration!\n";
    }
    else
    {
        map_virtual_device[virtualDevice->Name()] = virtualDevice;
        QAction * action = new QAction(virtualDevice->Name(),this);
        this->connect(action,SIGNAL(triggered()),virtualDevice,SLOT(wakeup()));
        menuVD->addAction(action);
    }
}

// ==================== [ SIGNALS       ] =====================================
void Entry::timerEvent(QTimerEvent *Event)
{
    OsTick();
#if defined(USE_KERNEL1)
    Schedule();
#endif
}

// ==================== [ PRIVATE SLOTS ] ======================================
void Entry::open(void)
{

}

void Entry::save(void)
{

}

// ==================== [ PRIVATE FUNCTIONS ] ==================================
void Entry::createMenuAndToolbar(void)
{
    QAction * action = NULL;
    QToolBar* toolbar = this->addToolBar("Console");
    QMenu* menubar = this->menuBar()->addMenu(tr("File"));

    action = new QAction(tr("&Open"),this);
    action->setShortcut(tr("Ctrl+O"));
    this->connect(action,SIGNAL(triggered()),this,SLOT(open()));
    menubar->addAction(action);

    action = new QAction(QIcon(mICON_SAVE),tr("&Save"),this);
    action->setShortcut(tr("Ctrl+S"));
    this->connect(action,SIGNAL(triggered()),this,SLOT(save()));
    toolbar->addAction(action);
    menubar->addAction(action);

    action = new QAction(tr("&Exit"),this);
    action->setShortcut(tr("Ctrl+Q"));
    this->connect(action,SIGNAL(triggered()),this,SLOT(close()));
    menubar->addAction(action);

    this->menuBSW = this->menuBar()->addMenu(tr("BSW"));

    this->menuVD = menuBSW->addMenu(tr("Virtual Device"));
}
