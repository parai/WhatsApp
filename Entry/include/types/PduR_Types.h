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
#ifndef PDUR_TYPES_H
#define PDUR_TYPES_H

/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
#ifdef __cplusplus
namespace autosar {
extern "C" {
#endif
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* This container groups routing path destinations. Destinations are used instead of routing paths
 *  since a routing path can be 1:n. It is desirable to be able to enable/disable a specific bus
 *  (i.e. a destination) rather than a routing path. Of course it is possible to create groups
 *  that covers specific routing paths as well.
 */
typedef struct
{
/* If set to true this routing path group will be enabled after initializing the PDU Router module
 *  (i.e. enabled in the PduR_Init function).
 */
	boolean PduRIsEnabledAtInit ;
/* The identification will be used by the disable/enable API in the PDU Router module API. */
/* Identification of the routing group. */
	uint16 PduRRoutingPathGroupId ;
/* This reference selects one destination of the routing path. */
/* /AUTOSAR/EcucDefs/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath/PduRDestPdu */
	PduR_DestPduType* PduRDestPduRef ;
} PduR_RoutingPathGroupType ;

/* Specifies the default value of the I-PDU. Only required for gateway operation and if at least
 *  one PDU specified by PduRDestPdu uses TriggerTransmit Data provision.
 */
typedef struct
{
	PduR_DefaultValueElementType* PduRDefaultValueElement ;
} PduR_DefaultValueType ;

/* Specifies how data are provided: direct (as part of the Transmit call) or via the TriggerTransmit
 *  callback function. Only required for non-TP I-PDUs (local and gatewayed).
 */
typedef enum
{
	PDUR_DIRECT,
	PDUR_TRIGGERTRANSMIT
} PduR_DestPduDataProvisionType ;

/* This container is a subcontainer of PduRRoutingPath and specifies one destination for the PDU
 *  to be routed.
 */
typedef struct
{
/* Represented as an array of IntegerParamDef. */
	PduR_DefaultValueType* PduRDefaultValue ;
	PduR_DestPduDataProvisionType PduRDestPduDataProvision ;
/* PDU identifier assigned by PDU Router. Used by communication interface and transport protocol
 *  modules for confirmation.
 */
	uint16 PduRDestPduHandleId ;
/* Defines the number of bytes which shall be received before transmission on the destination bus
 *  may start. Only required for routing-on-the-fly TP gateway PDUs. The threshold shall not be
 *  larger than the length of the related TP Buffer.
 */
	uint16 PduRTpThreshold ;
/* If set the destination communication interface module will call the TxConfirmation. However
 *  the TxConfirmation may be not called due to error. So the PduR shall not block until the TxConfirmation
 *  is called.
 * 
 *                                                                 One background for this parameter
 *  is for the PduR to know when all modules have confirmed a multicast operation.
 */
/* This parameter is only for communication interfaces. Transport protocol modules will always
 *  call the TxConfirmation function.
 */
	boolean PduRTransmissionConfirmation ;
/* Destination PDU reference; reference to unique PDU identifier which shall be used by the PDU
 *  Router instead of the source PDU ID when calling the related function of the destination module.
 */
/* /AUTOSAR/EcucDefs/EcuC/EcucPduCollection/Pdu */
	EcuC_PduType* PduRDestPduRef ;
/* Reference to a buffer that is allocated in the PduRTxBuffer. Having a global (for PduR) list
 *  of buffers allows reusage and hence less memory consumption.
 */
/* /AUTOSAR/EcucDefs/PduR/PduRRoutingTables/PduRTxBufferTable/PduRTxBuffer */
	PduR_TxBufferType* PduRDestTxBufferRef ;
} PduR_DestPduType ;

/* This container is a subcontainer of PduRRoutingPath and specifies the source of the PDU to be
 *  routed.
 */
typedef struct
{
/* PDU identifier assigned by PDU Router. */
	uint16 PduRSourcePduHandleId ;
/* Source PDU reference; reference to unique PDU identifier which shall be used for the requested
 *  PDU Router operation.
 */
/* /AUTOSAR/EcucDefs/EcuC/EcucPduCollection/Pdu */
	EcuC_PduType* PduRSrcPduRef ;
} PduR_SrcPduType ;

/* This container is a subcontainer of PduRRoutingTable and specifies the routing path of a PDU. */
typedef struct
{
	PduR_DestPduType* PduRDestPdu ;
	PduR_SrcPduType* PduRSrcPdu ;
} PduR_RoutingPathType ;

/* Represents one container of routing paths. Each container is either minimum routing or not. */
typedef struct
{
	PduR_RoutingPathType* PduRRoutingPath ;
/* Specifies if the container contains routing paths that are of the type minimum routing or not. */
	boolean PduRIsMinimumRouting ;
} PduR_RoutingTableType ;

/* Specifies a buffer used for gatwaying through TP. */
typedef struct
{
/* Length of the TP buffer in number of bytes */
	uint16 PduRTpBufferLength ;
} PduR_TpBufferType ;

/* This container will specify the needed buffers for gatewaying using TP. It is not connected
 *  to the specific routing path destination to allow a more efficient buffer handling.
 */
typedef struct
{
	PduR_TpBufferType* PduRTpBuffer ;
/* maximum number of TP buffers. */
	uint16 PduRMaxTpBufferNumber ;
} PduR_TpBufferTableType ;

/* Specifies a buffer used for gatwaying through communication interface. */
typedef struct
{
/* Length of the Tx buffer in number of bytes. */
	uint8 PduRPduMaxLength ;
/* Number of Pdus that can be stored in the buffer. If value is 1 then the buffer semantic is "last
 *  is best". If the value is greater then 1 then the buffer semnatic is a FiFo.
 */
	uint8 PduRTxBufferDepth ;
} PduR_TxBufferType ;

/* This container will specify the needed buffers for gatewaying using communication interface.
 *  It not defined per routing path to allow reusage of buffers.
 */
typedef struct
{
	PduR_TxBufferType* PduRTxBuffer ;
/* maximum number of Tx buffers. */
	uint16 PduRMaxTxBufferNumber ;
} PduR_TxBufferTableType ;

/* Each container describes a specific BSW module (upper/CDD/lower/IpduM) that the PDU Router shall
 *  interface to.
 */
typedef struct
{
/* Specifies if the Transport protocol module supports the CancelReceive API or not. Value true
 *  the API is supported.
 */
	boolean PduRCancelReceive ;
/* Specifies if the BSW module supports the CancelTransmit API or not. Value true the API is supported.
 */
	boolean PduRCancelTransmit ;
/* This parameter, if set to true, enables the PduR_<Up>ChangeParameterRequest Api for this Module. */
	boolean PduRChangeParameterRequestApi ;
/* A module can have both Communication Interface APIs and Transport Protocol APIs (e.g. the COM
 *  module).
 */
/* Specifies if the BSW module supports the Communication Interface APIs or not. Value true the
 *  APIs are supported.
 */
	boolean PduRCommunicationInterface ;
/* For example, if the CanIf module is referenced then the PDU Router module will implement the
 *  PduR_CanIfRxIndication API. And the PDUR module will call the CanIf_Transmit API. Other APIs
 *  are of course also covered.
 * 
 *                                         An upper module can also be an lower module (e.g. the
 *  IpduM module).
 */
/* The PduRLowerModule will decide who will call the APIs and who will implement the APIs. */
	boolean PduRLowerModule ;
/* This parameter is only valid for transport protocol modules and gateway operations. If transmission
 *  from a local upper layer module this module will handle the retransmission.
 */
/* If set to true this means that the destination transport protocol module will use the retransmission
 *  feature. This parameter might be set to false if the retransmission feature is not used, even
 *  though the destination transport protocol is supporting it.
 */
	boolean PduRRetransmission ;
/* The PDU Router module shall use the API parameters specified for transport protocol interface. */
	boolean PduRTransportProtocol ;
/* Specifies if the BSW module supports the TriggerTransmit API or not. Value true the API is supported.
 */
	boolean PduRTriggertransmit ;
/* Specifies if the BSW module supports the TxConfirmation API or not. Value true the API is supported.
 */
	boolean PduRTxConfirmation ;
/* For example, if the COM module is referenced then the PDU Router module will implement the PduR_Transmit
 *  API. And the PDUR module will call the Com_RxIndication API. Other APIs are of course also
 *  covered.
 * 
 *                                         An upper module can also be an lower module (e.g. the
 *  IpduM module).
 */
/* The PduRUpperModule will decide who will call the APIs and who will implement the APIs. */
	boolean PduRUpperModule ;
/* * PduR_<Up>CancelReceiveRequest
 *                                         * PduR_<Up>CancelTransmitRequest
 *                                         * PduR_<Up>ChangeParameterRequest 
 * 
 *                                         Example: If used by COM and the parameter is enabled
 *  the PduR_ComCancelTransmitRequest is used.
 * 
 *                                         The background is that upper layer modules differ in
 *  usage of this tag (e.g. COM is using the tag, DCM is not).
 */
/* This parameter, if set to true, enables the usage of the tag (<up>) in the following API calls: */
	boolean PduRUseTag ;
/* This is a reference to one BSW module's configuration (i.e. not the ECUC parameter definition
 *  template).
 */
/* Example, there could be several configurations of LinIf and this reference selects one of them. */
	/*TODO:ECUC-MODULE-CONFIGURATION-VALUES*/void* PduRBswModuleRef ;
} PduR_BswModulesType ;

/* This container is a subcontainer of PduR and specifies the general configuration parameters
 *  of the PDU Router.
 */
typedef struct
{
/* If true then PDU Router will enable the error-reporting to the Development Error Tracer (DET). */
	boolean PduRDevErrorDetect ;
/* If true the PduR_GetVersionInfo API is available. */
	boolean PduRVersionInfoApi ;
/* This parameter shall be seen as an input requirement to the configuration generator. */
/* If set the PduR configuration generator will report an error if zero-cost-operation cannot be
 *  fulfilled.
 */
	boolean PduRZeroCostOperation ;
} PduR_GeneralType ;

/* Represents one table of routing paths. */
typedef struct
{
/* Enabling and disabling of routing path groups are made using the PduR API */
	PduR_RoutingPathGroupType* PduRRoutingPathGroup ;
	PduR_RoutingTableType* PduRRoutingTable ;
	PduR_TpBufferTableType* PduRTpBufferTable ;
	PduR_TxBufferTableType* PduRTxBufferTable ;
/* Identification of the configuration of the PduR configuration. This identification can be read
 *  using the PduR API.
 */
	uint16 PduRConfigurationId ;
} PduR_RoutingTablesType ;

/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __cplusplus
}}  /* name space */
#endif
#endif /* PDUR_TYPES_H */

