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
/* ============================ [ INCLUDES ] ====================================================== */
#include "Std_Types.h"

#ifdef __cplusplus
namespace autosar {
extern "C" {
#endif
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

#define SUSPENDED			    ((StatusType) 0)
#define RUNNING				    ((StatusType) 1)
#define READY				    ((StatusType) 2)
#define WAITING				    ((StatusType) 3)

#define TICK_MAX       			(TickType)-1
#define INVALID_TASK            (TaskType)-1
/*
 *  Macros for declare a object 
 */
//#define DeclareTask(TaskName)		extern const TaskType TaskName
//#define DeclareResource(ResName)	extern const ResourceType ResName
//#define DeclareEvent(EventName)		extern const EventMaskType EventName
//#define DeclareAlarm(AlarmName)		extern const AlarmType AlarmName
//#define DeclareCounter(CounterName)	extern const CounterType CounterName

/*
 *  Macro for declare Task/Alarm/ISR Entry
 */
#define TASKNAME(TaskName)	TaskMain##TaskName
#define TASK(TaskName)		void TaskMain##TaskName(void)
#define ISRNAME(ISRName)	ISRMain##ISRName
#define ISR(ISRName)		void ISRMain##ISRName(void)
#define ALARMCALLBACKNAME(AlarmCallBackName) 	\
							AlarmMain##AlarmCallBackName
#define ALARMCALLBACK(AlarmCallBackName)	\
							void AlarmMain##AlarmCallBackName(void)
							
#define RES_SCHEDULER           (ResourceType)0 /* default resources for OS */


/*
 *  OS service API IDs
 */
#define OSServiceId_ActivateTask				((OSServiceIdType) 0)
#define OSServiceId_TerminateTask				((OSServiceIdType) 1)
#define OSServiceId_ChainTask					((OSServiceIdType) 2)
#define OSServiceId_Schedule					((OSServiceIdType) 3)
#define OSServiceId_GetTaskID					((OSServiceIdType) 4)
#define OSServiceId_GetTaskState				((OSServiceIdType) 5)
#define OSServiceId_EnableAllInterrupts			((OSServiceIdType) 6)
#define OSServiceId_DisableAllInterrupts		((OSServiceIdType) 7)
#define OSServiceId_ResumeAllInterrupts			((OSServiceIdType) 8)
#define OSServiceId_SuspendAllInterrupts		((OSServiceIdType) 9)
#define OSServiceId_ResumeOSInterrupts			((OSServiceIdType) 10)
#define OSServiceId_SuspendOSInterrupts			((OSServiceIdType) 11)
#define OSServiceId_GetResource					((OSServiceIdType) 12)
#define OSServiceId_ReleaseResource				((OSServiceIdType) 13)
#define OSServiceId_SetEvent					((OSServiceIdType) 14)
#define OSServiceId_ClearEvent					((OSServiceIdType) 15)
#define OSServiceId_GetEvent					((OSServiceIdType) 16)
#define OSServiceId_WaitEvent					((OSServiceIdType) 17)
#define OSServiceId_GetAlarmBase				((OSServiceIdType) 18)
#define OSServiceId_GetAlarm					((OSServiceIdType) 19)
#define OSServiceId_SetRelAlarm					((OSServiceIdType) 20)
#define OSServiceId_SetAbsAlarm					((OSServiceIdType) 21)
#define OSServiceId_CancelAlarm					((OSServiceIdType) 22)
#define OSServiceId_GetActiveApplicationMode	((OSServiceIdType) 23)
#define OSServiceId_StartOS						((OSServiceIdType) 24)
#define OSServiceId_ShutdownOS					((OSServiceIdType) 25)
#define OSServiceId_SignalCounter				((OSServiceIdType) 26)

/* ============================ [ TYPES    ] ====================================================== */
typedef uint8 					StatusType;
typedef uint32   				EventMaskType;
typedef EventMaskType *			EventMaskRefType;
typedef uint16  				TaskType;
typedef TaskType *				TaskRefType;
typedef uint8					TaskStateType;
typedef TaskStateType *			TaskStateRefType;
typedef uint32                  AppModeType;	/*! each bit is a mode */

typedef uint32					TickType;
typedef TickType*				TickRefType;
typedef uint8			        OSServiceIdType;	/* OS service API ID */
typedef uint8			        IsrType;			/* ISR ID */
typedef uint8			        CounterType;		/* Counter ID */

typedef uint8					AlarmType;
typedef struct
{
	TickType maxallowedvalue;
	TickType ticksperbase;
	TickType mincycle;
} 								AlarmBaseType;
typedef AlarmBaseType *			AlarmBaseRefType;

typedef uint8                   ResourceType;

typedef union {
	TaskType			tskid;
	TaskRefType			p_tskid;
	TaskStateRefType	p_state;
	ResourceType		resid;
	EventMaskType		mask;
	EventMaskRefType	p_mask;
	AlarmType			almid;
	AlarmBaseRefType	p_info;
	TickRefType			p_tick;
	TickType			incr;
	TickType			cycle;
	TickType			start;
	AppModeType			mode;
	CounterType			cntid;
} _ErrorHook_Par;

#include "os_i.h"
/* ============================ [ DATAS    ] ====================================================== */
extern OSServiceIdType	_errorhook_svcid;
extern _ErrorHook_Par	_errorhook_par1, _errorhook_par2, _errorhook_par3;
/* ============================ [ DECLARES ] ====================================================== */
/* ============================ [ LOCALS   ] ====================================================== */
/* ============================ [ FNCTIONS ] ====================================================== */
FUNC(void,MEM_OS_TICK) 				 OsTick 		  ( void );
FUNC(StatusType,MEM_GetAlarmBase) 	 GetAlarmBase    ( AlarmType AlarmId, AlarmBaseRefType Info );
FUNC(StatusType,MEM_GetAlarm) 		 GetAlarm	     ( AlarmType AlarmId, TickRefType Tick );
FUNC(StatusType,MEM_SetRelAlarm) 	 SetRelAlarm     ( AlarmType AlarmId, TickType Increment, TickType Cycle );
FUNC(StatusType,MEM_SetAbsAlarm) 	 SetAbsAlarm     ( AlarmType AlarmId, TickType Increment, TickType Cycle );
FUNC(StatusType,MEM_CancelAlarm)     CancelAlarm     ( AlarmType AlarmId );
FUNC(TickType,MEM_GetOsTick)         GetOsTick       ( void );
FUNC(StatusType,MEM_ACTIVATE_TASK) 	 ActivateTask    ( TaskType TaskId);
FUNC(StatusType,MEM_ACTIVATE_TASK) 	 TerminateTask   ( void );
FUNC(StatusType,MEM_Schedule) 		 Schedule        ( void );
FUNC(StatusType,MEM_GetTaskID) 		 GetTaskID       ( TaskRefType TaskID );
FUNC(StatusType,MEM_GetTaskState) 	 GetTaskState    ( TaskType TaskID,TaskStateRefType State );
FUNC(void,MEM_StartOS)               StartOS         ( AppModeType Mode );
FUNC(StatusType,MEM_GetResource)     GetResource     ( ResourceType ResID );
FUNC(StatusType,MEM_ReleaseResource) ReleaseResource ( ResourceType ResID );

extern void EnableAllInterrupts(void);
extern void DisableAllInterrupts(void);
extern void ResumeAllInterrupts(void);
extern void SuspendAllInterrupts(void);
extern void ResumeOSInterrupts(void);
extern void SuspendOSInterrupts(void);

extern AppModeType GetActiveApplicationMode(void);
extern void ShutdownOS(StatusType ercd);

extern StatusType SetEvent(TaskType tskid, EventMaskType mask);
extern StatusType ClearEvent(EventMaskType mask);
extern StatusType GetEvent(TaskType tskid, EventMaskRefType p_mask);
extern StatusType WaitEvent(EventMaskType mask);

extern StatusType SignalCounter(CounterType cntid);

/*
 *  Hooks
 */
extern void ErrorHook(StatusType ercd);
extern void PreTaskHook(void);
extern void PostTaskHook(void);
extern void StartupHook(void);
extern void ShutdownHook(StatusType ercd);
#ifdef __cplusplus
}}  // name space
#endif
#endif /* OS_H_ */
