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
#ifndef COM_TYPES_H
#define COM_TYPES_H

#ifdef __cplusplus
namespace autosar {
extern "C" {
#endif
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* Each instance of this choice container allows to define one routing destination either by reference
 *  to an already configured COM signal / signal group or by a  destination description container.
 */
typedef struct
{
} Com_GwDestinationType ;

/* This choice container allows the definition of the gateway source signal either by reference
 *  to an already configured COM signal / signal group or by a  source description container.
 */
typedef struct
{
} Com_GwSourceType ;

typedef struct
{
	Com_GwDestinationType* ComGwDestination ;
	Com_GwSourceType* ComGwSource ;
} Com_GwMappingType ;

/* Name of Com_CbkCounterErr callback function to be called. If this */
/* TODO: 
 * typedef void (*Com_IPduCounterErrorNotificationType)(void);
 */

/* This optional container contains the configuration parameters of PDU Counter. */
typedef struct
{
/* parameter is omitted no I-PDU counter mismatch notification shall take place. */
	Com_IPduCounterErrorNotificationType ComIPduCounterErrorNotification ;
/* Size of PDU Counter expressed in bits */
	uint8 ComIPduCounterSize ;
/* of I-PDU (SDU). Note that PDU counter is not allowed to cross a byte border.
 *                                                         The parameter ComIPduCounterStartPosition
 *  shall define the bit0 of the first  
 *                                                         byte like in little endian byte order.
 */
/* Position of PDU counter expressed in bits from start position of data content */
	uint16 ComIPduCounterStartPosition ;
/* Threshold value of I-PDU counter algorithm, see COM590. */
	uint8 ComIPduCounterThreshold ;
} Com_IPduCounterType ;

/* This optional container contains the information needed for each I-PDU replicated. */
typedef struct
{
/* The number of identical I-PDUs needed for successful voting. */
	uint8 ComIPduReplicationQuorum ;
} Com_IPduReplicationType ;

/* The available transmission modes described in [18] shall be extended by the additional mode None. */
typedef enum
{
	COM_TXMODEMODE_DIRECT,
	COM_TXMODEMODE_MIXED,
	COM_TXMODEMODE_NONE,
	COM_TXMODEMODE_PERIODIC,
} Com_TxModeModeType ;

/* This container contains the configuration parameters of the AUTOSAR COM module's transmission
 *  modes.
 */
typedef struct
{
/* The transmission mode None shall not have any further sub-attributes in the ComTxMode object. */
	Com_TxModeModeType ComTxModeMode ;
/* Defines the number of repetitions for the transmission mode DIRECT and the event driven part
 *  of transmission mode MIXED.
 */
	uint8 ComTxModeNumberOfRepetitions ;
/* Defines the repetition period in seconds of the multiple transmissions in case ComTxModeNumberOfRepetitions
 *  is configured greater than 1 and ComTxModeMode is configured to DIRECT or MIXED. In case of
 *  the mixed transmission mode only the event driven part is affected.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 ComTxModeRepetitionPeriod ;
/* Defines the period in seconds between the start of the I-PDU by Com_IpduGroupControl and the
 *  first transmission request in case ComTxModeMode is configured to PERIODIC or MIXED. In case
 *  of the mixed transmission mode only the periodic part is affected.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 ComTxModeTimeOffset ;
/* Defines the repetition period in seconds of the periodic transmission requests in case ComTxModeMode
 *  is configured to PERIODIC or MIXED. In case of the mixed transmission mode only the periodic
 *  part is affected.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 ComTxModeTimePeriod ;
} Com_TxModeType ;

/* This container contains the configuration parameters of the AUTOSAR COM module's transmission
 *  modes in the case the ComFilter evaluates to false.
 */
typedef struct
{
	Com_TxModeType* ComTxMode ;
} Com_TxModeFalseType ;

/* This container contains the configuration parameters of the AUTOSAR COM module's transmission
 *  modes in the case the ComFilter evaluates to true.
 */
typedef struct
{
	Com_TxModeType* ComTxMode ;
} Com_TxModeTrueType ;

/* Defines when the update-bits of signals or signal groups, contained in this I-PDU, will be cleared.
 */
typedef enum
{
	COM_TXIPDUCLEARUPDATEBIT_CONFIRMATION,
	COM_TXIPDUCLEARUPDATEBIT_TRANSMIT,
	COM_TXIPDUCLEARUPDATEBIT_TRIGGERTRANSMIT,
} Com_TxIPduClearUpdateBitType ;

/* This container contains additional transmission related configuration parameters of the AUTOSAR
 *  COM module's I-PDUs.
 */
typedef struct
{
	Com_TxModeFalseType* ComTxModeFalse ;
	Com_TxModeTrueType* ComTxModeTrue ;
/* Defines the Minimum Delay Time (MDT) between successive transmissions of this I-PDU in seconds.
 *  The MDT is independent of the possible different transmission modes. There is only one minimum
 *  delay time parameter for one I-PDU. The minimum delay timer is not reset by changing the transmission
 *  mode. Hence, it is not allowed to violate the minimum delay time by transmission mode changes.
 *  It is not possible to monitor the minimum delay time for I-PDUs that are requested using the
 *  Com_TriggerTransmit API.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 ComMinimumDelayTime ;
	Com_TxIPduClearUpdateBitType ComTxIPduClearUpdateBit ;
/* The AUTOSAR COM module fills not used areas of an I-PDU with this byte pattern. This attribute
 *  is mandatory to avoid undefined behaviour. This byte-pattern will be repeated throughout the
 *  I-PDU before any init-values or update-bits were set.
 */
	uint8 ComTxIPduUnusedAreasDefault ;
} Com_TxIPduType ;

/* This parameter defines the existence and the name of a callout function for the corresponding
 *  I-PDU. If this parameter is omitted no I-PDU callout shall take place for the corresponding
 *  I-PDU.
 */
/* TODO: 
 * typedef void (*Com_IPduCalloutType)(void);
 */

/* The direction defines if this I-PDU, and therefore the contributing signals and signal groups,
 *  shall be sent or received.
 */
typedef enum
{
	COM_IPDUDIRECTION_RECEIVE,
	COM_IPDUDIRECTION_SEND,
} Com_IPduDirectionType ;

/* For the definition of the two modes Immediate and Deferred. */
typedef enum
{
	COM_IPDUSIGNALPROCESSING_DEFERRED,
	COM_IPDUSIGNALPROCESSING_IMMEDIATE,
} Com_IPduSignalProcessingType ;

/* If there is a trigger transmit callout defined for this I-PDU this parameter contains the name
 *  of the callout function.
 */
/* TODO: 
 * typedef void (*Com_IPduTriggerTransmitCalloutType)(void);
 */

/* Defines if this I-PDU is a normal I-PDU that can be sent unfragmented or if this is a large
 *  I-PDU that shall be sent via the Transport Protocol of the underlying bus.
 */
typedef enum
{
	COM_IPDUTYPE_NORMAL,
	COM_IPDUTYPE_TP,
} Com_IPduTypeType ;

/* Contains the configuration parameters of the AUTOSAR COM module's I-PDUs. */
typedef struct
{
	Com_IPduCounterType* ComIPduCounter ;
	Com_IPduReplicationType* ComIPduReplication ;
	Com_TxIPduType* ComTxIPdu ;
	Com_IPduCalloutType ComIPduCallout ;
/* If the underlying IF-modul supports cancellation of transmit requests.
 *                                                 Defines for I-PDUs with ComIPduType TP:
 *                                                 If the underlying TP-module supports RX and
 *  TX cancellation of ongoing requests.
 */
/* Defines for I-PDUs with ComIPduType NORMAL: */
	boolean ComIPduCancellationSupport ;
	Com_IPduDirectionType ComIPduDirection ;
/* The numerical value used as the ID of this I-PDU. The ComIPduHandleId is required by the API
 *  calls to receive I-PDUs from the PduR (ComIP-duDirection: Receive). For Tx-I-PDUs (ComIPduDirection:
 *  Send) this handle Id is used by the PduR to confirm the transmission of the ComIPdu. In case
 *  no Tx-Confirmation is configured for a Tx-I-PDU, the ComIPduHandleId is not used.
 */
	uint16 ComIPduHandleId ;
	Com_IPduSignalProcessingType ComIPduSignalProcessing ;
	Com_IPduTriggerTransmitCalloutType ComIPduTriggerTransmitCallout ;
	Com_IPduTypeType ComIPduType ;
} Com_IPduType ;

/* Contains the configuration parameters of the AUTOSAR COM module's I-PDU groups. */
typedef struct
{
/* The ComIPduGroupHandleId is required by the API calls to start and stop I-PDU  Groups.
 * 
 *                                                 Range: 0 .. (ComSupportedIPduGroups-1)
 */
/* The numerical value used as the ID of this I-PDU Group . */
	uint16 ComIPduGroupHandleId ;
} Com_IPduGroupType ;

/* The range of values is specified in the [17] specification, chapter 2.2.2, Reception Filtering. */
typedef enum
{
	COM_FILTERALGORITHM_ALWAYS,
	COM_FILTERALGORITHM_MASKED_NEW_DIFFERS_MASKED_OLD,
	COM_FILTERALGORITHM_MASKED_NEW_DIFFERS_X,
	COM_FILTERALGORITHM_MASKED_NEW_EQUALS_X,
	COM_FILTERALGORITHM_NEVER,
	COM_FILTERALGORITHM_NEW_IS_OUTSIDE,
	COM_FILTERALGORITHM_NEW_IS_WITHIN,
	COM_FILTERALGORITHM_ONE_EVERY_N,
} Com_FilterAlgorithmType ;

/* This container contains the configuration parameters of the AUTOSAR COM module's Filters. */
typedef struct
{
	Com_FilterAlgorithmType ComFilterAlgorithm ;
/* The name of this attribute corresponds to the parameter name in the [17] specification of Reception
 *  Filtering.
 */
	uint64 ComFilterMask ;
/* The name of this attribute corresponds to the parameter name in the [17] specification of Reception
 *  Filtering.
 */
	uint64 ComFilterMax ;
/* The name of this attribute corresponds to the parameter name in the [17] specification of Reception
 *  Filtering.
 */
	uint64 ComFilterMin ;
/* Range = 0..(ComFilterPeriod-1) */
/* The name of this attribute corresponds to the parameter name in the [17] specification of Reception
 *  Filtering.
 */
	uint64 ComFilterOffset ;
/* This parameter defines the period of the ComFilterAlgorithm ONE_EVERY_N. */
	uint64 ComFilterPeriod ;
/* The name of this attribute corresponds to the parameter name in the [17] specification of Reception
 *  Filtering.
 */
	uint64 ComFilterX ;
} Com_FilterType ;

/* This parameter defines the action performed upon reception of an invalid signal. */
typedef enum
{
	COM_DATAINVALIDACTION_NOTIFY,
	COM_DATAINVALIDACTION_REPLACE,
} Com_DataInvalidActionType ;

/* Only valid on sender side: Name of Com_CbkTxErr callback function to be called. */
/* TODO: 
 * typedef void (*Com_ErrorNotificationType)(void);
 */

/* Only valid on receiver side: Name of Com_CbkInv callback function to be called. Name of the
 *  function which notifies the RTE about the reception of an invalidated signal/ signal group.
 *  Only applicable if ComDataInvalidAction is configured to NOTIFY.
 */
/* TODO: 
 * typedef void (*Com_InvalidNotificationType)(void);
 */

/* On sender side: Name of Com_CbkTxAck callback function to be called. */
/* TODO: 
 * typedef void (*Com_NotificationType)(void);
 */

/* This parameter defines the action performed upon expiration of the  reception deadline monitoring
 *  timer.
 */
typedef enum
{
	COM_RXDATATIMEOUTACTION_NONE,
	COM_RXDATATIMEOUTACTION_REPLACE,
} Com_RxDataTimeoutActionType ;

/* Defines the endianness of the signal's network representation. */
typedef enum
{
	COM_SIGNALENDIANNESS_BIG_ENDIAN,
	COM_SIGNALENDIANNESS_LITTLE_ENDIAN,
	COM_SIGNALENDIANNESS_OPAQUE,
} Com_SignalEndiannessType ;

/* The AUTOSAR type of the signal. Whether or not the signal is signed or unsigned can be found
 *  by examining the value of this attribute.
 */
typedef enum
{
	COM_SIGNALTYPE_BOOLEAN,
	COM_SIGNALTYPE_FLOAT32,
	COM_SIGNALTYPE_FLOAT64,
	COM_SIGNALTYPE_SINT16,
	COM_SIGNALTYPE_SINT32,
	COM_SIGNALTYPE_SINT8,
	COM_SIGNALTYPE_UINT16,
	COM_SIGNALTYPE_UINT32,
	COM_SIGNALTYPE_UINT8,
	COM_SIGNALTYPE_UINT8_DYN,
	COM_SIGNALTYPE_UINT8_N,
} Com_SignalTypeType ;

/* On sender side: Name of Com_CbkTxTOut callback function to be called. */
/* TODO: 
 * typedef void (*Com_TimeoutNotificationType)(void);
 */

/* Defines if a write access to this signal can trigger the transmission of the corresponding I-PDU.
 *  If the I-PDU is triggered, depends also on the transmission mode of the corresponding I-PDU.
 */
typedef enum
{
	COM_TRANSFERPROPERTY_PENDING,
	COM_TRANSFERPROPERTY_TRIGGERED,
	COM_TRANSFERPROPERTY_TRIGGERED_ON_CHANGE,
	COM_TRANSFERPROPERTY_TRIGGERED_ON_CHANGE_WITHOUT_REPETITION,
	COM_TRANSFERPROPERTY_TRIGGERED_WITHOUT_REPETITION,
} Com_TransferPropertyType ;

/* Contains the configuration parameters of the AUTOSAR COM module's signals. */
typedef struct
{
/* Note: On sender side the container is used to specify the transmission mode conditions. */
	Com_FilterType* ComFilter ;
/* Starting position within the I-PDU. This parameter refers to the position in the I-PDU and not
 *  in the shadow buffer. If the endianness conversion is configured to Opaque the parameter ComBitPosition
 *  shall define the bit0 of the first byte like in little endian byte order
 */
	uint16 ComBitPosition ;
/* For ComSignalType UINT8_N and UINT8_DYN this size shall be configured by ComSignalLength. */
/* Size in bits, for non-array signal types. */
	uint8 ComBitSize ;
/* Relating to signal groups the action in case if one of the included signals is an invalid signal.
 *                                                 If Replace is used the ComSignalInitValue will
 *  be used for the replacement.
 */
	Com_DataInvalidActionType ComDataInvalidAction ;
/* If this parameter is omitted no error notification shall take place. */
	Com_ErrorNotificationType ComErrorNotification ;
/* Defines the length of the first deadline monitoring timeout period in seconds. This timeout
 *  is used immediately after start (or restart) of the deadline monitoring service. The timeout
 *  period of the successive periods is configured by COM263_Conf.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 ComFirstTimeout ;
/* For signals it is required by the API calls Com_UpdateShadowSignal, Com_ReceiveShadowSignal
 *  and Com_InvalidateShadowSignal.
 *                                                 For signals groups it is required by the Com_SendSignalGroup
 *  and Com_ReceiveSignalGroup calls.
 */
/* The numerical value used as the ID. */
	uint16 ComHandleId ;
	Com_InvalidNotificationType ComInvalidNotification ;
/* On receiver side: Name of Com_CbkRxAck callback function to be called.
 * 
 *                                                 If this parameter is omitted no notification
 *  shall take place.
 */
	Com_NotificationType ComNotification ;
	Com_RxDataTimeoutActionType ComRxDataTimeoutAction ;
/* In case the ComSignalType is UINT8, UINT16, UINT32, SINT8, SINT16, SINT32 the string shall be
 *  interpreted as defined in the chapter Integer Type in the AUTOSAR EcuC specification.
 *                                                 In case the ComSignalType is FLOAT32, FLOAT64
 *  the string shall be interpreted as defined in the chapter Float Type in the AUTOSAR EcuC specification.
 *                                                 In case the ComSignalType is BOOLEAN the string
 *  shall be interpreted as defined in the chapter Boolean Type in the AUTOSAR EcuC specification.
 *  
 *                                                 In case the ComSignal is a UINT8_N, UINT6_DYN
 *  the string shall be interpreted as a decimal representation of the characters separated by
 *  blanks, e.g. "97 98 100" means a string "abd", where the char "a" is in byte 0(lowest address),
 *  "b" is in byte 1, and "d" is in byte 2 and (highest address).
 */
/* Defines the data invalid value of the signal. */
	char* ComSignalDataInvalidValue ;
	Com_SignalEndiannessType ComSignalEndianness ;
/* In case the ComSignalType is UINT8, UINT16, UINT32, SINT8, SINT16, SINT32 the string shall be
 *  interpreted as defined in the chapter Integer Type in the AUTOSAR EcuC specification.
 *                                                 In case the ComSignalType is FLOAT32, FLOAT64
 *  the string shall be interpreted as defined in the chapter Float Type in the AUTOSAR EcuC specification.
 *                                                 In case the ComSignalType is BOOLEAN the string
 *  shall be interpreted as defined in the chapter Boolean Type in the AUTOSAR EcuC specification.
 *  
 *                                                 In case the ComSignal is a UINT8_N, UINT6_DYN
 *  the string shall be interpreted as a decimal representation of the characters separated by
 *  blanks, e.g. "97 98 100" means a string "abd", where the char "a" is in byte 0(lowest address),
 *  "b" is in byte 1, and "d" is in byte 2 and (highest address).
 */
/* Initial value for this signal. The default value is 0. */
	char* ComSignalInitValue ;
/* For ComSignalType UINT8_N this parameter specifies the length n in bytes. For ComSignalType
 *  UINT8_DYN it specifies the maximum length in bytes. For all other types this parameter shall
 *  be ignored. 
 * 
 *                                                 Range: 0..8 for normal CAN/ LIN I-PDUs, 0..254
 *  for normal FlexRay I-PDUs, and 0..4095 for I-PDUs with ComIPduType TP.
 */
/* Description: */
	uint16 ComSignalLength ;
/* This type could also be used to reserved appropriate storage in AUTOSAR COM. */
	Com_SignalTypeType ComSignalType ;
/* Defines the length of the deadline monitoring timeout period in seconds. The period for the
 *  first timeout period can be configured separately by COM183_Conf.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 ComTimeout ;
/* On receiver side: Name of Com_CbkRxTOut callback function to be called. */
	Com_TimeoutNotificationType ComTimeoutNotification ;
	Com_TransferPropertyType ComTransferProperty ;
/* If this attribute is omitted then there is no update-bit. This setting must be consistently
 *  on sender and on receiver side.
 *                                                 Range: 
 *                                                 0..63 for CAN and LIN 
 *                                                 0..2031 for FlexRay
 */
/* Bit position of update-bit inside I-PDU. */
	uint16 ComUpdateBitPosition ;
} Com_SignalType ;

/* This container contains the configuration parameters of group signals. I.e. signals that are
 *  included within a signal group.
 */
typedef struct
{
/* Note: On sender side the container is used to specify the transmission mode conditions. */
	Com_FilterType* ComFilter ;
	uint16 ComBitPosition ;
/* For ComSignalType UINT8_N and UINT8_DYN this size shall be configured by ComSignalLength. */
	uint8 ComBitSize ;
/* For signals it is required by the API calls Com_UpdateShadowSignal, Com_ReceiveShadowSignal
 *  and Com_InvalidateShadowSignal.
 *                                                         For signals groups it is required by
 *  the Com_SendSignalGroup and Com_ReceiveSignalGroup calls.
 */
	uint16 ComHandleId ;
/* In case the ComSignalType is UINT8, UINT16, UINT32, SINT8, SINT16, SINT32 the string shall be
 *  interpreted as defined in the chapter Integer Type in the AUTOSAR EcuC specification.
 *                                                         In case the ComSignalType is FLOAT32,
 *  FLOAT64 the string shall be interpreted as defined in the chapter Float Type in the AUTOSAR
 *  EcuC specification.
 *                                                         In case the ComSignalType is BOOLEAN
 *  the string shall be interpreted as defined in the chapter Boolean Type in the AUTOSAR EcuC
 *  specification. 
 *                                                         In case the ComSignal is a UINT8_N,
 *  UINT6_DYN the string shall be interpreted as a decimal representation of the characters separated
 *  by blanks, e.g. "97 98 100" means a string "abd", where the char "a" is in byte 0(lowest address),
 *  "b" is in byte 1, and "d" is in byte 2 and (highest address).
 */
	char* ComSignalDataInvalidValue ;
	Com_SignalEndiannessType ComSignalEndianness ;
/* In case the ComSignalType is UINT8, UINT16, UINT32, SINT8, SINT16, SINT32 the string shall be
 *  interpreted as defined in the chapter Integer Type in the AUTOSAR EcuC specification.
 *                                                         In case the ComSignalType is FLOAT32,
 *  FLOAT64 the string shall be interpreted as defined in the chapter Float Type in the AUTOSAR
 *  EcuC specification.
 *                                                         In case the ComSignalType is BOOLEAN
 *  the string shall be interpreted as defined in the chapter Boolean Type in the AUTOSAR EcuC
 *  specification. 
 *                                                         In case the ComSignal is a UINT8_N,
 *  UINT6_DYN the string shall be interpreted as a decimal representation of the characters separated
 *  by blanks, e.g. "97 98 100" means a string "abd", where the char "a" is in byte 0(lowest address),
 *  "b" is in byte 1, and "d" is in byte 2 and (highest address).
 */
	char* ComSignalInitValue ;
/* For ComSignalType UINT8_N this parameter specifies the length n in bytes. For ComSignalType
 *  UINT8_DYN it specifies the maximum length in bytes. For all other types this parameter shall
 *  be ignored. 
 * 
 *                                                         Range: 0..8 for normal CAN/ LIN I-PDUs,
 *  0..254 for normal FlexRay I-PDUs, and 0..4095 for I-PDUs with ComIPduType TP.
 */
	uint16 ComSignalLength ;
/* This type could also be used to reserved appropriate storage in AUTOSAR COM. */
	Com_SignalTypeType ComSignalType ;
	Com_TransferPropertyType ComTransferProperty ;
} Com_GroupSignalType ;

/* Contains the configuration parameters of the AUTOSAR COM module's signal groups. */
typedef struct
{
	Com_GroupSignalType* ComGroupSignal ;
/* Relating to signal groups the action in case if one of the included signals is an invalid signal.
 *                                                 If Replace is used the ComSignalInitValue will
 *  be used for the replacement.
 */
	Com_DataInvalidActionType ComDataInvalidAction ;
/* If this parameter is omitted no error notification shall take place. */
	Com_ErrorNotificationType ComErrorNotification ;
	uint64 ComFirstTimeout ;
/* For signals it is required by the API calls Com_UpdateShadowSignal, Com_ReceiveShadowSignal
 *  and Com_InvalidateShadowSignal.
 *                                                 For signals groups it is required by the Com_SendSignalGroup
 *  and Com_ReceiveSignalGroup calls.
 */
	uint16 ComHandleId ;
	Com_InvalidNotificationType ComInvalidNotification ;
/* On receiver side: Name of Com_CbkRxAck callback function to be called.
 * 
 *                                                 If this parameter is omitted no notification
 *  shall take place.
 */
	Com_NotificationType ComNotification ;
	Com_RxDataTimeoutActionType ComRxDataTimeoutAction ;
	uint64 ComTimeout ;
/* On receiver side: Name of Com_CbkRxTOut callback function to be called. */
	Com_TimeoutNotificationType ComTimeoutNotification ;
	Com_TransferPropertyType ComTransferProperty ;
/* If this attribute is omitted then there is no update-bit. This setting must be consistently
 *  on sender and on receiver side.
 *                                                 Range: 
 *                                                 0..63 for CAN and LIN 
 *                                                 0..2031 for FlexRay
 */
	uint16 ComUpdateBitPosition ;
} Com_SignalGroupType ;

/* Contains the timebase parameters for Tx, Rx and routing. */
typedef struct
{
/* The COM module (generator) might rely on the fact that Com_MainFunctionRouteSignals is scheduled
 *  according to the value configured here.
 */
/* The period between successive calls to Com_MainFunctionRouteSignals in seconds. This parameter
 *  may be used by the COM generator to transform the values of the signal gateway related timing
 *  configuration parameters of the COM module to internal implementation specific counter or tick
 *  values. The COM module's internal timing handling is implementation specific.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 ComGwTimeBase ;
/* The COM module (generator) may rely on the fact that Com_MainFunctionRx is scheduled according
 *  to the value configured here.
 */
/* The period between successive calls to Com_MainFunctionRx in seconds. This parameter may be
 *  used by the COM generator to transform the values of the reception related timing configuration
 *  parameters of the COM module to internal implementation specific counter or tick values. The
 *  COM module's internal timing handling is implementation specific.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 ComRxTimeBase ;
/* The COM module (generator) may rely on the fact that Com_MainFunctionTx is scheduled according
 *  to the value configured here.
 */
/* The period between successive calls to Com_MainFunctionTx in seconds. This parameter may be
 *  used by the COM generator to transform the values of the transmission related timing configuration
 *  parameters of the COM module to internal implementation specific counter or tick values. The
 *  COM module's internal timing handling is implementation specific.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 ComTxTimeBase ;
} Com_TimeBaseType ;

/* This container contains the configuration parameters and sub containers of the AUTOSAR COM module.
 *  This container is a MultipleConfigurationContainer, i.e. this container and its sub-containers
 *  exist once per configuration set.
 */
typedef struct
{
	Com_GwMappingType* ComGwMapping ;
	Com_IPduType* ComIPdu ;
	Com_IPduGroupType* ComIPduGroup ;
	Com_SignalType* ComSignal ;
	Com_SignalGroupType* ComSignalGroup ;
	Com_TimeBaseType* ComTimeBase ;
/* This ID is returned by a call to Com_GetConfigurationId. */
	uint32 ComConfigurationId ;
} Com_ConfigType ;

/* Contains the general configuration parameters of the module. */
typedef struct
{
/* If this parameter is configured COM_DEV_ERROR_DETECT shall be set to ON as output of the configuration
 *  tool. (as input for the source code), see COM028.
 */
/* The error hook shall contain code to call the Det. */
	boolean ComConfigurationUseDet ;
/* Enables globally for the whole Com module the minimum delay time monitoring for cyclic and repeated
 *  transmissions (ComTxModeMode=PERIODIC or ComTxModeMode=MIXED for the cyclic transmissions,
 *  ComTxModeNumberOfRepetitions > 0 for repeated transmissions).
 */
	boolean ComEnableMDTForCyclicTransmission ;
/* If this Parameter is set to true, retry of failed transmission requests is enabled. If this
 *  Parameter is not present, the default value is assumed.
 */
	boolean ComRetryFailedTransmitRequests ;
/* Defines the maximum number of supported I-PDU groups. */
	uint16 ComSupportedIPduGroups ;
/* True: version information API activated
 *                                         False: version information API deactivated
 */
/* Activate/Deactivate the version information API (Com_GetVersionInfo). */
	boolean ComVersionInfoApi ;
} Com_GeneralType ;

/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __cplusplus
}}  /* name space */
#endif /* COM_TYPES_H */

