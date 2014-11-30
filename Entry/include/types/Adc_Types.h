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
#ifndef ADC_TYPES_H
#define ADC_TYPES_H

#ifdef __cplusplus
namespace autosar {
extern "C" {
#endif
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* In case of active limit checking: defines which conversion values are taken into account related
 *  to the boarders defined with AdcChannelLowLimit and AdcChannelHighLimit.
 */
typedef enum
{
	ADC_RANGE_ALWAYS,
	ADC_RANGE_BETWEEN,
	ADC_RANGE_NOT_BETWEEN,
	ADC_RANGE_NOT_OVER_HIGH,
	ADC_RANGE_NOT_UNDER_LOW,
	ADC_RANGE_OVER_HIGH,
	ADC_RANGE_UNDER_LOW,
} Adc_ChannelRangeSelectType ;

/* Upper reference voltage source for each channel. */
/* typedef enum
 * {
 * 	TODO: maybe specific to vendor as no LITERALS in arxml.
 * } Adc_ChannelRefVoltsrcHighType ;
 * 
 * 
 */
/* Lower reference voltage source for each channel. */
/* typedef enum
 * {
 * 	TODO: maybe specific to vendor as no LITERALS in arxml.
 * } Adc_ChannelRefVoltsrcLowType ;
 * 
 * 
 */
/* This container contains the channel configuration (parameters) depending on the hardware capability.
 */
typedef struct
{
/* ImplementationType: Adc_ConversionTimeType */
/* Configuration of conversion time, i.e. the time during which the analogue value is converted
 *  into digital representation, (in clock cycles) for each channel, if supported by hardware.
 */
	uint64 AdcChannelConvTime ;
/* High limit - used for limit checking. */
	uint64 AdcChannelHighLimit ;
/* ImplementationType: Adc_ChannelType */
/* This parameter defines the assignment of the channel to the physical ADC  hardware channel. */
	uint16 AdcChannelId ;
/* Enables or disables limit checking for an ADC channel. */
	boolean AdcChannelLimitCheck ;
/* Low limit - used for limit checking. */
	uint64 AdcChannelLowLimit ;
/* Implementation Type: Adc_ChannelRangeSelectType */
	Adc_ChannelRangeSelectType AdcChannelRangeSelect ;
/* Enumeration literals are defined vendor specific. */
	Adc_ChannelRefVoltsrcHighType AdcChannelRefVoltsrcHigh ;
/* Enumeration literals are defined vendor specific. */
	Adc_ChannelRefVoltsrcLowType AdcChannelRefVoltsrcLow ;
/* ImplementationType: Adc_ResolutionType */
/* Channel resolution in bits. */
	uint8 AdcChannelResolution ;
/* ImplementationType: Adc_SamplingTimeType */
/* Configuration of sampling time, i.e. the time during which the value is sampled, (in clock cycles)
 *  for each channel, if supported by hardware.
 */
	uint64 AdcChannelSampTime ;
} Adc_ChannelType ;

/* Type of access mode to group conversion results. */
typedef enum
{
	ADC_ACCESS_MODE_SINGLE,
	ADC_ACCESS_MODE_STREAMING,
} Adc_GroupAccessModeType ;

/* Type of conversion mode supported by the driver. */
typedef enum
{
	ADC_CONV_MODE_CONTINUOUS,
	ADC_CONV_MODE_ONESHOT,
} Adc_GroupConversionModeType ;

/* Replacement mechanism, which is used on ADC group level, if a group conversion is interrupted
 *  by a group which has a higher priority.
 */
typedef enum
{
	ADC_GROUP_REPL_ABORT_RESTART,
	ADC_GROUP_REPL_SUSPEND_RESUME,
} Adc_GroupReplacementType ;

/* Type of source event that starts a group conversion. */
typedef enum
{
	ADC_TRIGG_SRC_HW,
	ADC_TRIGG_SRC_SW,
} Adc_GroupTriggSrcType ;

/* Configures on which edge of the hardware trigger signal the driver should react, i.e. start
 *  the conversion (only if supported by the ADC hardware).
 */
typedef enum
{
	ADC_HW_TRIG_BOTH_EDGES,
	ADC_HW_TRIG_FALLING_EDGE,
	ADC_HW_TRIG_RISING_EDGE,
} Adc_HwTrigSignalType ;

/* Callback function for each group */
/* TODO: 
 * typedef void (*Adc_NotificationType)(void);
 */

/* Configure streaming buffer as "linear buffer" (i.e. the ADC Driver stops the conversion as soon
 *  as the stream buffer is full) or as "ring buffer" (wraps around if the end of the stream buffer
 *  is reached).
 */
typedef enum
{
	ADC_STREAM_BUFFER_CIRCULAR,
	ADC_STREAM_BUFFER_LINEAR,
} Adc_StreamingBufferModeType ;

/* This container contains the Group configuration (parameters). */
typedef struct
{
/* ImplementationType: Adc_GroupAccessModeType */
	Adc_GroupAccessModeType AdcGroupAccessMode ;
/* ImplementationType: Adc_GroupConvModeType */
	Adc_GroupConversionModeType AdcGroupConversionMode ;
/* ImplementationType: Adc_GroupType */
/* Numeric ID of the group. This parameter is the symbolic name to be used on the API. This symbolic
 *  name allows accessing Channel Group data. This value will be assigned to the symbolic name
 *  derived of the AdcGroup container shortName.
 */
	uint16 AdcGroupId ;
/* ImplementationType: Adc_GroupPriorityType */
/* Priority level of the AdcGroup. */
	uint8 AdcGroupPriority ;
/* ImplementationType: Adc_GroupReplacementType */
	Adc_GroupReplacementType AdcGroupReplacement ;
/* ImplementationType: Adc_TriggerSourceType */
	Adc_GroupTriggSrcType AdcGroupTriggSrc ;
/* ImplementationType: Adc_HwTriggerSignalType */
	Adc_HwTrigSignalType AdcHwTrigSignal ;
/* ImplementationType: Adc_HwTriggerTimerType */
/* Reload value of the ADC module embedded timer (only if supported by ADC hardware). */
	uint64 AdcHwTrigTimer ;
	Adc_NotificationType AdcNotification ;
/* ImplementationType: Adc_StreamBufferModeType */
	Adc_StreamingBufferModeType AdcStreamingBufferMode ;
/* Note: in single access mode this parameter assumes value 1, since only one sample per channel
 *  is processed.
 * 
 *                                                         ImplementationType: Adc_StreamNumSampleType
 */
/* Number of ADC values to be acquired per channel in streaming access mode. */
	uint8 AdcStreamingNumSamples ;
} Adc_GroupType ;

/* The ADC module specific clock input for the conversion  unit can */
/* typedef enum
{
	TODO: maybe specific to vendor as no LITERALS in arxml.
} Adc_ClockSourceType ;

 */
/* Description: Numeric ID of the HW Unit. This symbolic name allows accessing Hw Unit data. Enumeration
 *  literals are defined vendor specific.
 */
/* typedef enum
{
	TODO: maybe specific to vendor as no LITERALS in arxml.
} Adc_HwUnitIdType ;

 */
/* This container contains the Driver configuration (parameters) depending on grouping of channels */
typedef struct
{
/* The organization of this data structure could contain dependencies to the microcontroller so
 *  this is left up to the implementer and its location is left up to the configuration. 
 *                                                 Note: Since a AdcChannel can be part of several
 *  AdcGroups, this container is not realized as a subcontainer of AdcGroup but instead as a subcontainer
 *  of AdcHwUnit.
 */
	Adc_ChannelType* AdcChannel ;
	Adc_GroupType* AdcGroup ;
/* statically be configured to select different clock sources if provided by 
 *                                                 hardware. Enumeration literals are defined vendor
 *  specific.
 */
	Adc_ClockSourceType AdcClockSource ;
	Adc_HwUnitIdType AdcHwUnitId ;
/* ImplementationType: Adc_PrescaleType */
/* Optional ADC module specific clock prescale factor, if supported by hardware. */
	uint16 AdcPrescale ;
} Adc_HwUnitType ;

/* Determines whether a priority mechanism is available for prioritization of the conversion requests
 *  and if available, the type of prioritization mechanism. The selection applies for groups with
 *  trigger source software and trigger source hardware. Two
 */
typedef enum
{
	ADC_PRIORITY_HW,
	ADC_PRIORITY_HW_SW,
	ADC_PRIORITY_NONE,
} Adc_PriorityImplementationType ;

/* Alignment of ADC raw results in ADC result buffer (left/right alignment). */
typedef enum
{
	ADC_ALIGN_LEFT,
	ADC_ALIGN_RIGHT,
} Adc_ResultAlignmentType ;

/* This is the base container that contains the post-build selectable configuration parameters */
typedef struct
{
/* This container could contain HW specific parameters which are not defined in the Standardized
 *  Module Definition. They must be added in the Vendor Specific Module Definition.
 */
	Adc_HwUnitType* AdcHwUnit ;
} Adc_ConfigSetType ;

/* General configuration (parameters) of the ADC Driver software module. */
typedef struct
{
/* true: Adc_DeInit() can be used.
 *                                         false: Adc_DeInit() can not be used.
 */
/* Adds / removes the service Adc_DeInit() from the code. */
	boolean AdcDeInitApi ;
/* true: Enabled.
                                        false: Disabled. */
/* Switches the Development Error Detection and Notification ON or OFF. */
	boolean AdcDevErrorDetect ;
/* Enables or disables limit checking feature in the ADC driver. */
	boolean AdcEnableLimitCheck ;
/* Note: If priority mechanism is enabled, queuing mechanism is always active and the parameter
 *  ADC_ENABLE_QUEUING is not evaluated.
 *                                         true: Enabled.
 *                                         false: Disabled.
 */
/* Determines, if the queuing mechanism is active in case of priority mechanism disabled. */
	boolean AdcEnableQueuing ;
/* true: Adc_StartGroupConversion() and Adc_StopGroupConversion() can be used.
 *                                         false: Adc_StartGroupConversion() and Adc_StopGroupConversion()
 *  can not be used.
 */
/* Adds / removes the services Adc_StartGroupConversion() and Adc_StopGroupConversion() from the
 *  code.
 */
	boolean AdcEnableStartStopGroupApi ;
/* true: Enabled.
                                        false: Disabled. */
/* Determines, if the group notification mechanism (the functions to enable and disable the notifications)
 *  is available at runtime.
 */
	boolean AdcGrpNotifCapability ;
/* true: Adc_EnableHardwareTrigger() and Adc_DisableHardwareTrigger() can be used.
 *                                         false: Adc_EnableHardwareTrigger() and Adc_DisableHardwareTrigger()
 *  can not be used.
 */
/* Adds / removes the services Adc_EnableHardwareTrigger() and Adc_DisableHardwareTrigger() from
 *  the code.
 */
	boolean AdcHwTriggerApi ;
/* types of prioritization mechanism can be selected. The hardware prioritization mechanism (AdcPriorityHw)
 *  uses the ADC hardware features for prioritization of the software conversion requests and hardware
 *  trigger signals for groups with trigger source hardware. The mixed hardware and software prioritization
 *  mechanism (AdcPriorityHwSw) uses the ADC hardware features for prioritization of ADC hardware
 *  trigger for groups with trigger source hardware and a software implemented prioritization mechanism
 *  for groups with trigger source software. The group priorities for software triggered groups
 *  are typically configured with lower priority levels than the group priorities for hardware
 *  triggered groups.
 * 
 *                                         ImplementationType: Adc_PriorityImplementationType
 */
	Adc_PriorityImplementationType AdcPriorityImplementation ;
/* true: Adc_ReadGroup() can be used.
 *                                         false: Adc_ReadGroup() can not be used.
 */
/* Adds / removes the service Adc_ReadGroup() and from the code. */
	boolean AdcReadGroupApi ;
/* Implementation Type: Adc_ResultAlignmentType */
	Adc_ResultAlignmentType AdcResultAlignment ;
/* true: Adc_GetVersionInfo() can be used.
 *                                         false: Adc_GetVersionInfor() can not be used.
 */
/* Adds / removes the service Adc_GetVersionInfo() from the code. */
	boolean AdcVersionInfoApi ;
} Adc_GeneralType ;

/* Additional published parameters not covered by CommonPublishedInformation container. */
typedef struct
{
/* Information whether the result value of the ADC driver has sign information (true) or not (false).
 *  If the result shall be interpreted as signed value it shall apply to C-language rules.
 */
	boolean AdcChannelValueSigned ;
/* Information whether the first channel of an ADC Channel group can be configured (false) or is
 *  fixed (true) to a value determined by the ADC HW Unit.
 */
	boolean AdcGroupFirstChannelFixed ;
/* Maximum Channel resolution in bits (does not specify accuracy). */
	uint8 AdcMaxChannelResolution ;
} Adc_PublishedInformationType ;

/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __cplusplus
}}  /* name space */
#endif /* ADC_TYPES_H */

