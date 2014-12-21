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
#ifndef ARLUA_H_
#define ARLUA_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
#include <QThread>
#include <signal.h>
#include "lua.hpp"
#include "ardevice.h"

#ifdef __cplusplus
namespace autosar {
#endif
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ CLASS     ] ====================================================== */
class arLuaBG: public QThread
{
    Q_OBJECT
private:
    QString script;
private:

public:
    explicit arLuaBG(QString script,QObject *parent = 0);

    void run();
signals:
    void message(QString* msg);
};

class arLua : public arDevice
{
	Q_OBJECT
private:
	QPushButton * btnLoadScript;
	QPushButton * btnExecuteScript;
	QLineEdit * leScript;
	QPlainTextEdit* pleResult;
	QString  luaScript;

    arLuaBG* arluaBG;
public:
    explicit arLua(QString name,QWidget *parent = 0);

    void timerEvent(QTimerEvent*);
private:
    void print(QString*);
private slots:
	void on_btnLoadScript_clicked(void);
	void on_btnExecuteScript_clicked(void);
	void on_arluaBG_message(QString*);
};
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __cplusplus
}  /* name space */
#endif
#endif /* ARLUA_H_ */
