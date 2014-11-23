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
#ifndef OS_CFG_H_
#define OS_CFG_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Os.h"
#ifdef __cplusplus
namespace autosar {
extern "C" {
#endif
/* ============================ [ MACROS    ] ====================================================== */
#define TASKID_OsIdle		   	 0
#define TASKID_SchM_Startup    	 1
#define TASKID_SchM_BswService 	 2
#define TASKID_Rte_Runnable10ms  3
#define TASKID_Rte_Runnable20ms  4
#define TASKID_Rte_Runnable50ms  5
#define TASKID_Rte_Runnable100ms 6
#define TASKID_Rte_Runnable200ms 7
#define TASKID_Rte_Runnable1s    8
#define TASK_NUM               	 9

#define ALARMID_SchM_BswService	  0
#define ALARMID_Rte_Runnable10ms  1
#define ALARMID_Rte_Runnable20ms  2
#define ALARMID_Rte_Runnable50ms  3
#define ALARMID_Rte_Runnable100ms 4
#define ALARMID_Rte_Runnable200ms 5
#define ALARMID_Rte_Runnable1s    6
#define ALARM_NUM                 7

#define RES_CAN                 (RES_SCHEDULER + 1)
#define RES_LCD                 (RES_SCHEDULER + 2)
#define RES_NUMBER              (RES_SCHEDULER + 3)
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
extern CONST(task_declare_t,AUTOMATIC)  TaskList[TASK_NUM];
extern CONST(alarm_declare_t,AUTOMATIC) AlarmList[ALARM_NUM];
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
TASK(OsIdle);
TASK(SchM_Startup);
TASK(SchM_BswService);
TASK(Rte_Runnable10ms);
TASK(Rte_Runnable20ms);
TASK(Rte_Runnable50ms);
TASK(Rte_Runnable100ms);
TASK(Rte_Runnable200ms);
TASK(Rte_Runnable1s);

ALARMCALLBACK(SchM_BswService);
ALARMCALLBACK(Rte_Runnable10ms);
ALARMCALLBACK(Rte_Runnable20ms);
ALARMCALLBACK(Rte_Runnable50ms);
ALARMCALLBACK(Rte_Runnable100ms);
ALARMCALLBACK(Rte_Runnable200ms);
ALARMCALLBACK(Rte_Runnable1s);

#ifdef __cplusplus
}} //namespace
#endif
#endif /* OS_CFG_H_ */
