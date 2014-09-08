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
#ifndef OS_H_
#define OS_H_
#ifdef __cplusplus
extern "C" {
#endif
/* ============================ [ INCLUDES ] ====================================================== */
#include "Std_Types.h"

/* ============================ [ MACROS   ] ====================================================== */
#define E_OS_ACCESS 			(StatusType)1
#define	E_OS_CALLEVEL 			(StatusType)2
#define	E_OS_ID					(StatusType)3
#define	E_OS_LIMIT 				(StatusType)4
#define	E_OS_NOFUNC 			(StatusType)5
#define	E_OS_RESOURCE 			(StatusType)6
#define	E_OS_STATE 				(StatusType)7
#define	E_OS_VALUE 				(StatusType)8

#define OSDEFAULTAPPMODE        (AppModeType)1

#define SUSPENDED				(TaskStateType)0x01
#define READY					(TaskStateType)0x02
#define RUNNING					(TaskStateType)0x04
#define WAITING					(TaskStateType)0x08

#define TICK_MAX       			(TickType)-1

#define TASK(_task) 			void TaskMain##_task  ( void )
#define ALARM(_alarm)	    	void AlarmMain##_alarm ( void )

/* ============================ [ TYPES    ] ====================================================== */
typedef uint8 					StatusType;
typedef uint32_t 				EventMaskType;
typedef EventMaskType *			EventMaskRefType;
typedef uint16_t 				TaskType;
typedef TaskType *				TaskRefType;
typedef uint8					TaskStateType;
typedef TaskStateType *			TaskStateRefType;
typedef uint32                  AppModeType;	/*! each bit is a mode */

typedef uint32					TickType;
typedef TickType*				TickRefType;

typedef uint8					AlarmType;
typedef struct
{
	TickType MaxAllowedValue;
	TickType TickPerBase;
	TickType MinCycle;
} 								AlarmBaseType;

typedef AlarmBaseType *			AlarmBaseRefType;

#include "os_i.h"
/* ============================ [ DATAS    ] ====================================================== */
/* ============================ [ DECLARES ] ====================================================== */
/* ============================ [ LOCALS   ] ====================================================== */
/* ============================ [ FNCTIONS ] ====================================================== */
FUNC(void,MEM_OS_TICK) 				OsTick 		  ( void );
FUNC(StatusType,MEM_GetAlarmBase) 	GetAlarmBase  ( AlarmType AlarmId, AlarmBaseRefType Info );
FUNC(StatusType,MEM_GetAlarm) 		GetAlarm	  ( AlarmType AlarmId, TickRefType Tick );
FUNC(StatusType,MEM_SetRelAlarm) 	SetRelAlarm   ( AlarmType AlarmId, TickType Increment, TickType Cycle );
FUNC(StatusType,MEM_SetAbsAlarm) 	SetAbsAlarm   ( AlarmType AlarmId, TickType Increment, TickType Cycle );
FUNC(StatusType,MEM_CancelAlarm)    CancelAlarm   ( AlarmType AlarmId );
FUNC(TickType,MEM_GetOsTick)        GetOsTick     ( void );
FUNC(StatusType,MEM_ACTIVATE_TASK) 	ActivateTask  ( TaskType TaskId);
FUNC(StatusType,MEM_ACTIVATE_TASK) 	TerminateTask ( void );
FUNC(StatusType,MEM_Schedule) 		Schedule      ( void );
FUNC(StatusType,MEM_GetTaskID) 		GetTaskID     ( TaskRefType TaskID );
FUNC(StatusType,MEM_GetTaskState) 	GetTaskState  ( TaskType TaskID,TaskStateRefType State );
FUNC(void,MEM_StartOS)              StartOS       ( AppModeType Mode );
#ifdef __cplusplus
}
#endif
#endif /* OS_H_ */
