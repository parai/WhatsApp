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
#ifndef STBM_TYPES_H
#define STBM_TYPES_H

/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
#ifdef __cplusplus
namespace autosar {
extern "C" {
#endif
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* Entry address of the time-base specific callout routine which shall be invoked by the StbM for
 *  gathering the current time-base value.
 */
/* TODO: 
 * typedef void (*StbM_GlobalTimeProviderCalloutType)(void);
 */

/* Entry address of the time-base specific callout routine which shall be invoked by the StbM for
 *  gathering the current time-base status.
 */
/* TODO: 
 * typedef void (*StbM_SyncStateProviderCalloutType)(void);
 */

/* Entry address of the time-base specific callout routine which shall be invoked by the StbM for
 *  gathering the current time-base tick duration.
 */
/* TODO: 
 * typedef void (*StbM_TickDurationProviderCalloutType)(void);
 */

/* Entry address of the customer specific call-back routine which shall be invoked by the StbM
 *  periodically for time value propagation.
 */
/* TODO: 
 * typedef void (*StbM_GlobalTimeCustomerCallbackType)(void);
 */

/* Entry address of the customer specific call-back routine which shall be invoked by the StbM
 *  when state changes occur.
 */
/* TODO: 
 * typedef void (*StbM_SyncStateCustomerCallbackType)(void);
 */

/* Container for the references to DemEventParameter elements which shall be invoked using the
 *  API Dem_ReportErrorStatus API in case the corresponding error occurs. The EventId is taken
 *  from the referenced DemEventParameter's DemEventId value. The standardized errors are provided
 *  in the container and can be extended by vendor specific error references.
 */
typedef struct
{
/* Reference to the DemEventParameter which shall be issued when the error "StbM initialization
 *  failed" has occured.
 */
/* /AUTOSAR/EcucDefs/Dem/DemConfigSet/DemEventParameter */
	Dem_EventParameterType* STBM_E_INIT_FAILED ;
/* Reference to the DemEventParameter which shall be issued when the error "API request integrity
 *  failed" has occured.
 */
/* /AUTOSAR/EcucDefs/Dem/DemConfigSet/DemEventParameter */
	Dem_EventParameterType* STBM_E_INTEGRITY_FAILED ;
/* Reference to the DemEventParameter which shall be issued when the error "API request failed"
 *  has occured.
 */
/* /AUTOSAR/EcucDefs/Dem/DemConfigSet/DemEventParameter */
	Dem_EventParameterType* STBM_E_REQ_FAILED ;
} StbM_DemEventParameterRefsType ;

/* This container holds the general parameters of the Synchronized Time-base Manager */
typedef struct
{
/* Enables/Disables the StbM_GetAbsoluteTime API. */
	boolean StbMAbsoluteTimeApi ;
/* Switch for enabling the development error detection. */
	boolean StbMDevErrorDetect ;
/* Defines the upper range of the type "StbM_TickType". */
	uint16 StbMTickTypeRange ;
/* Activate/Deactivate the version information API (StbM_GetVersionInfo). True: version information
 *  API activated False: version information API deactivated.
 */
	boolean StbMVersionInfo ;
} StbM_GeneralType ;

/* Synchronized time.base collects the information about a specific time-base provider within the
 *  system.
 */
typedef struct
{
/* In case the synchronized time-base is derived from the local time, this container can be omitted.
 *  For this case, the StbM achieves the current time-base value by calling the OS interface "GetCounterValue"
 *  with the respective OSCounter configured via the ECUC param "StbMLocalTimeRef".
 */
	StbM_GlobalTimeProviderCalloutType StbMGlobalTimeProviderCallout ;
/* In case the synchronized time-base is derived from the local time, this container can be omitted.
 *  For this case, the state is always "STBM_STATE_SYNC".
 */
	StbM_SyncStateProviderCalloutType StbMSyncStateProviderCallout ;
/* Identification of a synchronized time-base via a unique identifier. */
	uint16 StbMSynchronizedTimeBaseIdentifier ;
/* In case the synchronized time-base is derived from the local time, this container can be omitted.
 *  For this case, the StbM achieves the tick duration by configuring an alarm which uses the HW
 *  counter configured via the ECUC param "StbMLocalTimeRef". Note: The tick duration of the local
 *  time will not change during runtime.
 */
	StbM_TickDurationProviderCalloutType StbMTickDurationProviderCallout ;
/* Optional reference to the FlexRay cluster. */
	/*TODO:FLEXRAY-CLUSTER*/void* StbMFlexRayClusterRef ;
/* Optional reference to the Ttcan cluster. */
	/*TODO:TTCAN-CLUSTER*/void* StbMTtcanClusterRef ;
/* Optional sub container in case a local time shall be accessed. */
/* In case this subcontainer is used, the destinated OS counter has to be configured properly,
 *  meaning:
 *                                         - the counter is directly driven by a HW timer 
 *                                         - the counter's OsCounterTicksPerBase set to one tick
 *  in ms.
 */
/* /AUTOSAR/EcucDefs/Os/OsCounter */
	Os_CounterType* StbMLocalTimeRef ;
} StbM_SynchronizedTimeBaseType ;

/* The triggered customer is directliy triggered by the Synchronized Time-base Manager by getting
 *  synchronized with the current (global) definition of time and passage of time.
 */
typedef struct
{
/* This configuration is only valid if the explicit OS ScheduleTable is NOT defined as triggered
 *  customer (via the reference "StbMOSScheduleTableRef").
 */
	StbM_GlobalTimeCustomerCallbackType StbMGlobalTimeCustomerCallback ;
/* This configuration is only valid if the explicit OS ScheduleTable is NOT defined as triggered
 *  customer (via the reference "StbMOSScheduleTableRef").
 */
	StbM_SyncStateCustomerCallbackType StbMSyncStateCustomerCallback ;
/* True: the customer will only be triggered when the related time-base is synchronized.
 *                                         False: the customer will be triggered with the local
 *  time-base when no synchronization for the related time-base is established.
 */
/* Activate/Deactivate the triggering of the customer in case the related time-base (StbmSynchronizedTimeBaseRef)
 *  is not synchronized.
 */
	boolean StbMTriggerInSyncState ;
/* The period is documented in microseconds. */
/* The triggering period of the triggered customer, called by the StbM_MainFunction. */
	uint32 StbMTriggeredCustomerPeriod ;
/* Optional reference to synchronized OS ScheduleTables. */
/* This configuration is only valid if the triggered customer shall be an OS ScheduleTable. In
 *  this case, the OS ScheduleTable will be explicitely synchronized by the StbM.
 */
/* /AUTOSAR/EcucDefs/Os/OsScheduleTable */
	Os_ScheduleTableType* StbMOSScheduleTableRef ;
/* Mandatory reference to the required synchronized time-base. */
/* /AUTOSAR/EcucDefs/StbM/StbMSynchronizedTimeBase */
	StbM_SynchronizedTimeBaseType* StbMSynchronizedTimeBaseRef ;
} StbM_TriggeredCustomerType ;

/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __cplusplus
}}  /* name space */
#endif
#endif /* STBM_TYPES_H */

