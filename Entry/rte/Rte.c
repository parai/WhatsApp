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
#include "Os.h"
#include "CanIf.h"
#ifdef __cplusplus
namespace autosar {
#endif

/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */

ALARMCALLBACK(Rte_Runnable10ms){(void)ActivateTask(TASKID_Rte_Runnable10ms);}
ALARMCALLBACK(Rte_Runnable20ms){(void)ActivateTask(TASKID_Rte_Runnable20ms);}
ALARMCALLBACK(Rte_Runnable50ms){(void)ActivateTask(TASKID_Rte_Runnable50ms);}
ALARMCALLBACK(Rte_Runnable100ms){(void)ActivateTask(TASKID_Rte_Runnable100ms);}
ALARMCALLBACK(Rte_Runnable200ms){(void)ActivateTask(TASKID_Rte_Runnable200ms);}
ALARMCALLBACK(Rte_Runnable1s){(void)ActivateTask(TASKID_Rte_Runnable1s);}

TASK(Rte_Runnable10ms){}
TASK(Rte_Runnable20ms){}
TASK(Rte_Runnable50ms){}
TASK(Rte_Runnable100ms){}
TASK(Rte_Runnable200ms){}
TASK(Rte_Runnable1s)
{

}

/* This is my example, don't care about it */
Std_ReturnType Rte_Start(void)
{
	SetRelAlarm(ALARMID_Rte_Runnable10ms, 10,10);
	SetRelAlarm(ALARMID_Rte_Runnable20ms, 10,20);
	SetRelAlarm(ALARMID_Rte_Runnable50ms, 10,50);
	SetRelAlarm(ALARMID_Rte_Runnable100ms,10,100);
	SetRelAlarm(ALARMID_Rte_Runnable200ms,10,200);
	SetRelAlarm(ALARMID_Rte_Runnable1s,   10,10000);
}
Std_ReturnType Rte_Stop(void)
{
	CancelAlarm(ALARMID_Rte_Runnable10ms);
	CancelAlarm(ALARMID_Rte_Runnable20ms);
	CancelAlarm(ALARMID_Rte_Runnable50ms);
	CancelAlarm(ALARMID_Rte_Runnable100ms);
	CancelAlarm(ALARMID_Rte_Runnable200ms);
	CancelAlarm(ALARMID_Rte_Runnable1s);
}

#ifdef __cplusplus
} /* namespace autosar */
#endif
