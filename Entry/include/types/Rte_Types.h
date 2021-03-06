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
#ifndef RTE_TYPES_H
#define RTE_TYPES_H

/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
#include "Os.h"
#ifdef __cplusplus
namespace autosar {
extern "C" {
#endif
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* Introduce a schedule point by explicitly calling Os Schedule service after the execution of
 *  the ExecutableEntity.  The Rte generator is allowed to optimize several consecutive calls to
 *  Os schedule into one single call if the ExecutableEntity executions in between have been skipped.
 */
typedef enum
{
	RTE_OSSCHEDULEPOINT_CONDITIONAL,
	RTE_OSSCHEDULEPOINT_NONE,
	RTE_OSSCHEDULEPOINT_UNCONDITIONAL
} Rte_OsSchedulePointType ;

/* Maps a BswSchedulableEntity onto one OsTask based on the activating BswEvent. */
typedef struct Rte_BswEventToTaskMappingType_tag
{
/* Activation offset in seconds. */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 RteBswActivationOffset ;
/* This parameter shall not be set to true when the mapped BswEvent refers to a BswSchedulableEntitiy
 *  which minimumStartInterval attribute is > 0.
 */
/* When RteBswImmediateRestart is set to true the BswSchedulableEntitiy shall be immediately re-started
 *  after termination if it was activated by this BswEvent while it was already started.
 */
	boolean RteBswImmediateRestart ;
/* For periodic activation this is the order of execution.
 *                                                 For event driver activation this is the order
 *  of evaluation which actual BswSchedulableEntity has to be executed.
 */
/* Each BswSchedulableEntity activation mapped to an OsTask has a specific position within the
 *  task execution.
 */
	uint16 RteBswPositionInTask ;
/* The absence of this parameter is interpreted as "NONE".
 * 
 *                                                 It shall be considered an invalid configuration
 *  if the task is preemptable and the value of this parameter is not set to "NONE" or the parameter
 *  is absent.
 */
	Rte_OsSchedulePointType RteOsSchedulePoint ;
/* Reference to the BswEvent which is pointing to the BswSchedulableEntity being mapped. This allows
 *  a fine grained mapping of BswSchedulableEntites based on the activating BswEvent.
 */
	/*TODO:BSW-EVENT*/void* RteBswEventRef ;
/* Reference to the OsTask the BswSchedulableEntity activated by the RteBswEventRef is mapped to. */
/* If no reference to the OsTask is specified the BswSchedulableEntity activated by this BswEvent
 *  is executed in the context of the caller.
 */
/* /AUTOSAR/EcucDefs/Os/OsTask */
    struct Os_TaskType_tag* RteBswMappedToTaskRef ;
/* If an OsAlarm is used to activate the OsTask this BswEvent is mapped to it shall be referenced
 *  here.
 */
/* /AUTOSAR/EcucDefs/Os/OsAlarm */
    struct Os_AlarmType_tag* RteBswUsedOsAlarmRef ;
/* If an OsEvent is used to activate the OsTask this BswEvent is mapped to it shall be referenced
 *  here.
 */
/* /AUTOSAR/EcucDefs/Os/OsEvent */
    struct Os_EventType_tag* RteBswUsedOsEventRef ;
/* If an OsScheduleTableExpiryPoint is used to activate the OsTask this BswEvent is mapped to it
 *  shall be referenced here.
 */
/* /AUTOSAR/EcucDefs/Os/OsScheduleTable/OsScheduleTableExpiryPoint */
    struct Os_ScheduleTableExpiryPointType_tag* RteBswUsedOsSchTblExpiryPointRef ;
} Rte_BswEventToTaskMappingType ;

/* To be used implementation mechanism for the specified ExclusiveArea. */
typedef enum
{
	RTE_EXCLUSIVEAREAIMPLMECHANISM_ALL_INTERRUPT_BLOCKING,
	RTE_EXCLUSIVEAREAIMPLMECHANISM_COOPERATIVE_RUNNABLE_PLACEMENT,
	RTE_EXCLUSIVEAREAIMPLMECHANISM_OS_INTERRUPT_BLOCKING,
	RTE_EXCLUSIVEAREAIMPLMECHANISM_OS_RESOURCE
} Rte_ExclusiveAreaImplMechanismType ;

/* Represents one ExclusiveArea of one BswImplementation. Used to specify the implementation means
 *  of this ExclusiveArea.
 */
typedef struct Rte_BswExclusiveAreaImplType_tag
{
	Rte_ExclusiveAreaImplMechanismType RteExclusiveAreaImplMechanism ;
/* Reference to the ExclusiveArea for which the implementation mechanism shall be specified. */
	/*TODO:EXCLUSIVE-AREA*/void* RteBswExclusiveAreaRef ;
/* Optional reference to an OsResource in case RteExclusiveAreaImplMechanism is configured to OS_RESOURCE
 *  for this ExclusiveArea.
 */
/* /AUTOSAR/EcucDefs/Os/OsResource */
    struct Os_ResourceType_tag* RteBswExclusiveAreaOsResourceRef ;
} Rte_BswExclusiveAreaImplType ;

/* Defines the configuration of Inter Basic Software Module Entity Triggering */
typedef struct Rte_BswExternalTriggerConfigType_tag
{
/* The queue is implemented by the RTE. A value greater or equal to 1 requests an queued behavior.
 *  
 *                                                 Setting the value of RteTriggerSourceQueueLength
 *  to 0 requests an none queued implementation of the trigger communication.
 * 
 *                                                 If there is no RteBswTriggerSourceQueueLength
 *  configured for a Trigger Emitter the default value of 0 applies as well.
 */
/* Length of trigger queue on the trigger source side. */
	uint32 RteBswTriggerSourceQueueLength ;
/* Reference to a Trigger instance in the role releasedTrigger of the related BSW Module instance. */
/* The referenced Trigger has to belong to the same BSW Module instance as the RteBswModuleInstance
 *  owning this parameter configures.
 */
	/*TODO:TRIGGER*/void* RteBswTriggerSourceRef ;
} Rte_BswExternalTriggerConfigType ;

/* Defines the configuration of internal Basic Software Module Entity Triggering */
typedef struct Rte_BswInternalTriggerConfigType_tag
{
/* The queue is implemented by the RTE. A value greater or equal to 1 requests an queued behavior.
 *  
 *                                                 Setting the value of RteTriggerSourceQueueLength
 *  to 0 requests an none queued implementation of the trigger communication.
 * 
 *                                                 If there is no RteBswTriggerSourceQueueLength
 *  configured for a Trigger Emitter the default value of 0 applies as well.
 */
	uint32 RteBswTriggerSourceQueueLength ;
/* Reference to a BswInternalTriggeringPoint of the related BSW Module instance. */
/* The referenced BswInternalTriggeringPoint has to belong to the same BSW Module instance as the
 *  RteBswModuleInstance owning this parameter configures.
 */
	/*TODO:BSW-INTERNAL-TRIGGERING-POINT*/void* RteBswTriggerSourceRef ;
} Rte_BswInternalTriggerConfigType ;

/* Defines the connection between one requiredModeGroup of this BSW Module instance and one providedModeGroup
 *  instance.
 */
typedef struct Rte_BswRequiredModeGroupConnectionType_tag
{
/* References the providedModeGroupPrototype to which this requiredModeGroup shall be connected. */
	/*TODO:MODE-DECLARATION-GROUP-PROTOTYPE*/void* RteBswProvidedModeGroupRef ;
/* References requiredModeGroupPrototype which shall be connected to the providedModeGroupPrototype. */
	/*TODO:MODE-DECLARATION-GROUP-PROTOTYPE*/void* RteBswRequiredModeGroupRef ;
/* Reference to the RteBswModuleInstance configuration container which identifies the instance
 *  of the BSW Module.
 */
/* Used with the RteBswProvidedModeGroupRef to unambiguously identify the ModeDeclarationGroupPrototype
 *  instance.
 */
/* /AUTOSAR/EcucDefs/Rte/RteBswModuleInstance */
    struct Rte_BswModuleInstanceType_tag* RteBswProvidedModeGrpModInstRef ;
} Rte_BswRequiredModeGroupConnectionType ;

/* Defines the connection between one requiredTrigger of this BSW Module instance and one releasedTrigger
 *  instance.
 */
typedef struct Rte_BswRequiredTriggerConnectionType_tag
{
/* References the releasedTrigger to which this requiredTrigger shall be connected. */
	/*TODO:TRIGGER*/void* RteBswReleasedTriggerRef ;
/* References one requiredTrigger which shall be connected to the releasedTrigger. */
	/*TODO:TRIGGER*/void* RteBswRequiredTriggerRef ;
/* Reference to the RteBswModuleInstance configuration container which identifies the instance
 *  of the BSW Module.
 */
/* Used with the RteBswReleasedTriggerRef to unambiguously identify the Trigger instance. */
/* /AUTOSAR/EcucDefs/Rte/RteBswModuleInstance */
    struct Rte_BswModuleInstanceType_tag* RteBswReleasedTriggerModInstRef ;
} Rte_BswRequiredTriggerConnectionType ;

/* The RTE generator shall have the option to switch off support for calibration for generated
 *  RTE code. This option shall influence complete RTE code at once.
 */
typedef enum
{
	RTE_CALIBRATIONSUPPORT_DOUBLE_POINTERED,
	RTE_CALIBRATIONSUPPORT_INITIALIZED_RAM,
	RTE_CALIBRATIONSUPPORT_NONE,
	RTE_CALIBRATIONSUPPORT_SINGLE_POINTERED
} Rte_CalibrationSupportType ;

/* Switch between the two available generation modes of the RTE generator. */
typedef enum
{
	RTE_GENERATIONMODE_COMPATIBILITY_MODE,
	RTE_GENERATIONMODE_VENDOR_MODE
} Rte_GenerationModeType ;

/* Defines whether the return value of RTE APIs is based on RTE-IOC interaction or RTE-COM interaction.
 */
typedef enum
{
	RTE_COM,
	RTE_IOC
} Rte_IocInteractionReturnValueType ;

/* Switch between the two available optimization modes of the RTE generator. */
typedef enum
{
	RTE_OPTIMIZATIONMODE_MEMORY,
	RTE_OPTIMIZATIONMODE_RUNTIME
} Rte_OptimizationModeType ;

/* The RTE generator shall enable VFB tracing for a given hook function when there is a #define
 *  in the RTE configuration header file for the hook function name and tracing is globally enabled.
 */
/* TODO: */
typedef void (*Rte_VfbTraceFunctionType)(void);

/* Definition of the initialization strategy applicable for the SectionInitializationPolicys selected
 *  by RteSectionInitializationPolicy.
 */
typedef enum
{
	RTE_INITIALIZATION_STRATEGY_AT_DATA_DECLARATION,
	RTE_INITIALIZATION_STRATEGY_AT_DATA_DECLARATION_AND_PARTITION_RESTART,
	RTE_INITIALIZATION_STRATEGY_AT_RTE_START_AND_PARTITION_RESTART,
	RTE_INITIALIZATION_STRATEGY_NONE
} Rte_InitializationStrategyType ;

/* Specifies an instance of a ModeDeclarationGroupPrototype of a Bsw-Module. */
typedef struct Rte_ModeSchtblMapBswType_tag
{
/* Reference to an instance of a ModeDeclarationGroupPrototype of a Bsw-Module. */
	/*TODO:MODE-DECLARATION-GROUP-PROTOTYPE*/void* RteModeSchtblMapBswProvidedModeGroupRef ;
/* Reference to an instance specification of a Bsw-Module. */
/* /AUTOSAR/EcucDefs/Rte/RteBswModuleInstance */
    struct Rte_BswModuleInstanceType_tag* RteModeSchtblMapBswInstanceRef ;
} Rte_ModeSchtblMapBswType ;

/* Specifies an instance of a ModeDeclarationGroupPrototype of a SwComponentPrototype. */
typedef struct Rte_ModeSchtblMapSwcType_tag
{
/* Reference to the PPortPrototype of a SwComponentPrototype. */
	/*TODO:P-PORT-PROTOTYPE*/void* RteModeSchtblMapSwcPortRef ;
/* Reference to an instance specification of a SwComponentPrototype. */
/* /AUTOSAR/EcucDefs/Rte/RteSwComponentInstance */
    struct Rte_SwComponentInstanceType_tag* RteModeSchtblMapSwcInstanceRef ;
} Rte_ModeSchtblMapSwcType ;

/* Provides configuration input in which Modes of a ModeDeclarionGroupPrototype of a Mode Manager
 *  a OsScheudleTable shall be active.
 */
typedef struct Rte_ModeToScheduleTableMappingType_tag
{
	Rte_ModeSchtblMapBswType* RteModeSchtblMapBsw ;
	Rte_ModeSchtblMapSwcType* RteModeSchtblMapSwc ;
/* Reference to the ModeDeclarations. */
	/*TODO:MODE-DECLARATION*/void* RteModeSchtblMapModeDeclarationRef ;
/* Reference to the OsScheduleTable which shall be active in the specified RteModeSchblMapModeDeclarationRefs.
 */
/* /AUTOSAR/EcucDefs/Os/OsScheduleTable */
    struct Os_ScheduleTableType_tag* RteModeScheduleTableRef ;
} Rte_ModeToScheduleTableMappingType ;

/* Attributes used in the activation of OsTasks and Runnable Entities. */
typedef struct Rte_UsedOsActivationType_tag
{
/* Important: This is a requirement from the Rte towards the Os/Mcu setup. The Rte Generator shall
 *  assume this activation offset to be fulfilled.
 */
/* Activation offset in seconds. */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 RteExpectedActivationOffset ;
/* Important: This is a requirement from the Rte towards the Os/Mcu setup. The Rte Generator shall
 *  assume this tick duration to be fulfilled.
 */
/* The expected tick duration in seconds which shall be configured to drive the OsScheduleTables
 *  or OsAlarm.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 RteExpectedTickDuration ;
/* Reference to an OsAlarm. */
/* /AUTOSAR/EcucDefs/Os/OsAlarm */
    struct Os_AlarmType_tag* RteActivationOsAlarmRef ;
/* Reference to an OsScheduleTable. */
/* /AUTOSAR/EcucDefs/Os/OsScheduleTable */
    struct Os_ScheduleTableType_tag* RteActivationOsSchTblRef ;
/* Reference to an OsTask. */
/* /AUTOSAR/EcucDefs/Os/OsTask */
    struct Os_TaskType_tag* RteActivationOsTaskRef ;
} Rte_UsedOsActivationType ;

/* Maps a RunnableEntity onto one OsTask based on the activating RTEEvent. */
typedef struct Rte_EventToTaskMappingType_tag
{
/* Activation offset in seconds. */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 RteActivationOffset ;
/* This parameter shall not be set to true when the mapped RTEEvent refers to a RunnableEntity
 *  which minimumStartInterval attribute is > 0.
 */
/* When RteImmediateRestart is set to true the RunnableEntitiy shall be immediately re-started
 *  after termination if it was activated by this RTEEvent while it was already started.
 */
	boolean RteImmediateRestart ;
/* The absence of this parameter is interpreted as "NONE".
 * 
 *                                                 It shall be considered an invalid configuration
 *  if the task is preemptable and the value of this parameter is not set to "NONE" or the parameter
 *  is absent.
 */
	Rte_OsSchedulePointType RteOsSchedulePoint ;
/* For periodic activation this is the order of execution.
 *                                                 For event driver activation this is the order
 *  of evaluation which actual RunnableEntity has to be executed.
 */
/* Each RunnableEntity mapped to an OsTask has a specific position within the task execution. */
	uint16 RtePositionInTask ;
/* Reference to the description of the RTEEvent which is pointing to the RunnableEntity being mapped.
 *  This allows a fine grained mapping of RunnableEntites based on the activating RTEEvent.
 */
	/*TODO:RTE-EVENT*/void* RteEventRef ;
/* Reference to the OsTask the RunnableEntity activated by the RteEventRef is mapped to. */
/* If no reference to the OsTask is specified the RunnableEntity shall be executed via a direct
 *  function call.
 */
/* /AUTOSAR/EcucDefs/Os/OsTask */
    struct Os_TaskType_tag* RteMappedToTaskRef ;
/* If an OsAlarm is used to activate the OsTask this RteEvent is mapped to it shall be referenced
 *  here.
 */
/* /AUTOSAR/EcucDefs/Os/OsAlarm */
    struct Os_AlarmType_tag* RteUsedOsAlarmRef ;
/* If an OsEvent is used to activate the OsTask this RteEvent is mapped to it shall be referenced
 *  here.
 */
/* /AUTOSAR/EcucDefs/Os/OsEvent */
    struct Os_EventType_tag* RteUsedOsEventRef ;
/* If an OsScheduleTableExpiryPoint is used to activate the OsTask this RteEvent is mapped to it
 *  shall be referenced here.
 */
/* /AUTOSAR/EcucDefs/Os/OsScheduleTable/OsScheduleTableExpiryPoint */
    struct Os_ScheduleTableExpiryPointType_tag* RteUsedOsSchTblExpiryPointRef ;
/* Optional reference to an OsTask where the activation of this RteEvent shall be evaluated. The
 *  actual execution of the Runnable Entity shall happen in the OsTask referenced by RteMappedToTaskRef.
 */
/* /AUTOSAR/EcucDefs/Os/OsTask */
    struct Os_TaskType_tag* RteVirtuallyMappedToTaskRef ;
} Rte_EventToTaskMappingType ;

/* Specifies the implementation to be used for the data consistency of this ExclusiveArea. */
typedef struct Rte_ExclusiveAreaImplementationType_tag
{
	Rte_ExclusiveAreaImplMechanismType RteExclusiveAreaImplMechanism ;
/* Reference to the ExclusiveArea. */
	/*TODO:EXCLUSIVE-AREA*/void* RteExclusiveAreaRef ;
/* Optional reference to an OsResource in case RteExclusiveAreaImplMechanism is configured to OS_RESOURCE
 *  for this ExclusiveArea.
 */
/* /AUTOSAR/EcucDefs/Os/OsResource */
    struct Os_ResourceType_tag* RteExclusiveAreaOsResourceRef ;
} Rte_ExclusiveAreaImplementationType ;

/* Defines the configuration of External Trigger Event Communication for Software Components */
typedef struct Rte_ExternalTriggerConfigType_tag
{
/* The queue is implemented by the RTE. A value greater or equal to 1 requests an queued behavior.
 *  
 *                                                 Setting the value of RteTriggerSourceQueueLength
 *  to 0 requests an none queued implementation of the trigger communication.
 * 
 *                                                 If there is no RteTriggerSourceQueueLength configured
 *  for a Trigger Emitter the default value of 0 applies as well.
 */
/* Length of trigger queue on the trigger source side. */
	uint32 RteTriggerSourceQueueLength ;
/* Reference to a Trigger instance in the pPortPrototype of the related component instance. */
/* The referenced Trigger instance has to belong to the same software component instance as the
 *  RteSwComponentInstance owning this parameter configures.
 */
	/*TODO:TRIGGER*/void* RteSwcTriggerSourceRef ;
} Rte_ExternalTriggerConfigType ;

/* Defines the configuration of Inter Runnable Triggering for Software Components */
typedef struct Rte_InternalTriggerConfigType_tag
{
/* The queue is implemented by the RTE. A value greater or equal to 1 requests an queued behavior.
 *  
 *                                                 Setting the value of RteTriggerSourceQueueLength
 *  to 0 requests an none queued implementation of the trigger communication.
 * 
 *                                                 If there is no RteTriggerSourceQueueLength configured
 *  for a Trigger Emitter the default value of 0 applies as well.
 */
	uint32 RteTriggerSourceQueueLength ;
/* Reference to an InternalTriggeringPoint of the related component instance. */
/* The referenced InternalTriggeringPoint has to belong to the same software component instance
 *  as the RteSwComponentInstance owning this parameter configures.
 */
	/*TODO:INTERNAL-TRIGGERING-POINT*/void* RteSwcTriggerSourceRef ;
} Rte_InternalTriggerConfigType ;

/* Specifies the relationship between the AtomicSwComponentType's NVRAMMapping / NVRAM needs and
 *  the NvM module configuration.
 */
typedef struct Rte_NvRamAllocationType_tag
{
/* This symbol will be resolved into the parameter "NvmRamBlockDataAddress" from the "NvmBlockDescriptor".
 */
/* This is the name of the linker object name where the NVRam Block will be mirrored by the Nvm. */
/* TODO: I don't know how to implement it */
	void* RteNvmRamBlockLocationSymbol ;
/* This symbol will be resolved into the parameter "NvmRomBlockDataAddress" from the "NvmBlockDescriptor".
 */
/* This is the name of the linker object name where the NVRom Block will be accessed by the Nvm. */
/* TODO: I don't know how to implement it */
	void* RteNvmRomBlockLocationSymbol ;
/* Reference to the SwSeriveDependency which is used to specify the NvBlockNeeds. */
	/*TODO:SWC-SERVICE-DEPENDENCY*/void* RteSwNvRamMappingRef ;
/* Reference to the used NvM block for storage of the NVRAMMapping information. */
/* /AUTOSAR/EcucDefs/NvM/NvMBlockDescriptor */
	NvM_BlockDescriptorType* RteNvmBlockRef ;
} Rte_NvRamAllocationType ;

/* Specifies for each ParameterSwComponentType or AtomicSwComponentType whether calibration is
 *  enabled.
 */
typedef struct Rte_ComponentTypeCalibrationType_tag
{
/* Enables calibration support for the specified ParameterSwComponentType or AtomicSwComponentType. */
	boolean RteCalibrationSupportEnabled ;
/* Reference to the SwAddrMethod for which software calibration support shall be enabled. */
	/*TODO:SW-ADDR-METHOD*/void* RteCalibrationSwAddrMethodRef ;
} Rte_ComponentTypeCalibrationType ;

/* General configuration parameters of the Bsw Scheduler section. */
typedef struct Rte_BswGeneralType_tag
{
/* Enables the generation of the SchM_GetVersionInfo() API. */
	boolean RteSchMVersionInfoApi ;
/* If this parameter is set to true the ShadowSignal APIs and Signal APIs (Com_SendSignal, Com_InvalidateSignal,
 *  Com_ReceiveSignal) are used. 
 *                                         If this parameter is set to false only the Signal APIs
 *  (Com_SendSignal, Com_InvalidateSignal, Com_ReceiveSignal) are used.
 */
/* This parameter defines whether the ComShadowSignalAPIs ((Com_UpdateShadowSignal, Com_InvalidateShadowSignal,
 *  Com_ReceiveShadowSignal) are used or not.
 */
	boolean RteUseComShadowSignalApi ;
} Rte_BswGeneralType ;

/* Represents one instance of a Bsw-Module configured on one ECU. */
typedef struct Rte_BswModuleInstanceType_tag
{
	Rte_BswEventToTaskMappingType* RteBswEventToTaskMapping ;
	Rte_BswExclusiveAreaImplType* RteBswExclusiveAreaImpl ;
	Rte_BswExternalTriggerConfigType* RteBswExternalTriggerConfig ;
	Rte_BswInternalTriggerConfigType* RteBswInternalTriggerConfig ;
	Rte_BswRequiredModeGroupConnectionType* RteBswRequiredModeGroupConnection ;
	Rte_BswRequiredTriggerConnectionType* RteBswRequiredTriggerConnection ;
/* Reference to the BswImplementation for which the Rte /SchM is configured. */
	/*TODO:BSW-IMPLEMENTATION*/void* RteBswImplementationRef ;
/* Reference to the ECU Configuration Values provided for this BswImplementation. */
	/*TODO:MODULE-CONFIGURATION*/void* RteBswModuleConfigurationRef ;
} Rte_BswModuleInstanceType ;

/* This container holds the parameters for the configuration of the RTE Generation. */
typedef struct Rte_GenerationType_tag
{
	Rte_CalibrationSupportType RteCalibrationSupport ;
/* Holds the vendor ID of the generated Rte code. */
	uint16 RteCodeVendorId ;
/* The Rte shall log development errors to the Det module. */
	boolean RteDevErrorDetect ;
/* The Rte shall detect if it is started when its APIs are called, and the BSW Scheduler shall
 *  check if it is initialized when its APIs are called.
 */
	boolean RteDevErrorDetectUninit ;
	Rte_GenerationModeType RteGenerationMode ;
	Rte_IocInteractionReturnValueType RteIocInteractionReturnValue ;
/* The RTE generator shall have the option to switch off support for measurement for generated
 *  RTE code. This option shall influence complete RTE code at once.
 */
	boolean RteMeasurementSupport ;
	Rte_OptimizationModeType RteOptimizationMode ;
/* If present, the RTE generator shall provide the list of C RTE identifiers whose name is not
 *  unique when only the first RteToolChainSignificantCharacters characters are considered.
 */
	uint16 RteToolChainSignificantCharacters ;
/* If set to true the RTE generator shall enable the value range checking for the specified VariableDataPrototypes.
 */
	boolean RteValueRangeCheckEnabled ;
/* Defines an additional prefix for all VFB trace functions to be generated. With this approach
 *  it is possible to have debugging and DLT trace functions at the same time.
 */
/* TODO: I don't know how to implement it */
	void* RteVfbTraceClientPrefix ;
/* The RTE generator shall globally enable VFB tracing when RteVfbTrace is set to "true". */
	boolean RteVfbTraceEnabled ;
/* Example: #define Rte_WriteHook_i1_p1_a_Start
 * 
 *                                         This also applies to VFB trace functions with a RteVfbTraceClientPrefix,
 *  e.g. Rte_Dbg_WriteHook_I1_P1_a_Start.
 */
	Rte_VfbTraceFunctionType RteVfbTraceFunction ;
} Rte_GenerationType ;

/* Configuration of the Implicit Communication behavior to be generated. */
typedef struct Rte_ImplicitCommunicationType_tag
{
/* Data values for Coherent Implicit Read Access'es are read before the first reading RunnbaleEntity
 *  starts and are stable during the execution of all the reading RunnableEntitys; except Coherent
 *  Implicit Write Access'es belongs to the same Coherency Group. 
 *                                         Data values written by Coherent Implicit Write Access'es
 *  are available for readers not belonging to the Coherency Group after the last writing RunnableEntity
 *  has terminated.
 * 
 *                                         Please note that a Coherent Implicit Data Access can
 *  be defined for VariableAccess'es to same and different VariableDataElements. Nevertheless all
 *  Coherent Implicit Data Access'es of one Coherency Group have to be executed in the same task.
 */
/* If set to true the referenced VariableAccess'es of this RteImplicitCommunication container are
 *  in one CoherencyGroup.
 */
	boolean RteCoherentAccess ;
/* If set to true the RTE will perform preemption area specific buffer update immediately before
 *  (for VariableAccess in the role dataReadAccess) resp. after (for VariableAccess in the role
 *  dataWriteAccess) Runnable execution.
 */
	boolean RteImmediateBufferUpdate ;
/* Reference to the VariableAccess in the dataReadAccess role. */
	/*TODO:VARIABLE-ACCESS*/void* RteVariableReadAccessRef ;
/* Reference to the VariableAccess in the dataWriteAccess role. */
	/*TODO:VARIABLE-ACCESS*/void* RteVariableWriteAccessRef ;
/* Reference to a SwComponentPrototype. */
/* This denotes the instances of the VariableAccess belonging to the RteImplicitCommunication. */
	/*TODO:SW-COMPONENT-PROTOTYPE*/void* RteSoftwareComponentInstanceRef ;
} Rte_ImplicitCommunicationType ;

/* Specifies the initialization strategy for variables allocated by RTE with the purpose to implement
 *  VariableDataPrototypes.
 */
typedef struct Rte_InitializationBehaviorType_tag
{
	Rte_InitializationStrategyType RteInitializationStrategy ;
/* The SectionInitializationPolicy describes the intended initialization of MemorySections. 
 * 
 *                                         The following values are standardized in AUTOSAR Methodology:
 * 
 *                                         * '''NO-INIT''': No initialization and no clearing is
 *  performed. Such data elements must not be read before one has written a value into it.
 *                                         * '''INIT''': To be used for data that are initialized
 *  by every reset to the specified value (initValue). 
 *                                         * '''POWER-ON-INIT''': To be used for data that are
 *  initialized by "Power On" to the specified value (initValue). Note: there might be several
 *  resets between power on resets. 
 *                                         * '''CLEARED''': To be used for data that are initialized
 *  by every reset to zero. 
 *                                         * '''POWER-ON-CLEARED''': To be used for data that are
 *  initialized by "Power On" to zero. Note: there might be several resets between power on resets.
 */
/* This parameter describes the SectionInitializationPolicys for which a particular RTE initialization
 *  strategy applies.
 */
	char* RteSectionInitializationPolicy ;
} Rte_InitializationBehaviorType ;

/* Interaction of the Rte with the Os. */
typedef struct Rte_OsInteractionType_tag
{
/* The Mode Manager is either specified as a SwComponentPrototype (RteModeSchtblMapSwc) or as a
 *  BSW-Module (RteModeSchtblMapBsw).
 */
	Rte_ModeToScheduleTableMappingType* RteModeToScheduleTableMapping ;
	Rte_UsedOsActivationType* RteUsedOsActivation ;
} Rte_OsInteractionType ;

/* Specifies the PostbuildVariantSets for each of the PostBuild configurations of the RTE. */
typedef struct Rte_PostBuildVariantConfigurationType_tag
{
/* Reference to the PredefinedVariant element which defines the values for PostBuildVariationCriterion
 *  elements.
 */
	/*TODO:PREDEFINED-VARIANT*/void* RtePostBuildUsedPredefinedVariant ;
} Rte_PostBuildVariantConfigurationType ;

/* Representation of one SwComponentPrototype located on the to be configured ECU. All subcontainer
 *  configuration aspects are in relation to this SwComponentPrototype.
 */
typedef struct Rte_SwComponentInstanceType_tag
{
/* Even if a RunnableEntity shall be executed via a direct function call this RteEventToTaskMapping
 *  shall be specified, but no RteMappedToTask and RtePositionInTask elements given.
 */
	Rte_EventToTaskMappingType* RteEventToTaskMapping ;
	Rte_ExclusiveAreaImplementationType* RteExclusiveAreaImplementation ;
	Rte_ExternalTriggerConfigType* RteExternalTriggerConfig ;
	Rte_InternalTriggerConfigType* RteInternalTriggerConfig ;
	Rte_NvRamAllocationType* RteNvRamAllocation ;
/* Reference to a SwComponentPrototype. */
	/*TODO:SW-COMPONENT-PROTOTYPE*/void* RteSoftwareComponentInstanceRef ;
} Rte_SwComponentInstanceType ;

/* Representation of one SwComponentType for the base of all configuration parameter which are
 *  affecting the whole type and not a specific instance.
 */
typedef struct Rte_SwComponentTypeType_tag
{
/* If references to SwAddrMethod are provided in RteCalibrationSwAddrMethodRef only ParameterDataPrototypes
 *  with the referenced SwAddrMethod shall have software calibration support enabled.
 */
	Rte_ComponentTypeCalibrationType* RteComponentTypeCalibration ;
/* Reference to either AtomicSwComponentType or ParameterSwComponentType. */
	/*TODO:SW-COMPONENT-TYPE*/void* RteComponentTypeRef ;
/* The Implementation which shall be assiged to the SwComponentType. */
	/*TODO:SWC-IMPLEMENTATION*/void* RteImplementationRef ;
} Rte_SwComponentTypeType ;

/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __cplusplus
}}  /* name space */
#endif
#endif /* RTE_TYPES_H */

