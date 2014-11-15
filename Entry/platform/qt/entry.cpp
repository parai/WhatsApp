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

static class Entry* self = NULL;

Entry::Entry ( QWidget *parent )
		: QMainWindow(parent)
{
	self = this;
	this->setWindowTitle("WhatsApp ( parai@foxmail.com )");
    this->setWindowIcon(QIcon(ICON_PARAI));
	this->createMenuAndToolbar();
	this->startTimer(1);

	this->setGeometry(25,30,600,20);

	EcuM_Init();
}

class Entry* Entry::Self ( void )
{
	return self;
}
Entry::~Entry ( )
{
	qDebug() << "~Entry()";

	map_device.clear(); // this in charge to destroy VirtualDevice
}

void Entry::registerDevice ( arDevice* device )
{
	if ( map_device.contains(device->Name()) )
	{
		qDebug() << "System error: Device " << device->Name() << " re-registeration!\n";
		delete device;
	}
	else
	{
		map_device[device->Name()] = device;
		QAction * action = new QAction(device->Name(),this);
		this->connect(action,SIGNAL(triggered()),device,SLOT(wakeup()));
		menuVD->addAction(action);
	}
}
void Entry::deleteDevice ( QString name )
{
	if ( map_device.contains(name) )
	{
		arDevice* device = map_device.take(name);
		delete device;
		/* menu virtual device re-build */
		menuVD->clear();
		QList<arDevice*> devices = 	map_device.values();
		for(int i=0;i<devices.size();i++)
		{
			device = devices[i];
			QAction * action = new QAction(device->Name(),this);
			this->connect(action,SIGNAL(triggered()),device,SLOT(wakeup()));
			menuVD->addAction(action);
		}
	}
	else
	{
		qDebug() << "System error: Virtual device " << name  << " delete!\n";
	}
}

arDevice* Entry::getDevice ( QString name )
{
	if ( map_device.contains(name) )
	{
		return map_device[name];
	}
	else
	{
		return NULL;
	}
}

// ==================== [ SIGNALS       ] =====================================
void Entry::timerEvent ( QTimerEvent *Event )
{
	OsTick();
#if defined(USE_KERNEL1)
	Schedule();
#endif
}

// ==================== [ PRIVATE SLOTS ] ======================================
void Entry::open ( void )
{

}

void Entry::save ( void )
{

}

// ==================== [ PRIVATE FUNCTIONS ] ==================================
void Entry::createMenuAndToolbar ( void )
{
	QAction * action = NULL;
	QToolBar* toolbar = this->addToolBar("Console");
	QMenu* menubar = this->menuBar()->addMenu(tr("File"));

	action = new QAction(tr("&Open"),this);
	action->setShortcut(tr("Ctrl+O"));
	this->connect(action,SIGNAL(triggered()),this,SLOT(open()));
	menubar->addAction(action);

    action = new QAction(QIcon(ICON_SAVE),tr("&Save"),this);
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
