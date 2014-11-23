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
#ifdef __cplusplus
namespace autosar {
#endif
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
CONST(task_declare_t,AUTOMATIC)  TaskList[TASK_NUM] =
{
    DeclareTask(OsIdle,			   TRUE,	0xFFFFFFFFUL     , 1),
    DeclareTask(SchM_Startup,	   TRUE,	OSDEFAULTAPPMODE , 1),
    DeclareTask(SchM_BswService,   FALSE,	0				 , 10),
    DeclareTask(Rte_Runnable10ms,  FALSE,	0				 , 2),
    DeclareTask(Rte_Runnable20ms,  FALSE,	0				 , 2),
    DeclareTask(Rte_Runnable50ms,  FALSE,	0				 , 2),
    DeclareTask(Rte_Runnable100ms, FALSE,	0				 , 2),
    DeclareTask(Rte_Runnable200ms, FALSE,	0				 , 2),
    DeclareTask(Rte_Runnable1s, FALSE,	0				 , 2),

};


CONST(alarm_declare_t,AUTOMATIC) AlarmList[ALARM_NUM] =
{
	DeclareAlarm(SchM_BswService),
	DeclareAlarm(Rte_Runnable10ms),
	DeclareAlarm(Rte_Runnable20ms),
	DeclareAlarm(Rte_Runnable50ms),
	DeclareAlarm(Rte_Runnable100ms),
	DeclareAlarm(Rte_Runnable200ms),
	DeclareAlarm(Rte_Runnable1s)
};
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __cplusplus
} /* namespace autosar */
#endif
