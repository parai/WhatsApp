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
STATIC	TickType				OsTickCounter;

STATIC TickType			 	AlarmTick[ALARM_NUM];
STATIC TickType			 	AlarmPeriod[ALARM_NUM];
/* ============================ [ DECLARES ] ====================================================== */
/* ============================ [ LOCALS   ] ====================================================== */
/* ============================ [ FNCTIONS ] ====================================================== */
FUNC(void,MEM_OsTick) OsTick ( void )
{
	AlarmType AlarmId;
	OsTickCounter ++;

	for(AlarmId=0; AlarmId<ALARM_NUM; AlarmId++)
	{
		if(AlarmTick[AlarmId] > 0)
		{
			AlarmTick[AlarmId]--;
			if(0u == AlarmTick[AlarmId])
			{
				AlarmList[AlarmId].main();
				AlarmTick[AlarmId] = AlarmPeriod[AlarmId];
			}
		}
	}
}

FUNC(StatusType,MEM_GetAlarmBase) GetAlarmBase ( AlarmType AlarmId, AlarmBaseRefType Info )
{
	assert(AlarmId<ALARM_NUM);

    Info[0].maxallowedvalue = TICK_MAX;
    Info[0].ticksperbase     = 1u;
    Info[0].mincycle        = 1u;

	return E_OK;
}

FUNC(StatusType,MEM_GetAlarm) GetAlarm(AlarmType AlarmId, TickRefType Tick)
{
	assert(AlarmId<ALARM_NUM);

	Tick[0] = AlarmTick[AlarmId];

	return E_OK;
}

FUNC(StatusType,MEM_SetRelAlarm) SetRelAlarm ( AlarmType AlarmId, TickType Increment, TickType Cycle )
{
	assert(AlarmId<ALARM_NUM);

	AlarmTick[AlarmId] = Increment;
	AlarmPeriod[AlarmId] = Cycle;

	return E_OK;
}

FUNC(StatusType,MEM_SetAbsAlarm) SetAbsAlarm ( AlarmType AlarmId, TickType Start, TickType Cycle )
{
	assert(AlarmId<ALARM_NUM);

	if (OsTickCounter < Start)
	{
		Start = Start - OsTickCounter;
	}
	else
	{
		Start = TICK_MAX - OsTickCounter + Start + 1;
	}

	AlarmTick[AlarmId] = Start;
	AlarmPeriod[AlarmId] = Cycle;

	return E_OK;
}

FUNC(StatusType,MEM_CancelAlarm) CancelAlarm ( AlarmType AlarmId )
{
	assert(AlarmId<ALARM_NUM);

	AlarmTick[AlarmId] = 0;
	AlarmPeriod[AlarmId] = 0;

	return E_OK;
}

FUNC(TickType,MEM_GetOsTick) GetOsTick( void )
{
	return OsTickCounter;
}

FUNC(void,MEM_OsAlarmInit) OsAlarmInit ( void )
{
    memset(AlarmTick,0,sizeof(AlarmTick));
    memset(AlarmPeriod,0,sizeof(AlarmPeriod));
}
