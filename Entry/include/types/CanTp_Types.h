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
#ifndef CANTP_TYPES_H
#define CANTP_TYPES_H

/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
#ifdef __cplusplus
namespace autosar {
extern "C" {
#endif
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* Used for grouping of the ID of a PDU and the Reference to a PDU. */
typedef struct
{
/* Each RxNsdu identifier is linked to only one SF/FF/CF N-PDU identifier. 
 *                                                                 Nevertheless, in the case of
 *  extended or mixed addressing format, the same N-PDU identifier can be used for several N-SDU
 *  identifiers. The distinction is made by the N_TA or N_AE value (first data byte 
 *                                                                 of SF or FF frames).
 */
/* The N-PDU identifier attached to the RxNsdu is identified by CanTpRxNSduId. */
	uint16 CanTpRxNPduId ;
/* Reference to a Pdu in the COM-Stack. */
/* /AUTOSAR/EcucDefs/EcuC/EcucPduCollection/Pdu */
	EcuC_PduType* CanTpRxNPduRef ;
} CanTp_RxNPduType ;

/* Used for grouping of the ID of a PDU and the Reference to a PDU. */
typedef struct
{
/* Handle Id to be used by the CanIf to confirm the transmission of the CanTpTxFcNPdu to the CanIf
 *  module.
 */
	uint16 CanTpTxFcNPduConfirmationPduId ;
/* Reference to a Pdu in the COM-Stack. */
/* /AUTOSAR/EcucDefs/EcuC/EcucPduCollection/Pdu */
	EcuC_PduType* CanTpTxFcNPduRef ;
} CanTp_TxFcNPduType ;

/* Declares which communication addressing mode is supported for this Rx N-SDU. */
typedef enum
{
	CANTP_EXTENDED,
	CANTP_MIXED,
	CANTP_STANDARD
} CanTp_RxAddressingFormatType ;

/* Defines if the receive frame uses padding or not. */
typedef enum
{
	CANTP_OFF,
	CANTP_ON
} CanTp_RxPaddingActivationType ;

/* Declares the communication type of this Rx N-SDU. */
typedef enum
{
	CANTP_FUNCTIONAL,
	CANTP_PHYSICAL
} CanTp_RxTaTypeType ;

/* The following parameters needs to be configured for each CAN N-SDU that the CanTp module receives
 *  via the CanTpChannel.
 */
typedef struct
{
	CanTp_NAeType* CanTpNAe ;
	CanTp_NSaType* CanTpNSa ;
	CanTp_NTaType* CanTpNTa ;
	CanTp_RxNPduType* CanTpRxNPdu ;
	CanTp_TxFcNPduType* CanTpTxFcNPdu ;
/* Sets the number of N-PDUs the CanTp receiver allows the sender to send, before waiting for an
 *  authorization to continue transmission of the following N-PDUs.For further details on this
 *  parameter value see ISO 15765-2 specification.
 */
	uint8 CanTpBs ;
/* Value in seconds of the N_Ar timeout. N_Ar is the time for transmission of a CAN frame (any
 *  N_PDU) on the receiver side.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 CanTpNar ;
/* Value in seconds of the performance requirement for (N_Br + N_Ar). N_Br is the elapsed time
 *  between the receiving indication of a FF or CF or the transmit confirmation of a FC, until
 *  the transmit request of the next FC.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 CanTpNbr ;
/* Value in seconds of the N_Cr timeout. N_Cr is the time until reception of the next Consecutive
 *  Frame N_PDU.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 CanTpNcr ;
/* Enum values:
 *                                                         CanTpStandard. To use normal addressing
 *  format.
 *                                                         CanTpExtended. To use extended addressing
 *  format.
 *                                                         CanTpMixed. To use mixed addressing
 *  format.
 */
	CanTp_RxAddressingFormatType CanTpRxAddressingFormat ;
/* Depending on SF or FF N-SDU the value will be limited to 7 (6 for an extended addressing format)
 *  and 4095 respectively.
 */
/* Data Length Code of this RxNsdu. In case of variable message length, this value indicates the
 *  minimum data length.
 */
	uint16 CanTpRxDl ;
/* Unique identifier user by the upper layer to call CanTp_CancelReceive, CanTp_ChangeParameter
 *  and CanTp_ReadParameter.
 */
	uint16 CanTpRxNSduId ;
/* Definition of enumeration values:
 * 
 *                                                         CanTpOn:
 *                                                         The N-PDU received uses padding for
 *  SF, FC and the last CF. (N-PDU length is always 8 bytes)
 * 
 *                                                         CanTpOff:
 *                                                         The N-PDU received does not use padding
 *  for SF, CF and the last CF. (N-PDU length is dynamic)
 */
	CanTp_RxPaddingActivationType CanTpRxPaddingActivation ;
	CanTp_RxTaTypeType CanTpRxTaType ;
/* CanTpRxWftMax is used to avoid sender nodes being potentially hooked-up in case of a temporarily
 *  reception inability on the part of the receiver nodes, whereby the sender could be waiting
 *  continuously.
 */
/* This parameter indicates how many Flow Control wait N-PDUs can be consecutively transmitted
 *  by the receiver. It is local to the node and is not transmitted inside the FC protocol data
 *  unit.
 */
	uint16 CanTpRxWftMax ;
/* For further details on this parameter value see ISO 15765-2 specification. */
/* Sets the duration of the minimum time the CanTp sender shall wait between the transmissions
 *  of two CF N-PDUs.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 CanTpSTmin ;
/* Reference to a Pdu in the COM-Stack. */
/* /AUTOSAR/EcucDefs/EcuC/EcucPduCollection/Pdu */
	EcuC_PduType* CanTpRxNSduRef ;
} CanTp_RxNSduType ;

/* Used for grouping of the ID of a PDU and the Reference to a PDU. */
typedef struct
{
/* Each TxNsdu identifier is linked to one Rx FC N-PDU identifier only. However, in the case of
 *  extended addressing format, the same FC N-PDU identifier can be used for several N-SDU identifiers.
 *  The distinction is made by means of the N_TA value (first data byte of FC frames).
 */
/* N-PDU identifier attached to the FC N-PDU of this TxNsdu identified by CanTpTxNSduId. */
	uint16 CanTpRxFcNPduId ;
/* Reference to a Pdu in the COM-Stack. */
/* /AUTOSAR/EcucDefs/EcuC/EcucPduCollection/Pdu */
	EcuC_PduType* CanTpRxFcNPduRef ;
} CanTp_RxFcNPduType ;

/* Used for grouping of the ID of a PDU and the Reference to a PDU. */
typedef struct
{
/* Handle Id to be used by the CanIf to confirm the transmission of the CanTpTxNPdu to the CanIf
 *  module.
 */
	uint16 CanTpTxNPduConfirmationPduId ;
/* Reference to a Pdu in the COM-Stack. */
/* /AUTOSAR/EcucDefs/EcuC/EcucPduCollection/Pdu */
	EcuC_PduType* CanTpTxNPduRef ;
} CanTp_TxNPduType ;

/* Declares which communication addressing format is supported for this TxNsdu. */
typedef enum
{
	CANTP_EXTENDED,
	CANTP_MIXED,
	CANTP_STANDARD
} CanTp_TxAddressingFormatType ;

/* Defines if the transmit frame use padding or not. */
typedef enum
{
	CANTP_OFF,
	CANTP_ON
} CanTp_TxPaddingActivationType ;

/* Declares the communication type of this TxNsdu. */
typedef enum
{
	CANTP_FUNCTIONAL,
	CANTP_PHYSICAL
} CanTp_TxTaTypeType ;

/* The following parameters needs to be configured for each CAN N-SDU that the CanTp module transmits
 *  via the CanTpChannel.
 */
typedef struct
{
	CanTp_NAeType* CanTpNAe ;
	CanTp_NSaType* CanTpNSa ;
	CanTp_NTaType* CanTpNTa ;
	CanTp_RxFcNPduType* CanTpRxFcNPdu ;
	CanTp_TxNPduType* CanTpTxNPdu ;
/* Value in second of the N_As timeout. N_As is the time for transmission of a CAN frame (any N_PDU)
 *  on the part of the sender.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 CanTpNas ;
/* Value in seconds of the N_Bs timeout. N_Bs is the time of transmission until reception of the
 *  next Flow Control N_PDU.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 CanTpNbs ;
/* Value in seconds of the performance requirement of (N_Cs + N_As). N_Cs is the time which elapses
 *  between the transmit request of a CF N-PDU until the transmit request of the next CF N-PDU.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 CanTpNcs ;
/* switch for enabling Transmit Cancellation. */
	boolean CanTpTc ;
/* Definition of Enumeration values:
 *                                                         CanTpStandard to use normal addressing
 *  format.
 *                                                         CanTpExtended to use extended addressing
 *  format (the N_TA container of this TxNsdu will be used).
 *                                                         CanTpMixed to use mixed addressing format
 *  (the N_AE container of this TxNsdu will be used).
 */
	CanTp_TxAddressingFormatType CanTpTxAddressingFormat ;
/* Data Length Code of this TxNsdu. In case of variable length message, this value indicates the
 *  minimum data length.
 */
	uint16 CanTpTxDl ;
/* Unique identifier to a structure that contains all useful information to process the transmission
 *  of a TxNsdu.
 */
	uint16 CanTpTxNSduId ;
/* Definition of Enumeration values:
 * 
 *                                                         CanTpOn
 *                                                         The transmit N-PDU uses padding for
 *  SF, FC and the last CF. (N-PDU length is always 8 bytes)
 * 
 *                                                         CanTpOff
 *                                                         The transmit N-PDU does not use padding
 *  for SF, CF and the last CF. (N-PDU length is dynamic)
 */
	CanTp_TxPaddingActivationType CanTpTxPaddingActivation ;
/* Enumeration values:
 *                                                         CanTpPhysical. Used for 1:1 communication.
 *                                                         CanTpFunctional. Used for 1:n communication.
 */
	CanTp_TxTaTypeType CanTpTxTaType ;
/* Reference to a Pdu in the COM-Stack. */
/* /AUTOSAR/EcucDefs/EcuC/EcucPduCollection/Pdu */
	EcuC_PduType* CanTpTxNSduRef ;
} CanTp_TxNSduType ;

/* The CAN Transport Layer supports half and full duplex channel modes. */
typedef enum
{
	CANTP_MODE_FULL_DUPLEX,
	CANTP_MODE_HALF_DUPLEX
} CanTp_ChannelModeType ;

/* This container contains the configuration parameters of the CanTp channel. */
typedef struct
{
	CanTp_RxNSduType* CanTpRxNSdu ;
	CanTp_TxNSduType* CanTpTxNSdu ;
	CanTp_ChannelModeType CanTpChannelMode ;
} CanTp_ChannelType ;

/* This container contains the configuration parameters and sub containers of the AUTOSAR CanTp
 *  module. This container is a MultipleConfigurationContainer, i.e. this container and its sub-containers
 *  exist once per configuration set.
 */
typedef struct
{
	CanTp_ChannelType* CanTpChannel ;
/* Allow to configure the time for the MainFunction (as float in seconds). Please note: This period
 *  shall be the same as call cycle time of the periodic task were CanTp Main function is called.
 */
/* in fact, it should be type <float> according to arxml, but only supported in tool side*/
	uint64 CanTpMainFunctionPeriod ;
} CanTp_ConfigType ;

/* This container contains the general configuration parameters of the CanTp module. */
typedef struct
{
/* This parameter, if set to true, enables the CanTp_ChangeParameterRequest Api for this Module. */
	boolean CanTpChangeParameterApi ;
/* Switches the Development Error Detection and Notification ON or OFF */
	boolean CanTpDevErrorDetect ;
/* Used for the initialization of unused bytes with a certain value */
	uint8 CanTpPaddingByte ;
/* This parameter, if set to true, enables the CanTp_ReadParameterApi for this module. */
	boolean CanTpReadParameterApi ;
/* The function CanTp_GetVersionInfo is configurable (On/Off) by this configuration parameter. */
	boolean CanTpVersionInfoApi ;
} CanTp_GeneralType ;

/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __cplusplus
}}  /* name space */
#endif
#endif /* CANTP_TYPES_H */

