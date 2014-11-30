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
#ifndef FRNM_TYPES_H
#define FRNM_TYPES_H

#ifdef __cplusplus
namespace autosar {
extern "C" {
#endif
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* This container describes the FlexRay NM RX PDU:s. */
typedef struct
{
/* This parameted defines if the PDU contains NM Data. */
	boolean FrNmRxPduContainsData ;
/* This parameted defines if the PDU contains NM Vote information. */
	boolean FrNmRxPduContainsVote ;
/* It is used for referring to the FlexRay Interface receive function. 
 *                                                                 It must be consistent with the
 *  value configured in the FlexRay Interface.
 *                                                                 This ID is used for the combined
 *  reception of NM Vote and NM Data or for the reception of the NM Vote if NM Data is received
 *  in a separate PDU.
 * 
 *                                                                 ImplementationType: PduIdType
 */
/* PDU identifier configured for the respective FlexRay Channel. */
	uint16 FrNmRxPduId ;
} FrNm_RxPduType ;

/* This container describes the FlexRay NM TX PDU:s. */
typedef struct
{
/* Handle Id to be used by the Lower Layer to confirm the transmission of the FrNmTxPdu to the
 *  LowerLayer.
 */
	uint16 FrNmTxConfirmationPduId ;
/* This parameted defines if the PDU contains NM Data. */
	boolean FrNmTxPduContainsData ;
/* This parameted defines if the PDU contains NM Vote information. */
	boolean FrNmTxPduContainsVote ;
} FrNm_TxPduType ;

/* This optional container is used to configure the UserNm PDU. This container is only available
 *  if FrNmComUserDataSupport is enabled.
 */
typedef struct
{
/* This parameter defines the Handle ID of the NM User Data I-PDU. */
	uint16 FrNmTxUserDataPduId ;
} FrNm_UserDataTxPduType ;

/* This parameter defines the PDU scheduling variant that should be used for this channel. */
typedef enum
{
	FRNM_PDU_SCHEDULE_VARIANT_1,
	FRNM_PDU_SCHEDULE_VARIANT_2,
	FRNM_PDU_SCHEDULE_VARIANT_3,
	FRNM_PDU_SCHEDULE_VARIANT_4,
	FRNM_PDU_SCHEDULE_VARIANT_5,
	FRNM_PDU_SCHEDULE_VARIANT_6,
	FRNM_PDU_SCHEDULE_VARIANT_7,
} FrNm_PduScheduleVariantType ;

/* This container contains instance specific identifiers related to the respective FlexRay Channel. */
typedef struct
{
	FrNm_RxPduType* FrNmRxPdu ;
	FrNm_TxPduType* FrNmTxPdu ;
	FrNm_UserDataTxPduType* FrNmUserDataTxPdu ;
/* Specifies the Bit position of the CWU within the NM-Message. */
	uint8 FrNmCarWakeUpBitPosition ;
/* Specifies the Byte position of the CWU within the NM-Message. */
	uint8 FrNmCarWakeUpBytePosition ;
/* FrNmCarWakeUpFilterNodeId is considered as CWU request.
 *                                                         FALSE - CWU Filtering is not supported
 *                                                         TRUE - CWU Filtering is supported
 */
/* If CWU filtering is supported, only the CWU bit within the NM message with source node identifier */
	boolean FrNmCarWakeUpFilterEnabled ;
/* message with source node identifier FrNmCarWakeUpFilterNodeId is considered as CWU
 *                                                         request.
 */
/* Source node identifier for CWU filtering. If CWU filtering is supported, only the CWU bit within
 *  the NM
 */
	uint8 FrNmCarWakeUpFilterNodeId ;
/* FALSE - CarWakeUp not supported
 *                                                         TRUE - CarWakeUp supported
 */
/* Enables or disables support of CarWakeUp bit evaluation in received NM messages. */
	boolean FrNmCarWakeUpRxEnabled ;
/* This parameter is used to activate or deactivate the control bit vector support for a Fr Nm
 *  Channel.
 */
	boolean FrNmControlBitVectorActive ;
/* It is used for identifying the respective NM node in the NM-cluster. 
 *                                                         It must be unique for each NM node within
 *  one NM cluster.
 */
/* NM node identifier configured for the respective FlexRay Channel. */
	uint8 FrNmNodeId ;
/* Option 1	NM-Vote and NM-Data in static segment (one PDU)
 *                                                         Option 2	NM-Vote and NM-Data in dynamic
 *  segment (one PDU)
 *                                                         Option 3	NM-Vote and NM-Data in static
 *  segment (separate PDU)
 *                                                         Option 4	NM-Vote in static segment and
 *  NM-Data in dynamic segment
 *                                                         Option 5	NM-Vote in dynamic segment
 *  and NM-Data in static segment
 *                                                         Option 6	NM-Vote and NM-Data in dynamic
 *  segment (separate PDU)
 *                                                         Option 7	Combined NM-Vote and CBV in
 *  static segment and NM-Data in dynamic segment
 */
	FrNm_PduScheduleVariantType FrNmPduScheduleVariant ;
/* false: Partial networking Range not supported
 *                                                         true: Partial networking supported
 */
/* Enables or disables support of partial networking. */
	boolean FrNmPnEnabled ;
/* false: PN request are not calculated
 *                                                         true: PN request are calculated
 */
/* Specifies if FrNm calculates the PN request information for external requests. (ERA) */
	boolean FrNmPnEraCalcEnabled ;
/* This parameter is used to activate or deactivate the repeat message bit support for a Fr Nm
 *  Channel.
 */
	boolean FrNmRepeatMessageBitActive ;
/* This parameter defines if this channel shall provide the synchronization point indication to
 *  the NM Interface.
 */
	boolean FrNmSynchronizationPointEnabled ;
} FrNm_ChannelIdentifiersType ;

/* Number of FlexRay Schedule Cycles needed to transmit the NM Data of all ECUs on the FlexRay bus */
typedef enum
{
	FRNM_CYCLE_VALUE_1,
	FRNM_CYCLE_VALUE_16,
	FRNM_CYCLE_VALUE_2,
	FRNM_CYCLE_VALUE_32,
	FRNM_CYCLE_VALUE_4,
	FRNM_CYCLE_VALUE_64,
	FRNM_CYCLE_VALUE_8,
} FrNm_DataCycleType ;

/* Number of Flexray Schedule Cycles used to repeat the transmission of the Nm vote of all ECUs
 *  on the Flexray Bus.
 */
typedef enum
{
	FRNM_CYCLE_VALUE_1,
	FRNM_CYCLE_VALUE_16,
	FRNM_CYCLE_VALUE_2,
	FRNM_CYCLE_VALUE_32,
	FRNM_CYCLE_VALUE_4,
	FRNM_CYCLE_VALUE_64,
	FRNM_CYCLE_VALUE_8,
} FrNm_RepetitionCycleType ;

/* Number of FlexRay Schedule Cycles needed to transmit the Nm vote of all ECUs on the FlexRay Bus. */
typedef enum
{
	FRNM_CYCLE_VALUE_1,
	FRNM_CYCLE_VALUE_16,
	FRNM_CYCLE_VALUE_2,
	FRNM_CYCLE_VALUE_32,
	FRNM_CYCLE_VALUE_4,
	FRNM_CYCLE_VALUE_64,
	FRNM_CYCLE_VALUE_8,
} FrNm_VotingCycleType ;

/* This container contains instance-specific timing related to the respective FlexRay  Channel. */
typedef struct
{
	FrNm_DataCycleType FrNmDataCycle ;
/* This parameter defines the processing cycle of the main function of FrNm module in seconds. */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 FrNmMainFunctionPeriod ;
/* Timeout  of a NM-message. It determines in seconds how long the NM shall wait with notification
 *  of transmission failure while communication errors occur on the bus.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 FrNmMsgTimeoutTime ;
/* On a value of "1", the NM-State Machine will leave the Ready Sleep State after one NM Repetition
 *  Cycle with no "keep awake" votes.
 */
/* Numbers of repetitions in the ready sleep state before NM switches to bus sleep mode. */
	uint16 FrNmReadySleepCnt ;
/* The value "0" denotes that no Remote Sleep Indication functionality is configured. */
/* Timeout for Remote Sleep Indication. It defines the time in seconds how long it shall take to
 *  recognize that all other nodes are ready to sleep.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 FrNmRemoteSleepIndTime ;
/* The value "0" denotes that no Repeat Message State is configured, which means that Repeat Message
 *  State is transient and implies that it is left immediately after entry and consequently no
 *  startup stability is guaranteed and no node detection procedure is possible.
 */
/* Timeout for Repeat Message State. Defines the time in seconds how long the NM shall stay in
 *  the Repeat Message State.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 FrNmRepeatMessageTime ;
	FrNm_RepetitionCycleType FrNmRepetitionCycle ;
/* Initial value for the SyncLossTimer in seconds. */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 FrNmSyncLossTimer ;
/* Pre-processor switch for enabling the inhibition of vote changes from the next-to-last repetition
 *  cycle to the last repetition cycle before the Ready Sleep Counter expires.
 */
	boolean FrNmVoteInhibitionEnabled ;
	FrNm_VotingCycleType FrNmVotingCycle ;
} FrNm_ChannelTimingType ;

/* This container contains the configuration parameters for a FlexRay NM Channel. */
typedef struct
{
	FrNm_ChannelIdentifiersType* FrNmChannelIdentifiers ;
	FrNm_ChannelTimingType* FrNmChannelTiming ;
} FrNm_ChannelType ;

/* This container contains module constants related to the FlexRay NM functionality. */
typedef struct
{
/* Number of AUTOSAR FR NM clusters allowed within one ECU. */
	uint8 FrNmNumberOfClusters ;
} FrNm_GlobalConstantsType ;

/* Filter mask byte configuration */
typedef struct
{
/* Index of the filter mask byte. Specifies the position within the filter mask byte array. */
	uint8 FrNmPnFilterMaskByteIndex ;
/* Parameter to configure the filter mask byte. */
	uint8 FrNmPnFilterMaskByteValue ;
} FrNm_PnFilterMaskByteType ;

/* PN information configuration */
typedef struct
{
	FrNm_PnFilterMaskByteType* FrNmPnFilterMaskByte ;
/* Specifies the length of the PN request information in the NM message. */
	uint8 FrNmPnInfoLength ;
/* Specifies the offset of the PN request information in the NM message. */
	uint8 FrNmPnInfoOffset ;
} FrNm_PnInfoType ;

/* This container contains module features related to the FlexRay NM functionality. */
typedef struct
{
	FrNm_PnInfoType* FrNmPnInfo ;
/* Pre-processor switch for enabling the bus synchronisation. */
	boolean FrNmBusSynchronizationEnabled ;
/* Enable/disable the user data support. */
	boolean FrNmComUserDataSupport ;
/* calculationFormula = If (FrNmNodeDetectionEnabled == False) then Equal(False) else Equal(False
 *  or True)
 */
/* Pre-processor switch for enabling control bit vector support. */
	boolean FrNmControlBitVectorEnabled ;
/* Enables/disables the coordinator synchronisation support. */
	boolean FrNmCoordinatorSyncSupport ;
/* Pre-processor switch for enabling the cycle counter emulation. */
	boolean FrNmCycleCounterEmulation ;
/* Pre-processor switch for enabling the support of dual channel transmission and reception of
 *  NM messages.
 */
	boolean FrNmDualChannelPduEnable ;
/* Pre-processor switch for enabling the processing of FlexRay Hardware aggregated NM-Votes. */
	boolean FrNmHwVoteEnable ;
/* calculationFormula = If (FrNmPassiveModeEnabled == False) then Equal(NmNodeDetectionEnabled)
 *  else Equal(False)
 */
/* Pre-processor switch for enabling node detection support. */
	boolean FrNmNodeDetectionEnabled ;
/* calculationFormula = Equal(NmPassiveModeEnabled) */
/* Pre-processor switch for enabling Passive Mode Configuration support. */
	boolean FrNmPassiveModeEnabled ;
/* Pre-processor switch for enabling PDU reception indication. */
	boolean FrNmPduRxIndicationEnabled ;
/* true: PN request are calculated
 *                                                 false: PN request are not calculated
 */
/* Specifies if FrNm calculates the PN request information for internal an external requests. (EIRA) */
	boolean FrNmPnEiraCalcEnabled ;
/* Specifies the runtime of the reset timer in seconds. This reset time is valid for the reset
 *  of PN requests in the EIRA and in the ERA. The value shall be the same for every channel. Thus
 *  it is a global config parameter.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 FrNmPnResetTime ;
/* calculationFormula = If (FrNmPassiveModeEnabled == True) then Equal(False) else Equal(False
 *  or True)
 */
/* Pre-processor switch for enabling remote sleep indication. */
	boolean FrNmRemoteSleepIndicationEnabled ;
/* Pre-processor switch for enabling the repeat message bit support. */
	boolean FrNmRepeatMessageBitEnabled ;
/* Pre-processor switch for enabling SourceNodeIdentifier support. */
	boolean FrNmSourceNodeIdentifierEnabled ;
/* Pre-processor switch for enabling state change indication. */
	boolean FrNmStateChangeIndicationEnabled ;
/* Pre-processor switch for enabling user data support. */
	boolean FrNmUserDataEnabled ;
/* repetition cycles before the Ready Sleep Counter expires. */
/* Pre-processor switch for disabling vote changes in the last two */
	boolean FrNmVotingNextToLastRepetitionCycleDisable ;
} FrNm_GlobalFeaturesType ;

/* This container contains module properties related to the FlexRay NM functionality. */
typedef struct
{
/* Pre-processor switch for enabling development error detection */
	boolean FrNmDevErrorDetect ;
/* Parameter describing if the execution of FrNm_Main function crosses the FlexRay cycle boundary
 *  or not.
 */
	boolean FrNmMainAcrossFrCycle ;
/* Pre-processor switch for enabling version info API support. */
	boolean FrNmVersionInfoApi ;
} FrNm_GlobalPropertiesType ;

/* This container contains the configuration parameters for all FlexRay NM channels. */
typedef struct
{
	FrNm_ChannelType* FrNmChannel ;
} FrNm_ChannelConfigType ;

/* This container contains all global configuration parameters for the FrNm module. */
typedef struct
{
	FrNm_GlobalConstantsType* FrNmGlobalConstants ;
	FrNm_GlobalFeaturesType* FrNmGlobalFeatures ;
	FrNm_GlobalPropertiesType* FrNmGlobalProperties ;
} FrNm_GlobalConfigType ;

/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __cplusplus
}}  /* name space */
#endif /* FRNM_TYPES_H */

