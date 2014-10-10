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
#ifndef OS_CONFIG_H_H
#define OS_CONFIG_H_H
/* ============================ [ INCLUDES  ] ====================================================== */
#include "osek_kernel.h"

#ifdef __cplusplus
namespace autosar { extern "C" {
#endif
/* ============================ [ MACROS    ] ====================================================== */
#define TASKID_OsIdle 						0
#define TASKID_SchM_Startup 				1
#define TASKID_SchM_BswService 				2
#define TASK_NUM               			    3

#define ALARMID_SchM_BswService         0
#define ALARM_NUM						1

#define ID_OS_TICK						0
#define COUNTER_NUM    					1

#define RES_CAN                 (RES_SCHEDULER + 1)
#define RES_NUM                 (RES_SCHEDULER + 2)

//#define BASIC_STATUS

/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
extern TASK(OsIdle);
extern TASK(SchM_Startup);
extern TASK(SchM_BswService);

extern ALARMCALLBACK(SchM_BswService);
#ifdef __cplusplus
}}  /* name space */
#endif
#endif  /* OS_CONFIG_H_H */
