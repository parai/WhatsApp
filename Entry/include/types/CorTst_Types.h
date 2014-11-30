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
 * Version: AUTOSAR 4.2.0
 * Generated by arxml.py
 */
#ifndef CORTST_TYPES_H
#define CORTST_TYPES_H

#ifdef __cplusplus
namespace autosar {
extern "C" {
#endif
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* This container specifies configuration parameters to select individual tests for foreground
 *  mode and background mode. The availability is hardware and implementation specific.
 */
typedef struct
{
/* Enable/Disables core address test. */
	boolean CorTstAddress ;
/* Enable/Disables core ALU test. */
	boolean CorTstAlu ;
/* Enable/Disables core cache test. */
	boolean CorTstCache ;
/* Enable/Disables core interrupt test */
	boolean CorTstInterrupt ;
/* Enable/Disables core memory interface test */
	boolean CorTstMemoryIf ;
/* Enable/Disables core MPU test */
	boolean CorTstMpu ;
/* Enable/Disables core register test */
	boolean CorTstRegister ;
} CorTst_SelectType ;

/* Multiple Configuration Set Container, defines background mode. */
typedef struct
{
	CorTst_SelectType* CorTstSelect ;
} CorTst_BackgroundConfigSetType ;

typedef struct
{
/* Adds / removes the service CorTst_Abort() from the code. */
	boolean CorTstAbortApi ;
/* Adds / removes the service CorTst_GetCurrentStatus() from the code. */
	boolean CorTstGetCurrentStatus ;
/* Adds / removes the service CorTst_GetFgndSignature() from the code. */
	boolean CorTstGetFgndSignature ;
/* Adds / removes the service CorTst_GetSignature() from the code. */
	boolean CorTstGetSignature ;
/* Adds / removes the service CorTst_GetState() from the code. */
	boolean CorTstGetStateApi ;
/* Adds / removes the service CorTst_Start() from the code. */
	boolean CorTstStartApi ;
/* Adds / removes the service CorTst_GetVersionInfo() from the code. */
	boolean CorTstVersionInfoApi ;
} CorTst_ConfigApiServicesType ;

/* Container for the references to DemEventParameter elements which shall be invoked using the
 *  API Dem_ReportErrorStatus in case the corresponding error occurs. The EventId is taken from
 *  the referenced DemEventParameter's DemEventId value. The standardized errors are provided in
 *  the container and can be extended by vendor specific error references.
 */
typedef struct
{
} CorTst_DemEventParameterRefsType ;

/* Multiple Configuration Set Container , defines foreground mode. */
typedef struct
{
	CorTst_SelectType* CorTstSelect ;
/* This is the Id of this specific foreground test configuration. The value shall be used in the
 *  call to the API CorTst_Start(CorTst_TestIdFgndType TestId).
 */
	uint32 CorTstTestIdFgnd ;
} CorTst_ForegroundConfigSetType ;

typedef struct
{
/* Switch for enabling the development error detection. */
	boolean CorTstDevErrorDetect ;
/* This parameter holds the number of test configurations available for the foreground tests as
 *  defined in this configuration.
 */
	uint32 CorTstFgndTestNumber ;
/* Switch to indicate that the notification is supported. */
	boolean CorTstNotificationSupported ;
/* Defines the end value of the Test Interval Id. */
	uint32 CorTstTestIntervalIdEndValue ;
/* Switch for enabling test result comparison within the Core test driver. In this mode a core
 *  test result OK or NOTOK shall not be calculated from the core test driver. Within core test
 *  driver no comparison against the reference value is processed.
 */
	boolean CorTstTestResultMode ;
} CorTst_GeneralType ;

/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __cplusplus
}}  /* name space */
#endif /* CORTST_TYPES_H */

