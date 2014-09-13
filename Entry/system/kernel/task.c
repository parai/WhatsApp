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
/**
 python:
cstr = 'PRIVATE uint8 tableUnMap[256] = {'
for i in range(0,256):
    if(i%16==0):
        cstr += '\n\t'
    for pos in [7,6,5,4,3,2,1,0]:
        if((i&(1<<pos)) != 0):
            cstr += '%s,'%(pos)
            break
        elif(pos==0):
            cstr += '%s,'%(pos)
cstr += '};\n\n'
print cstr
*/
STATIC uint8 tableUnMap[256] = {
    0,0,1,1,2,2,2,2,3,3,3,3,3,3,3,3,
    4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
    6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
    6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
    6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
    6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
    7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
    7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
    7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
    7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
    7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
    7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
    7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
    7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
};
STATIC uint8 readyGrp;
STATIC uint8 readyTable[8];

STATIC TaskType    			CurrentTask;
STATIC AppModeType				AppMode;
/* ============================ [ DECLARES ] ====================================================== */
extern FUNC(void,MEM_OsAlarmInit)    OsAlarmInit ( void );
extern FUNC(void,MEM_OsResourceInit) OsResourceInit ( void );

STATIC FUNC(void,MEM_TASK_INIT)         Init   ( void );
STATIC FUNC(TaskType,MEM_TASK_GETBIT)   GetBit ( void  );
STATIC FUNC(void,MEM_TASK_SETBIT)       SetBit ( uint8 priority );
STATIC FUNC(bool,MEM_TASK_ISBITSET)     IsBitSet( uint8 priority );
STATIC FUNC(void,MEM_TASK_CLEARBIT)     ClearBit( uint8 priority );
/* ============================ [ LOCALS   ] ====================================================== */

STATIC FUNC(void,MEM_TASK_INIT) Init ( void )
{
    CurrentTask = 0;    // Idle is ready always
    readyGrp = 0;
    memset(readyTable,0,8);

    {	/* task auto-start up */
        TaskType task;
        for (task=0; task < TASK_NUM; task++)
        {
            P2CONST(task_declare_t, AUTOMATIC,LOCAL) declare = &TaskList[task];
            assert(task == declare->priority);
            if ( (TRUE == declare->autostart) &&
                 (0u   != (declare->app_mode&AppMode)) )
            {
                SetBit(task);
            }
        }
    }

    OsAlarmInit();
    OsResourceInit();
}
STATIC FUNC(TaskType,MEM_TASK_GETBIT) GetBit ( void  )
{
    uint8 result = 0;	/* the OsIdle must be with priority 0 */
    if( readyGrp != 0x00u)
    {
        uint8 y = tableUnMap[readyGrp];
        uint8 x = tableUnMap[readyTable[y]];
        result  = ((y<<3)+x);
    }
    else
    {
        /* only os Idle is ready */
    }

    return result;
}
STATIC FUNC(void,MEM_TASK_SETBIT) SetBit(uint8 priority)
{
    uint8 y = priority>>3;
    uint8 x = priority&7;
    readyGrp      |= 1<<y;
    readyTable[y] |= 1<<x;
}

STATIC FUNC(bool,MEM_TASK_ISBITSET) IsBitSet(uint8 priority)
{
    bool isBitSet = FALSE;
    uint8 y = priority>>3;
    uint8 x = priority&7;

    if( (readyGrp & (1<<y)) && (readyTable[y] & (1<<x)) )
    {
        isBitSet = TRUE;
    }
    return isBitSet;
}
STATIC FUNC(void,MEM_TASK_CLEARBIT) ClearBit(uint8 priority)
{
    uint8 y = priority>>3;
    uint8 x = priority&7;
    readyTable[y] &= ~(1<<x);
    if(0u == readyTable[y])
    {
        readyGrp &= ~( 1<<y );
    }
}
/* ============================ [ FNCTIONS ] ====================================================== */
FUNC(StatusType,MEM_ActivateTask)  ActivateTask ( TaskType TaskID )
{
    StatusType ercd = E_OK;

    if(TaskID < TASK_NUM)
    {
        SetBit(TaskID);
    }
    else
    {
        ercd = E_OS_ID;
    }
    return ercd;
}
FUNC(StatusType,MEM_TerminateTask) TerminateTask ( void )
{
	StatusType ercd = E_OK;


	return ercd;
}

FUNC(StatusType,MEM_Schedule) 		Schedule      ( void )
{
    TaskType task;
    P2CONST(task_declare_t,AUTOMATIC,LOCAL) declare;
    StatusType ercd = E_OK;

    if ( E_OK == GetResource(RES_SCHEDULER) )
    {
        task = GetBit();
        assert(task < TASK_NUM);
        declare = &TaskList[task];

        if (task > CurrentTask)
        {	/* task with high priority */
            TaskType previous = CurrentTask;	/* link it in the dynamic ram queue */

            CurrentTask = task;		/* preempt */
            SetBit(previous);       /* put this low priority task to ready map again */
            ClearBit(CurrentTask);	/* pop up the higher ready task from ready map */

            ReleaseResource(RES_SCHEDULER);

            declare->main();

            GetResource(RES_SCHEDULER);

            ClearBit(previous);     /* resume the low priority task  from ready map */
            CurrentTask = previous;
        }
        else
        {
            if(0 == CurrentTask)
            {	/* no task is ready, execute idle*/
                ReleaseResource(RES_SCHEDULER);

                declare->main();

                GetResource(RES_SCHEDULER);
            }
        }

        ReleaseResource(RES_SCHEDULER);
    }
    else
    {
        ercd = E_OS_RESOURCE;   /* Scheduler only supports the check of RES_SCHEDULER */
    }

    return ercd;
}
FUNC(StatusType,MEM_GetTaskID) 		GetTaskID     ( TaskRefType TaskID )
{
	StatusType ercd = E_OK;

    *TaskID = CurrentTask;

	return ercd;
}
FUNC(StatusType,MEM_GetTaskState) 	GetTaskState  ( TaskType TaskID,TaskStateRefType State )
{
	StatusType ercd = E_OK;

    if (TaskID == CurrentTask )
    {
        *State = RUNNING;
    }
    else if(IsBitSet(TaskID))
    {
        *State = READY;
    }
    else
    {
        *State = SUSPENDED;
    }
	return ercd;
}

FUNC(void,MEM_StartOS)              StartOS       ( AppModeType Mode )
{
	AppMode = Mode;

    Init();
}

TASK(OsIdle)
{

}

