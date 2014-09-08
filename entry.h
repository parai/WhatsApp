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

#include <QMainWindow>
#include <QAction>
#include <QToolBar>
#include <QIcon>
#include <QMessageBox>
#include <QDebug>
// ====================== [ ICON RESOURCES ] =======================
#define mRES_DIR   "D:/Qt/Projects/WhatsApp/res/"   /* Base Directory */
#define mICON_SAVE mRES_DIR "isave.bmp"

class Entry : public QMainWindow
{
    Q_OBJECT
public:
    explicit Entry(QWidget *parent = 0);

signals:

protected:
    void timerEvent(QTimerEvent *Event);
private slots:
    void save();
private:
    void createToolbar(void);

};

#endif // ENTRY_H
