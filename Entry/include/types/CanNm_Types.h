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
#ifndef CANNM_TYPES_H
#define CANNM_TYPES_H

/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
#ifdef __cplusplus
namespace autosar {
extern "C" {
#endif
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* This container is used to configure the Rx PDU properties that are used for the CanNm Channel. */
typedef struct
{
/* This parameter defines the Rx PDU ID of the CanIf L-PDU range that is associated with this CanNmChannel
 *  instance.
 */
	uint16 CanNmRxPduId ;
/* Reference to the global PDU that is used by this CanNmChannel instance. */
/* /AUTOSAR/EcucDefs/EcuC/EcucPduCollection/Pdu */
	EcuC_PduType* CanNmRxPduRef ;
} CanNm_RxPduType ;

/* This container contains the CanNmTxConfirmationPduId and the CanNmTxPduRef. */
typedef struct
{
/* Handle Id to be used by the Lower Layer to confirm the transmission of the CanNmTxPdu to the
 *  LowerLayer.
 */
	uint16 CanNmTxConfirmationPduId ;
/* The reference to the common PDU structure. */
/* /AUTOSAR/EcucDefs/EcuC/EcucPduCollection/Pdu */
	EcuC_PduType* CanNmTxPduRef ;
} CanNm_TxPduType ;

/* This optional container is used to configure the UserNm PDU. This container is only available
 *  if CanNmComUserDataSupport is enabled.
 */
typedef struct
{
/* This parameter defines the Handle ID of the NM User Data I-PDU. */
	uint16 CanNmTxUserDataPduId ;
/* Reference to the NM User Data I-PDU in the global PDU collection. */
/* /AUTOSAR/EcucDefs/EcuC/EcucPduCollection/Pdu */
	EcuC_PduType* CanNmTxUserDataPduRef ;
} CanNm_UserDataTxPduType ;

/* Defines the position of the control bit vector within the NM PDU. */
typedef enum
{
	CANNM_PDU_BYTE_0,
	CANNM_PDU_BYTE_1,
	CANNM_PDU_OFF
} CanNm_PduCbvPositionType ;

/* Defines the position of the source node identifier within the NM PDU. */
typedef enum
{
	CANNM_PDU_BYTE_0,
	CANNM_PDU_BYTE_1,
	CANNM_PDU_OFF
} CanNm_PduNidPositionType ;

/* This container contains the channel specific configuration parameter of the CanNm. */
typedef struct
{
	CanNm_RxPduType* CanNmRxPdu ;
	CanNm_TxPduType* CanNmTxPdu ;
	CanNm_UserDataTxPduType* CanNmUserDataTxPdu ;
/* false: Only NM messages with an with CRI bit = true and containing an PN request for this ECU
 *  triggers the standard RX indication handling
 *                                                 true: Every NM message triggers the standard
 *  RX indication handling
 */
/* Specifies if CanNm drops irrelevant NM messages. */
	boolean CanNmAllNmMessagesKeepAwake ;
/* This parameter defines if bus load reduction for the respective NM channel is active or not. */
	boolean CanNmBusLoadReductionActive ;
/* Specifies the Bit position of the CWU within the NM-Message. */
	uint8 CanNmCarWakeUpBitPosition ;
/* Specifies the Byte position of the CWU within the NM-Message. */
	uint8 CanNmCarWakeUpBytePosition ;
/* FALSE - CWU filtering is not supported
 *                                                 TRUE - CWU filtering is supported
 */
/* If CWU filtering is supported, only the CWU bit within the NM message with source node identifier
 *  CanNmCarWakeUpFilterNodeId is considered as CWU request.
 */
	boolean CanNmCarWakeUpFilterEnabled ;
/* Source node identifier for CWU filtering. If CWU filtering is supported, only the CWU bit within
 *  the NM message with source node identifier CanNmCarWakeUpFilterNodeId is considered as CWU
 *  request.
 */
	uint8 CanNmCarWakeUpFilterNodeId ;
/* FALSE - CarWakeUp not supported
 *                                                 TRUE - CarWakeUp supported
 */
/* Enables or disables support of CarWakeUp bit evaluation in received NM messages. */
	boolean CanNmCarWakeUpRxEnabled ;
/* Defines the immediate NM PDU cycle time in seconds which is used for CanNmImmediateNmTransmissions
 *  NM PDU transmissions. This parameter is only valid if CanNmImmediateNmTransmissions is greater
 *  one.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 CanNmImmediateNmCycleTime ;
/* Defines the number of immediate NM PDUs which shall be transmitted. If the value is zero no
 *  immediate NM PDUs are transmitted. The cycle time of immeditate NM PDUs is defined by CanNmImmediateNmCycleTime.
 */
	uint8 CanNmImmediateNmTransmissions ;
/* This parameter is only valid if CanNmPassiveModeEnabled is False. */
/* Time offset in the periodic transmission node. It determines the start delay of the transmission.
 *  Specified in seconds.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 CanNmMsgCycleOffset ;
/* This parameter is only valid if CanNmPassiveModeEnabled is False. */
/* Period of a NM-message in seconds. It determines the periodic rate in the "periodic transmission
 *  mode with bus load reduction" and is the basis for transmit scheduling in the "periodic transmission
 *  mode without bus load reduction".
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 CanNmMsgCycleTime ;
/* This parameter is only valid if 
 *                                                 CanNmBusLoadReductionEnabled == True and
 *                                                 CanNmBusLoadReductionActive == True and
 *                                                 CanNmPassiveModeEnabled == False
 * 
 *                                                 Otherwise this parameter is not used.
 */
/* Node specific bus cycle time in the periodic transmission mode with bus load reduction. Specified
 *  in seconds.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 CanNmMsgReducedTime ;
/* This parameter is only valid if CANNM_PASSIVE_MODE_ENABLED is disabled. */
/* Transmission Timeout of NM-message. If there is no transmission confirmation by the CAN Interface
 *  within this timeout, the CANNM module shall give an error notification.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 CanNmMsgTimeoutTime ;
/* This parameter is only valid if
 *                                                 CanNmPassiveModeEnabled = False and
 *                                                 CanNmNodeDetectionEnabled = True
 */
/* Node identifier of local node. */
	uint8 CanNmNodeId ;
/* The value of the parameter represents the location of the control bit vector in the NM PDU (CanNmPduByte0
 *  means byte 0, CanNmPduByte1 means byte 1, CanNmPduOff means source node identifier is not part
 *  of the NM PDU)
 * 
 *                                                 if(CANNM_PDU_CBV_POSITION != CANNM_PDU_OFF &&
 *  CANNM_PDU_NID_POSITION != CANNM_PDU_OFF) then CANNM_PDU_CBV_POSITION != CANNM_PDU_NID_POSITION
 * 
 *                                                 if(CANNM_PDU_CBV_POSITION != CANNM_PDU_OFF &&
 *  CANNM_PDU_NID_POSITION == CANNM_PDU_OFF) then CANNM_PDU_CBV_POSITION = CANNM_PDU_BYTE0
 * 
 *                                                 ImplementationType: CanNm_PduPositionType
 */
	CanNm_PduCbvPositionType CanNmPduCbvPosition ;
/* The value of the parameter represents the location of the source node identifier in the NM PDU
 *  (CanNMPduByte0 means byte 0, CanNmPduByte1 means byte 1, CanNmPduOff means source node identifier
 *  is not part of the NM PDU)
 * 
 *                                                 if(CANNM_PDU_NID_POSITION != CANNM_PDU_OFF &&
 *  CANNM_PDU_CBV_POSITION != CANNM_PDU_OFF) then CANNM_PDU_NID_POSITION != CANNM_PDU_CBV_POSITION
 * 
 *                                                 if(CANNM_PDU_NID_POSITION != CANNM_PDU_OFF &&
 *  CANNM_PDU_CBV_POSITION == CANNM_PDU_OFF) then CANNM_PDU_NID_POSITION = CANNM_PDU_BYTE0
 * 
 *                                                 ImplementationType: CanNm_PduPositionType
 */
	CanNm_PduNidPositionType CanNmPduNidPosition ;
/* false: Partial networking Range not supported
 *                                                 true: Partial networking supported
 */
/* Enables or disables support of partial networking. */
	boolean CanNmPnEnabled ;
/* false: PN request are not calculated
 *                                                 true: PN request are calculated
 */
/* Specifies if CanNm calculates the PN request information for external requests. (ERA) */
	boolean CanNmPnEraCalcEnabled ;
/* true: CanNm_NetworkRequest triggers a change from NO to RM. */
/* false: CanNm_NetworkRequest is ignored in NO. */
	boolean CanNmPnHandleMultipleNetworkRequests ;
/* It defines the time in seconds how long it shall take to recognize that all other nodes are
 *  ready to sleep. 
 * 
 *                                                 Typically it should be equal to: n * CanNmMsgCycleTime,
 *  where n denotes the number of NM-Messages that are normally sent before Remote Sleep Indication
 *  is detected. 
 *                                                 The value of n decremented by one determines
 *  the amount of lost NM-Messages that can be tolerated by the Remote Sleep Indication procedure.
 *  
 *                                                 The value 0 denotes that no Remote Sleep Indication
 *  functionality is configured.
 */
/* Timeout for Remote Sleep Indication. */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 CanNmRemoteSleepIndTime ;
/* It defines the time in seconds how long the NM shall stay in the Repeat Message State.
 * 
 *                                                 Typically it should be equal to: n * CanNmMsgCycleTime,
 *  where n denotes the number of NM-Messages that are normally sent in the Repeat Message State.
 *  
 *                                                 The value of n decremented by one determines
 *  the amount of lost NM-Messages that can be tolerated by the node detection procedure. 
 *                                                 The value 0 denotes that no Repeat Message State
 *  is configured. It means that Repeat Message State is transient what implicates that it is left
 *  immediately after entrance and in result no start-up stability is guaranteed and no node detection
 *  procedure is possible.
 */
/* Timeout for Repeat Message State. */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 CanNmRepeatMessageTime ;
/* It denotes the time in seconds how long the NM shall stay in the Network Mode before transition
 *  into Prepare Bus-Sleep Mode shall take place.
 * 
 *                                                 It shall be equal for all nodes in the cluster.
 *  
 *                                                 It shall be greater than CanNmMsgCycleTime.
 *                                                 Typically it should be equal to: n * CanNmMsgCycleTime,
 *  where n denotes the number of NM-Message cycle times in the Ready Sleep State before transition
 *  into the Bus-Sleep Mode is initiated. The value of n decremented by one determines the amount
 *  of lost NM-Messages that can be tolerated by the coordination algorithm.
 */
/* Network Timeout for NM-Messages. */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 CanNmTimeoutTime ;
/* Defines the length of the user data contained in the NM PDU */
	uint8 CanNmUserDataLength ;
/* It denotes the time in seconds how long the NM shall stay in the Prepare Bus-Sleep Mode before
 *  transition into Bus-Sleep Mode shall take place. 
 * 
 *                                                 It shall be equal for all nodes in the cluster.
 *  
 *                                                 It shall be long enough to make all Tx-buffer
 *  empty.
 */
/* Timeout for bus calm down phase. */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 CanNmWaitBusSleepTime ;
/* Reference to a Pdu in the COM-Stack. The SduRef is required for every CanNm Channel, because
 *  ERA is reported per channel.
 */
/* /AUTOSAR/EcucDefs/EcuC/EcucPduCollection/Pdu */
	EcuC_PduType* CanNmPnEraRxNSduRef ;
/* This reference points to the unique channel defined by the ComMChannel and provides access to
 *  the unique channel index value in ComMChannelId.
 */
/* /AUTOSAR/EcucDefs/ComM/ComMConfigSet/ComMChannel */
	ComM_ChannelType* CanNmComMNetworkHandleRef ;
} CanNm_ChannelConfigType ;

/* PN information configuration */
typedef struct
{
/* Specifies the offset of the PN request information in the NM message. */
	uint8 CanNmPnFilterMaskByteIndex ;
/* Parameter to configure the filter mask byte. */
	uint8 CanNmPnFilterMaskByteValue ;
} CanNm_PnFilterMaskByteType ;

/* PN information configuration */
typedef struct
{
	CanNm_PnFilterMaskByteType* CanNmPnFilterMaskByte ;
/* Specifies the length of the PN request information in the NM message. */
	uint8 CanNmPnInfoLength ;
/* Specifies the offset of the PN request information in the NM message. */
	uint8 CanNmPnInfoOffset ;
} CanNm_PnInfoType ;

/* This container contains the global configuration parameter of the CanNm. The parameters and
 *  the parameters of the sub containers shall be mapped to the C data type CanNm_ConfigType (for
 *  parameters where it is possible) which is passed to the CanNm_Init function.
 */
typedef struct
{
	CanNm_ChannelConfigType* CanNmChannelConfig ;
	CanNm_PnInfoType* CanNmPnInfo ;
/* Pre-processor switch for enabling busload reduction support. */
	boolean CanNmBusLoadReductionEnabled ;
/* calculationFormula = If (CanNmPassiveModeEnabled == False) then Equal(NmBusSynchronizationEnabled)
 *  else Equal(False)
 */
/* Pre-processor switch for enabling bus synchronization support. This feature is required for
 *  gateway nodes only.
 */
	boolean CanNmBusSynchronizationEnabled ;
/* calculationformula = Equal(NmComControlEnabled) */
/* Pre-processor switch for enabling the Communication Control support. */
	boolean CanNmComControlEnabled ;
/* Enable/disable the user data support. */
	boolean CanNmComUserDataSupport ;
/* Enables/disables the coordinator synchronisation support. */
	boolean CanNmCoordinatorSyncSupport ;
/* Pre-processor switch for enabling development error detection support. */
	boolean CanNmDevErrorDetect ;
/* Pre-processor switch for enabling the asynchronous transmission of a NM PDU upon bus-communication
 *  request in Prepare-Bus-Sleep mode.
 */
	boolean CanNmImmediateRestartEnabled ;
/* Enable/disable the immediate tx confirmation. */
	boolean CanNmImmediateTxconfEnabled ;
/* Call cycle in seconds of CanNm_MainFunction. */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 CanNmMainFunctionPeriod ;
/* Precompile time switch to enable the node detection feature. */
	boolean CanNmNodeDetectionEnabled ;
/* Number of Can NM channels allowed within one ECU. */
	uint8 CanNmNumberOfChannels ;
/* calculationFormula = Equal(NmPassiveModeEnabled) */
/* Pre-processor switch for enabling support of the Passive Mode. */
	boolean CanNmPassiveModeEnabled ;
/* calculationFormula = Equal(NmPduRxIndicationEnabled) */
/* Pre-processor switch for enabling the PDU Rx Indication. */
	boolean CanNmPduRxIndicationEnabled ;
/* true: PN request are calculated
 *                                         false: PN request are not calculated
 */
/* Specifies if CanNm calculates the PN request information for internal an external requests. (EIRA) */
	boolean CanNmPnEiraCalcEnabled ;
/* Specifies the runtime of the reset timer in seconds. This reset time is valid for the reset
 *  of PN requests in the EIRA and in the ERA. The value shall be the same for every channel. Thus
 *  it is a global config parameter.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 CanNmPnResetTime ;
/* calculationFormula = If (CanNmPassiveModeEnabled == False) then Equal(NmRemoteSleepIndEnabled)
 *  else Equal(False)
 */
/* Pre-processor switch for enabling remote sleep indication support. This feature is required
 *  for gateway nodes only.
 */
	boolean CanNmRemoteSleepIndEnabled ;
/* calculationformula = Equal(NmRepeatMsgIndEnabled) */
/* Enable/disable the notification that a RepeatMessageRequest bit has been received. */
	boolean CanNmRepeatMsgIndEnabled ;
/* calculationFormula = Equal(NmStateChangeIdEnabled) */
/* Pre-processor switch for enabling the CAN NM state change notification. */
	boolean CanNmStateChangeIndEnabled ;
/* calculationFormula = Equal(NmUserDataEnabled) */
/* Pre-processor switch for enabling user data support. */
	boolean CanNmUserDataEnabled ;
/* Pre-processor switch for enabling version info API support. */
	boolean CanNmVersionInfoApi ;
/* Reference to a Pdu in the COM-Stack. */
/* Only one SduRef is required for CanNm because the EIRA is the aggregation over all Can Channels. */
/* /AUTOSAR/EcucDefs/EcuC/EcucPduCollection/Pdu */
	EcuC_PduType* CanNmPnEiraRxNSduRef ;
} CanNm_GlobalConfigType ;

/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __cplusplus
}}  /* name space */
#endif
#endif /* CANNM_TYPES_H */

