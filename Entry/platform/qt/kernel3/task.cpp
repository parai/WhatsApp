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
#include "task.h"
#include <QList>
namespace autosar {
extern "C" {

/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ CLASS     ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
QList<arTask*> task_context;
/* ============================ [ DECLARES  ] ====================================================== */
extern FUNC(void,MEM_OsAlarmInit)    OsAlarmInit ( void );
extern FUNC(void,MEM_OsResourceInit) OsResourceInit ( void );
/* ============================ [ LOCALS    ] ====================================================== */
STATIC AppModeType	  AppMode;

STATIC FUNC(void,MEM_TASK_INIT) Init ( void )
{
	TaskType task;
	/* task context set-up */
	for(task=0;task<TASK_NUM;task++)
	{
		P2CONST(task_declare_t, AUTOMATIC,LOCAL) declare = &TaskList[task];
        task_context.push_back( new arTask(task,declare) );
	}

    /* task auto-start up */
	for (task=0; task < TASK_NUM; task++)
	{
		P2CONST(task_declare_t, AUTOMATIC,LOCAL) declare = &TaskList[task];
		assert(task == declare->priority);
		if ( (TRUE == declare->autostart) &&
			 (0u   != (declare->app_mode&AppMode)) )
		{
			ActivateTask(task);
		}
	}

    OsAlarmInit();
    OsResourceInit();
}
/* ============================ [ FUNCTIONS ] ====================================================== */
arTask::arTask(TaskType task_id,const task_declare_t* declare,QObject *parent) :
    QThread(parent)
{
    this->task_id = task_id;
    this->declare = declare;
    activation = 0;
    setEvent = 0;

    start(QThread::HighestPriority);
}
bool arTask::Activate(void)
{
	bool reslut = true;
	if(activation < declare->max_activation)
	{
		activation ++ ;
	}
	else
	{
		reslut = false;
	}
	return reslut;
}

bool arTask::WaitEvent(EventMaskType eventMask)
{
	while(0 == (eventMask&setEvent))
	{
		msleep(1);
	}
	return true;
}
bool arTask::ClearEvent(void)
{
	setEvent = 0;
	return true;
}
bool arTask::SetEvent(EventMaskType eventMask)
{
	setEvent |= eventMask;
	return true;
}

void arTask::run()
{
	while(true)
	{
		while((activation>0) && (declare!=NULL))
		{
			ClearEvent();
			declare->main(task_id);
			activation--;
		}
		msleep(1);
	}
	assert(0);
}

FUNC(StatusType,MEM_ActivateTask)  ActivateTask ( TaskType TaskID )
{
    StatusType ercd = E_OK;

    if(TaskID < TASK_NUM)
    {
		if(task_context[TaskID]->Activate())
		{
			// pass
		}
		else
		{
			ercd = E_OS_LIMIT;
		}
    }
    else
    {
    	ercd = E_OS_ID;
    }
    return ercd;
}
FUNC(StatusType,MEM_TerminateTask) TerminateTask ( void )
{
	StatusType ercd = E_OK;


	return ercd;
}

FUNC(void,MEM_StartOS)              StartOS       ( AppModeType Mode )
{
	AppMode = Mode;

    Init();
}

TASK(OsIdle)
{

}

}} /* namespace autosar */

