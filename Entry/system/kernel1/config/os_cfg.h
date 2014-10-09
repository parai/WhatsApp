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
#define TASKID_OsIdle		   	0
#define TASKID_SchM_Startup    	1
#define TASKID_SchM_BswService 	2
#define TASK_NUM               	3

#define ALARMID_SchM_BswService		0
#define ALARM_NUM                   1

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

ALARMCALLBACK(SchM_BswService);

#ifdef __cplusplus
}} //namespace
#endif
#endif /* OS_CFG_H_ */
