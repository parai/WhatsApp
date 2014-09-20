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

Entry::Entry(QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowTitle("WhatsApp ( parai@foxmail.com )");
    this->setWindowIcon(QIcon(mICON_PARAI));
    this->createMenuAndToolbar();
    this->startTimer(1);

    this->resize(600,20);

    // example ...
    VirtualDevice* device = new VirtualCan(this);
    registerVirtualDevice(device);

    StartOS(OSDEFAULTAPPMODE);
}

void Entry::registerVirtualDevice(VirtualDevice* virtualDevice)
{
    std::string key((const char *)virtualDevice->Name().toLocal8Bit());
    std::pair<map_virtual_device_t::iterator, bool> status = map_virtual_device.insert(std::make_pair(key, virtualDevice));
    if (status.second == false)
    {
        qDebug() << "System error: Virtual device " << virtualDevice->Name() << " re-registeration!\n";
    }
    else
    {
        QAction * action = new QAction(virtualDevice->Name(),this);
        this->connect(action,SIGNAL(triggered()),virtualDevice,SLOT(wakeup()));
        menuVD->addAction(action);
    }
}

// ==================== [ SIGNALS       ] =====================================
void Entry::timerEvent(QTimerEvent *Event)
{
    static int iCounter = 0;
    iCounter ++ ;
    (void)Event;
    //qDebug() << iCounter << "ms Timer Elapsed!\n";
    OsTick();
    (void)Schedule();
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
