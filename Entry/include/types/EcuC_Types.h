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
#ifndef ECUC_TYPES_H
#define ECUC_TYPES_H

/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
#ifdef __cplusplus
namespace autosar {
extern "C" {
#endif
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* Definition of one Partition on this ECU. */
typedef struct EcuC_PartitionType_tag
{
/* Denotes that this partition will execute all BSW Modules. BSW Modules can only be executed in
 *  one partition.
 */
	boolean EcucPartitionBswModuleExecution ;
/* Specifies the requirement whether the Partition can be restarted. If set to true all software
 *  executing in this partition shall be capable of handling a restart.
 */
	boolean PartitionCanBeRestarted ;
/* References the SW Component instances from the Ecu Extract that shall be executed in this partition.
 */
	/*TODO:SW-COMPONENT-PROTOTYPE*/void* EcucPartitionSoftwareComponentInstanceRef ;
} EcuC_PartitionType ;

/* One Pdu flowing through the COM-Stack. */
typedef struct EcuC_PduType_tag
{
/* Length of the Pdu in bytes.  It should be noted that in former AUTOSAR releases (Rel 2.1, Rel
 *  3.0, Rel 3.1, Rel 4.0 Rev. 1) this parameter was defined in bits.
 */
	uint16 PduLength ;
/* Optional reference to the PduToFrameMapping from the SystemTemplate which this Pdu represents. */
	/*TODO:PDU-TO-FRAME-MAPPING*/void* SysTPduToFrameMappingRef ;
} EcuC_PduType ;

/* The PduIdType is used within the entire AUTOSAR Com Stack except for bus drivers. The size of
 *  this global type depends on the maximum number of PDUs used within one software module. If
 *  no software module deals with more PDUs that 256, this type can be set to uint8. If at least
 *  one software module handles more than 256 PDUs, this type must be set to uint16. See AUTOSAR_SWS_CommunicationStackTypes
 *  for more details.
 */
typedef enum
{
	ECUC_PDUIDTYPEENUM_UINT16,
	ECUC_PDUIDTYPEENUM_UINT8
} EcuC_PduIdTypeEnumType ;

/* The PduLengthType is used within the entire AUTOSAR Com Stack except for bus drivers. The size
 *  of this global type depends on the maximum length of PDUs to be sent by an ECU. If no segmentation
 *  is used the length depends on the maximum payload size of a frame of the underlying communication
 *  system (for FlexRay maximum size is 255 bytes, therefore uint8). If segementation is used it
 *  depends on the maximum length of a  segmeneted N-PDU (in general uint16 is used). See AUTOSAR_SWS_CommunicationStackTypes
 *  for more details.
 */
typedef enum
{
	ECUC_PDULENGTHTYPEENUM_UINT16,
	ECUC_PDULENGTHTYPEENUM_UINT32,
	ECUC_PDULENGTHTYPEENUM_UINT8
} EcuC_PduLengthTypeEnumType ;

/* Collection of Partitions defined for this ECU. */
typedef struct EcuC_PartitionCollectionType_tag
{
/* One Partition will be implemented using one Os-Application. */
	EcuC_PartitionType* EcucPartition ;
} EcuC_PartitionCollectionType ;

/* Collection of all Pdu objects flowing through the Com-Stack. */
typedef struct EcuC_PduCollectionType_tag
{
/* This Pdu is used by all Com-Stack modules to agree on referencing the same Pdu. */
	EcuC_PduType* Pdu ;
	EcuC_PduIdTypeEnumType PduIdTypeEnum ;
	EcuC_PduLengthTypeEnumType PduLengthTypeEnum ;
} EcuC_PduCollectionType ;

/* Collection of PredefinedVariant elements containing definition of values for SwSystemconst which
 *  shall be applied when resolving the variability during ECU Configuration.
 */
typedef struct EcuC_VariationResolverType_tag
{
	/*TODO:PREDEFINED-VARIANT*/void* PredefinedVariantRef ;
} EcuC_VariationResolverType ;

/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __cplusplus
}}  /* name space */
#endif
#endif /* ECUC_TYPES_H */

