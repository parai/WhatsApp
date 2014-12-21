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
/* ============================ [ INCLUDES  ] ====================================================== */
#include "arlua.h"
#ifdef __cplusplus
namespace autosar {
#endif
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ CLASS     ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
extern "C" int lua_main (int argc, char **argv);
static int luai_can_write (lua_State *L);
/* ============================ [ LOCALS    ] ====================================================== */
QList<QString*> luaPrint;

static const luaL_Reg autosarlib[] = {
		{"Can_Write",luai_can_write},
		{NULL,NULL}
};
/* ============================ [ FUNCTIONS ] ====================================================== */
static int luai_can_write (lua_State *L)
{
	qDebug() << "luai_can_write called" ;

	int n = lua_gettop(L);  /* number of arguments */
	if(3==n)
	{
		uint32 busid,canid;
		uint8 data[8];
		int is_num;

		busid = lua_tounsignedx(L, 1,&is_num);
		if(!is_num)
		{
			 return luaL_error(L,"incorrect argument busid to function 'Can_Write'");
		}

		canid = lua_tounsignedx(L, 2,&is_num);
		if(!is_num)
		{
			 return luaL_error(L,"incorrect argument canid to function 'Can_Write'");
		}

		qDebug()<<busid<<canid;
		int dlc = luaL_len ( L , 3 ) ;
		qDebug()<<busid<<canid<<dlc;
		if(dlc > 8)
		{
			return luaL_error(L,"len(data array{})>8 to function 'Can_Write'");
		}
		else
		{
			int i = 0;
			// Push another reference to the table on top of the stack (so we know
			// where it is, and this function can work for negative, positive and
			// pseudo indices
			lua_pushvalue(L, 3);
			// stack now contains: -1 => table
			lua_pushnil(L);
			// stack now contains: -1 => nil; -2 => table
			while (lua_next(L, -2))
			{
				// stack now contains: -1 => value; -2 => key; -3 => table
				// copy the key so that lua_tostring does not modify the original
				lua_pushvalue(L, -2);
				// stack now contains: -1 => key; -2 => value; -3 => key; -4 => table
				//printf("%s => %s\n", lua_tostring(L, -1), lua_tostring(L, -2));
				data[i] = lua_tounsignedx(L, -2,&is_num);
				if(!is_num)
				{
					return luaL_error(L,"invalid data[%d] to function 'Can_Write'",i);
				}
				else
				{
					i ++;
				}
				// pop value + copy of key, leaving original key
				lua_pop(L, 2);
				// stack now contains: -1 => key; -2 => table
			}
			// stack now contains: -1 => table (when lua_next returns 0 it pops the key
			// but does not push anything.)
			// Pop table
			lua_pop(L, 1);
			// Stack is now the same as it was on entry to this function
			qDebug()<<"Can_Write("<<busid<<","<<canid<<","<<dlc<<",["<<data[0]<<data[1]	\
					<<data[2]<<data[3]<<data[4]<<data[5]<<data[6]<<data[7]<<"])";

		}

		lua_pushnumber(L, 0);        /* result OK */
		return 1;
	}
	else
	{
		return luaL_error(L, "Can_Write (bus_id,can_id,{xx,xx,xx,xx,xx,xx,xx,xx}) API should has 3 arguments");
	}
}


extern "C" int luaopen_autosar (lua_State *L)
{
	qDebug() << "arLua:load AUTOSAR library!" ;
	luaL_newlib(L, autosarlib);
	return 1;
}
extern "C" void luai_writestring(const char* s,int l)
{
    char* local = (char*)malloc(l+1);

	if(local != NULL)
	{
		strncpy(local,s,l);
		local[l] = '\0';
		QString* string  = new QString(local);
		luaPrint.append(string);
		free(local);
	}

}
extern "C" void luai_writestringerror(const char* format,...)
{
	va_list args;
	unsigned long length;
	static char log_buf[1024];
	va_start(args, format);
	length = vsprintf(log_buf,format,args);
	va_end(args);

	luai_writestring(log_buf,length);
}
extern "C" void luai_writeline(void)
{
	luai_writestring("\n",1);
}
arLuaBG::arLuaBG(QString script,QObject *parent) :
		QThread(parent),script(script)
{

}

void arLuaBG::run()
{
	int status;
	int argc = 2;
    char* argv[2];

    argv[0] = "lua";
    argv[1] = "../WhatsApp/example/Lua.lua";
    // TODO: how to unicode to ascii
    //argv[1] = script.toLocal8Bit().data();

    status = lua_main(argc,argv);

    if(EXIT_SUCCESS == status)
    {
    	qDebug() << "Execute Script Success.";
        emit message(new QString("Execute Script Success.\n"));
    }
    else
    {
    	qDebug() << "Execute Script Fail.";
        emit message(new QString("Execute Script Fail.\n"));
    }
}


arLua::arLua(QString name,QWidget *parent) :
	arDevice(name,parent)
{
	QWidget* widget= new QWidget(this);
	QVBoxLayout* vbox = new QVBoxLayout();

	{
		QHBoxLayout* hbox = new QHBoxLayout();
		hbox->addWidget(new QLabel(tr("Script:")));
		leScript = new QLineEdit();
		leScript->setText("../WhatsApp/example/Lua.lua");
		hbox->addWidget(leScript);
		btnLoadScript = new QPushButton(tr("..."));
		connect(btnLoadScript,SIGNAL(clicked()),this,SLOT(on_btnLoadScript_clicked()));
		hbox->addWidget(btnLoadScript);

		btnExecuteScript = new QPushButton(tr("Run"));
		connect(btnExecuteScript,SIGNAL(clicked()),this,SLOT(on_btnExecuteScript_clicked()));
		hbox->addWidget(btnExecuteScript);
		vbox->addLayout(hbox);
	}

	pleResult = new QPlainTextEdit();
	pleResult->setReadOnly(true);

	vbox->addWidget(pleResult);


    widget->setLayout(vbox);
    this->setCentralWidget(widget);

    arluaBG = NULL;

    setVisible(true);

    this->startTimer(1);
}
void arLua::print(QString* msg)
{
	pleResult->setPlainText(pleResult->toPlainText()+(*msg));
	QTextCursor cursor =  pleResult->textCursor();
	cursor.movePosition(QTextCursor::End);
	pleResult->setTextCursor(cursor);
	delete msg;
}
void arLua::timerEvent(QTimerEvent* event)
{
	while(!luaPrint.isEmpty())
	{
		QString* msg = luaPrint[0];
		luaPrint.removeFirst();

		print(msg);
	}
}

void arLua::on_btnLoadScript_clicked(void)
{
	luaScript = QFileDialog::getOpenFileName(this,"Load Lua Script","../WhatsApp/example",tr("Lua script (*.lua)"));

	leScript->setText(luaScript);
}

void arLua::on_btnExecuteScript_clicked(void)
{
    if(arluaBG != NULL) { delete arluaBG; arluaBG=NULL;}

    luaScript = leScript->text();

    QFile file(luaScript);
    if(file.exists())
    {
    	pleResult->clear();
    	QString* time = new QString("arLua Start at "+QDateTime::currentDateTime().toString()+"\n");
    	print(time);
        arluaBG = new arLuaBG(luaScript,this);
        connect(arluaBG,SIGNAL(message(QString*)),this,SLOT(on_arluaBG_message(QString*)));
        arluaBG->start();
    }
    else
    {
    	QMessageBox::warning(this,"Lua Script","Invalid Script: "+luaScript);
    }
}

void arLua::on_arluaBG_message(QString* msg)
{
	print(msg);
}
#ifdef __cplusplus
} /* namespace autosar */
#endif
