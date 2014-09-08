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
        this->createToolbar();
        this->startTimer(1);

        StartOS(OSDEFAULTAPPMODE);
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
void Entry::save()
{
    QMessageBox::about(this,"Save","Toolbar Icon Save Clicked!");
}

// ==================== [ PRIVATE FUNCTIONS ] ==================================
void Entry::createToolbar(void)
{
    QToolBar* toolbar = NULL;
    QAction * action = NULL;
    toolbar = this->addToolBar("Console");

    action = new QAction(QIcon(mICON_SAVE),tr("&Save"),this);
    action->setShortcut(tr("Ctrl+S"));
    this->connect(action,SIGNAL(triggered()),this,SLOT(save()));
    toolbar->addAction(action);
}
