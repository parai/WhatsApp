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
#include "Can.h"
#include "CanIf.h"
#include "Det.h"

#ifdef __cplusplus
namespace autosar {
#endif
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
STATIC FUNC(void,MEM_EcuM_AL_DriverInitZero) EcuM_AL_DriverInitZero (void)
{
	Det_Init();
	Det_Start();
}

STATIC FUNC(void,MEM_EcuM_AL_DriverInitZero) EcuM_AL_DriverInitOne ( const EcuM_ConfigType *ConfigPtr )
{
    Can_Init(&Can_Config);
}

STATIC FUNC(void,MEM_EcuM_AL_DriverInitZero) EcuM_AL_DriverInitTwo ( const EcuM_ConfigType *ConfigPtr )
{
	CanIf_Init(&CanIf_Config);
}

STATIC FUNC(void,MEM_EcuM_AL_DriverInitZero) EcuM_AL_DriverInitThree ( const EcuM_ConfigType *ConfigPtr )
{

}
/* ============================ [ FUNCTIONS ] ====================================================== */
void StartupHook(void)
{

}
void ShutdownHook(StatusType ercd)
{
    if( E_OK != ercd)
    {

    }
}
void PreTaskHook(void)
{
}
void PostTaskHook(void)
{
}
void ErrorHook(StatusType ercd)
{
    if( E_OK != ercd)
    {
    }
    else
    {

    }
}

FUNC(void, MEM_EcuM_Init) EcuM_Init ( void )
{

	EcuM_AL_DriverInitZero();
	EcuM_AL_DriverInitOne(NULL);

	StartOS(OSDEFAULTAPPMODE);
}

FUNC(void,MEM_EcuM_StartupTwo) EcuM_StartupTwo ( void )
{
	EcuM_AL_DriverInitTwo(NULL);

	EcuM_AL_DriverInitThree(NULL);

	Rte_Start();
}

#ifdef __cplusplus
} /* namespace autosar */
#endif
