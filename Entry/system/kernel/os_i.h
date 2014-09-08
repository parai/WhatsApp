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
#ifndef OS_I_H
#define OS_I_H
/* ============================ [ INCLUDES ] ====================================================== */
#include "Os.h"
#include "os_i.h"

/* ============================ [ MACROS   ] ====================================================== */
#define DeclareTask(Name,Autostart,AppMode)		\
    {											\
        .main = TaskMain##Name,							\
        .priority = TASKID_##Name,				\
        .autostart = Autostart,					\
        .app_mode = AppMode						\
    }

#define DeclareAlarm(Name)						\
    {											\
        .main = AlarmMain##Name						\
    }

/* ============================ [ TYPES    ] ====================================================== */
/*! extended OS types */
typedef void         (*task_main_t)(void);
typedef void         (*alarm_main_t)(void);
typedef uint8 		   task_priority_t;

typedef struct
{
    task_main_t    	main;
    task_priority_t priority;	/*! priority also represent the task id, the same as TaskType */
    bool            autostart;
    AppModeType     app_mode;	/*! means task runnable modes */
}task_declare_t;

typedef struct
{
    alarm_main_t main;
    /* No Autostart support */
}alarm_declare_t;

#include "os_cfg.h"
/* ============================ [ DATAS    ] ====================================================== */
/* ============================ [ DECLARES ] ====================================================== */
/* ============================ [ LOCALS   ] ====================================================== */
/* ============================ [ FNCTIONS ] ====================================================== */

#endif // OS_I_H
