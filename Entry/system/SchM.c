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
#include "EcuM.h"
#include "Rte.h"

#ifdef __cplusplus
namespace autosar {
#endif
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */

TASK(SchM_Startup)
{
    SetRelAlarm(ALARMID_SchM_BswService,10,5);

    EcuM_StartupTwo();

	TerminateTask();
}

ALARMCALLBACK(SchM_BswService)
{
   (void)ActivateTask(TASKID_SchM_BswService);
}

TASK(SchM_BswService)
{
	TerminateTask();
}

#ifdef __cplusplus
} /* namespace autosar */
#endif
