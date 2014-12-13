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
#ifndef MCU_TYPES_H
#define MCU_TYPES_H

/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
#ifdef __cplusplus
namespace autosar {
extern "C" {
#endif
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* This container defines a reference point in the Mcu Clock tree. It defines the frequency which
 *  then can be used by other modules as an input value. Lower multiplictiy is 1, as even in the
 *  simpliest case (only one frequency is used), there is one frequency to be defined.
 */
typedef struct
{
/* This is the frequency for the specific instance of the McuClockReferencePoint container. It
 *  shall be given in Hz.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 McuClockReferencePointFrequency ;
} Mcu_ClockReferencePointType ;

/* This container contains the configuration (parameters) for the Clock settings of the MCU.  Please
 *  see MCU031 for more information on the MCU clock settings.
 */
typedef struct
{
	Mcu_ClockReferencePointType* McuClockReferencePoint ;
/* The Id of this McuClockSettingConfig to be used as argument for the API call "Mcu_InitClock". */
	uint8 McuClockSettingId ;
} Mcu_ClockSettingConfigType ;

/* Container for the references to DemEventParameter elements which shall be invoked using the
 *  API Dem_ReportErrorStatus API in case the corresponding error occurs. The EventId is taken
 *  from the referenced DemEventParameter's DemEventId value. The standardized errors are provided
 *  in the container and can be extended by vendor specific error references.
 */
typedef struct
{
/* Reference to configured DEM event to report "Clock source failure". */
/* /AUTOSAR/EcucDefs/Dem/DemConfigSet/DemEventParameter */
	Dem_EventParameterType* MCU_E_CLOCK_FAILURE ;
} Mcu_DemEventParameterRefsType ;

/* This container contains the configuration (parameters) for the Mode setting of the MCU.  Please
 *  see MCU035 for more information on the MCU mode settings.
 */
typedef struct
{
/* The parameter represents the MCU Mode settings. */
	uint8 McuMode ;
} Mcu_ModeSettingConfType ;

/* This container contains the configuration (parameters) for the RAM Sector setting. Please see
 *  MCU030 for more information on RAM sec-tor settings.
 */
typedef struct
{
/* This parameter shall represent the Data pre-setting to be initialized */
	uint8 McuRamDefaultValue ;
/* This parameter shall represent the MCU RAM section base address */
	uint32 McuRamSectionBaseAddress ;
/* This parameter represents the MCU RAM Section size in bytes. */
	uint32 McuRamSectionSize ;
} Mcu_RamSectorSettingConfType ;

/* Enables/Disables clock failure notification. In case this feature is not supported by HW the
 *  setting should be disabled.
 */
typedef enum
{
	MCU_CLOCKSRCFAILURENOTIFICATION_DISABLED,
	MCU_CLOCKSRCFAILURENOTIFICATION_ENABLED
} Mcu_ClockSrcFailureNotificationType ;

/* This container contains the configuration for the different type of reset reason that can be
 *  retrieved from Mcu_GetResetReason Api.
 */
typedef struct
{
/* The parameter represents the different type of reset that a Micro supports. This parameter is
 *  referenced by the parameter EcuMResetReason in the ECU State manager module.
 */
	uint8 McuResetReason ;
} Mcu_ResetReasonConfType ;

/* This container contains the configuration (parameters) of the MCU driver. */
typedef struct
{
/* Pre-processor switch for enabling the development error detection and reporting. */
	boolean McuDevErrorDetect ;
/* (e.g. If the H/W does not support the functionality, this parameter can be used to disable the
 *  Api).
 */
/* Pre-processor switch to enable/disable the API Mcu_GetRamState. */
	boolean McuGetRamStateApi ;
/* If this parameter is set to FALSE, the clock initialization has to be disabled from the MCU
 *  driver. This concept applies when there are some write once clock registers and a bootloader
 *  is present. If this parameter is set to TRUE, the MCU driver is responsible of the clock initialization.
 */
	boolean McuInitClock ;
/* This parameter shall be set True, if the H/W does not have a PLL or the PLL circuitry is enabled
 *  after the power on without S/W intervention. In this case MCU_DistributePllClock has to be
 *  disabled and  MCU_GetPllStatus has to return MCU_PLL_STATUS_UNDEFINED. Otherwise this parameters
 *  has to be set False
 */
	boolean McuNoPll ;
/* Pre-processor switch to enable / disable the use of the function Mcu_PerformReset() */
	boolean McuPerformResetApi ;
/* Pre-processor switch to enable / disable the API to read out the modules version information. */
	boolean McuVersionInfoApi ;
} Mcu_GeneralConfigurationType ;

/* This container contains the configuration (parameters) of the MCU driver */
typedef struct
{
	Mcu_ClockSettingConfigType* McuClockSettingConfig ;
	Mcu_DemEventParameterRefsType* McuDemEventParameterRefs ;
	Mcu_ModeSettingConfType* McuModeSettingConf ;
	Mcu_RamSectorSettingConfType* McuRamSectorSettingConf ;
	Mcu_ClockSrcFailureNotificationType McuClockSrcFailureNotification ;
/* calculationFormula = Number of configured McuModeSettingConf */
/* This parameter shall represent the number of Modes available for the MCU. */
	uint8 McuNumberOfMcuModes ;
/* calculationFormula = Number of configured McuRamSectorSettingConf */
/* This parameter shall represent the number of RAM sectors available for the MCU. */
	uint32 McuRamSectors ;
/* This parameter relates to the MCU specific reset configuration. This applies to the function
 *  Mcu_PerformReset, which performs a microcontroller reset using the hardware feature of the
 *  microcontroller.
 */
	uint8 McuResetSetting ;
} Mcu_ModuleConfigurationType ;

/* Container holding all MCU specific published information parameters */
typedef struct
{
	Mcu_ResetReasonConfType* McuResetReasonConf ;
} Mcu_PublishedInformationType ;

/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __cplusplus
}}  /* name space */
#endif
#endif /* MCU_TYPES_H */

