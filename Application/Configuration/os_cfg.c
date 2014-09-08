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
/* ============================ [ INCLUDES ] ====================================================== */
#include "Os.h"
/* ============================ [ MACROS   ] ====================================================== */
/* ============================ [ TYPES    ] ====================================================== */
/* ============================ [ DATAS    ] ====================================================== */
CONST(task_declare_t,AUTOMATIC)  TaskList[TASK_NUM] =
{
    DeclareTask(OsIdle,			TRUE,	OSDEFAULTAPPMODE),
    DeclareTask(SchM_Startup,	TRUE,	OSDEFAULTAPPMODE),
    DeclareTask(SchM_BswService,FALSE,	0				)
};


CONST(alarm_declare_t,AUTOMATIC) AlarmList[ALARM_NUM] =
{
        DeclareAlarm(SchM_BswService)
};
/* ============================ [ DECLARES ] ====================================================== */
/* ============================ [ LOCALS   ] ====================================================== */
/* ============================ [ FNCTIONS ] ====================================================== */
TASK(OsIdle)
{
}

ALARM(SchM_BswService)
{
    (void)ActivateTask(TASKID_SchM_BswService);
}


