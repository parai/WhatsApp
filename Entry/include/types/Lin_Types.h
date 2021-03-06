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
#ifndef LIN_TYPES_H
#define LIN_TYPES_H

/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
#ifdef __cplusplus
namespace autosar {
extern "C" {
#endif
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* This container contains the configuration (parameters) of the LIN Controller(s). */
typedef struct Lin_ChannelType_tag
{
/* Specifies the baud rate of the LIN channel */
	uint16 LinChannelBaudRate ;
/* Identifies the LIN channel. Replaces LIN_CHANNEL_INDEX_NAME from the LIN SWS. */
	uint16 LinChannelId ;
/* Specifies if the LIN hardware channel supports wake up functionality */
	boolean LinChannelWakeupSupport ;
/* Reference to the LIN clock source configuration, which is set in the MCU driver configuration. */
/* /AUTOSAR/EcucDefs/Mcu/McuModuleConfiguration/McuClockSettingConfig/McuClockReferencePoint */
	Mcu_ClockReferencePointType* LinClockRef ;
/* This parameter contains a reference to the Wakeup Source for this controller as defined in the
 *  ECU State Manager.
 */
/* /AUTOSAR/EcucDefs/EcuM/EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource */
	EcuM_WakeupSourceType* LinChannelEcuMWakeupSource ;
} Lin_ChannelType ;

/* Container for the references to DemEventParameter elements which shall be invoked using the
 *  API Dem_ReportErrorStatus API in case the corresponding error occurs. The EventId is taken
 *  from the referenced DemEventParameter's DemEventId value. The standardized errors are provided
 *  in the container and can be extended by vendor specific error references.
 */
typedef struct Lin_DemEventParameterRefsType_tag
{
/* Reference to the DemEventParameter which shall be issued when the error "Timeout caused by hardware
 *  error" has occured. If the reference is not configured the error shall be reported as DET error.
 */
/* /AUTOSAR/EcucDefs/Dem/DemConfigSet/DemEventParameter */
	Dem_EventParameterType* LIN_E_TIMEOUT ;
} Lin_DemEventParameterRefsType ;

/* This container contains the parameters related to each LIN Driver Unit. */
typedef struct Lin_GeneralType_tag
{
/* Switches the Development Error Detection and Notification ON or OFF. */
	boolean LinDevErrorDetect ;
/* Specifies the InstanceId of this module instance. If only one instance is present it shall have
 *  the Id 0.
 */
	uint8 LinIndex ;
/* Specifies the maximum number of loops for blocking function until a timeout is raised in short
 *  term wait loops
 */
	uint16 LinTimeoutDuration ;
/* Switches the Lin_GetVersionInfo function ON or OFF. */
	boolean LinVersionInfoApi ;
} Lin_GeneralType ;

/* This container contains the global configuration parameter of the Lin driver. This container
 *  is a MultipleConfigurationContainer, i.e. this container and its sub-containers exit once per
 *  configuration set.
 */
typedef struct Lin_GlobalConfigType_tag
{
	Lin_ChannelType* LinChannel ;
	Lin_DemEventParameterRefsType* LinDemEventParameterRefs ;
} Lin_GlobalConfigType ;

/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __cplusplus
}}  /* name space */
#endif
#endif /* LIN_TYPES_H */

