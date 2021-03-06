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
#ifndef MEMMAP_TYPES_H
#define MEMMAP_TYPES_H

/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
#ifdef __cplusplus
namespace autosar {
extern "C" {
#endif
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* Defines a addressing mode with a set of #pragma statements implementing the start and the stop
 *  of a section.
 */
typedef struct MemMap_AddressingModeType_tag
{
/* Defines a set of #pragma statements implementing the start of a section. */
	char** MemMapAddressingModeStart ;
/* Defines a set of #pragma statements implementing the start of a section. */
	char** MemMapAddressingModeStop ;
/* The to be used alignment is defined in the alignment attribute of the MemorySection. If the
 *  MemMapAlignmentSelector fits to alignment attribute of the MemorySection the set of #pragmas
 *  of the related MemMapAddressingMode shall be used to implement the start and the stop of a
 *  section.
 * 
 *                                                 Please note that the same MemMapAddressingMode
 *  can be applicable for several alignments, e.g. "8" bit and "UNSPECIFIED".
 */
/* Defines a the alignments for which the MemMapAddressingMode applies. */
	char* MemMapAlignmentSelector ;
} MemMap_AddressingModeType ;

/* This constrains the usage of this addressing mode set for Generic Mappings to swAddrMethods. */
typedef enum
{
	MEMMAP_ALLOCATION_KEYWORD_POLICY_ADDR_METHOD_SHORT_NAME,
	MEMMAP_ALLOCATION_KEYWORD_POLICY_ADDR_METHOD_SHORT_NAME_AND_ALIGNMENT
} MemMap_SupportedMemoryAllocationKeywordPolicyType ;

/* This constrains the usage of this addressing mode set for Generic Mappings to swAddrMethods. */
typedef enum
{
	MEMMAP_SECTION_TYPE_CALIBRATION_OFFLINE,
	MEMMAP_SECTION_TYPE_CALIBRATION_ONLINE,
	MEMMAP_SECTION_TYPE_CAL_PRM,
	MEMMAP_SECTION_TYPE_CODE,
	MEMMAP_SECTION_TYPE_CONFIG_DATA,
	MEMMAP_SECTION_TYPE_CONST,
	MEMMAP_SECTION_TYPE_EXCLUDE_FROM_FLASH,
	MEMMAP_SECTION_TYPE_USER_DEFINED,
	MEMMAP_SECTION_TYPE_VAR,
	MEMMAP_SECTION_TYPE_VAR_FAST,
	MEMMAP_SECTION_TYPE_VAR_NO_INIT,
	MEMMAP_SECTION_TYPE_VAR_POWER_ON_INIT
} MemMap_SupportedSectionTypeType ;

/* Defines which SwAddrMethod is implemented with which MemMapAddressingModeSet. */
typedef struct MemMap_GenericMappingType_tag
{
/* Reference to the SwAddrMethod which applies to the MemMapGenericMapping. */
	/*TODO:SW-ADDR-METHOD*/void* MemMapSwAddressMethodRef ;
/* Reference to the MemMapAddressingModeSet which applies to the MemMapGenericMapping. */
/* /AUTOSAR/EcucDefs/MemMap/MemMapAddressingModeSet */
	MemMap_AddressingModeSetType* MemMapAddressingModeSetRef ;
} MemMap_GenericMappingType ;

/* Defines which MemorySection of a BSW Module or a Software Component is implemented with which
 *  MemMapAddressingModeSet.
 */
typedef struct MemMap_SectionSpecificMappingType_tag
{
/* Reference to the MemorySection which applies to the MemMapSectionSpecificMapping. */
	/*TODO:MEMORY-SECTION*/void* MemMapMemorySectionRef ;
/* Reference to the MemMapAddressingModeSet which applies to the MemMapModuleSectionSpecificMapping. */
/* /AUTOSAR/EcucDefs/MemMap/MemMapAddressingModeSet */
	MemMap_AddressingModeSetType* MemMapAddressingModeSetRef ;
} MemMap_SectionSpecificMappingType ;

/* Defines a set of addressing modes which might apply to a SwAddrMethod. */
typedef struct MemMap_AddressingModeSetType_tag
{
	MemMap_AddressingModeType* MemMapAddressingMode ;
/* The attribute option of a swAddrMethod mapped via MemMapGenericMapping to this MemMapAddressingModeSet
 *  shall be equal to one of the configured MemMapSupportedAddressMethodOption's
 */
/* This constrains the usage of this addressing mode set for Generic Mappings to swAddrMethods. */
	char* MemMapSupportedAddressingMethodOption ;
/* The attribute MemoryAllocationKeywordPolicy of a swAddrMethod mapped via MemMapGenericMapping
 *  to this MemMapAddressingModeSet shall be equal to one of the configured MemMapSupportedMemoryAllocationKeywordPolicy's
 */
	MemMap_SupportedMemoryAllocationKeywordPolicyType MemMapSupportedMemoryAllocationKeywordPolicy ;
/* The sectionIntializationPolicy attribute value of a swAddrMethod mapped via MemMapGenericMapping
 *  to this MemMapAddressingModeSet shall be equal to one of the configured MemMapSupportedSectionIntializationPolicy's
 *  
 * 
 *                                         Please note that SectionInitializationPolicyType describes
 *  the intended initialization of MemorySections. 
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
 * 
 *                                         Please note that the values are defined similar to the
 *  representation of enumeration types in the XML schema to ensure backward compatibility.
 */
/* This constrains the usage of this addressing mode set for Generic Mappings to swAddrMethods. */
	char* MemMapSupportedSectionInitializationPolicy ;
/* The attribute sectionType of a swAddrMethod mapped via MemMapGenericMapping or MemMapSectionSpecificMapping
 *  to this MemMapAddressingModeSet shall be equal to one of the configured MemMapSupportedSectionType's.
 */
	MemMap_SupportedSectionTypeType MemMapSupportedSectionType ;
} MemMap_AddressingModeSetType ;

/* Defines a set of addressing modes which might apply to a SwAddrMethod. */
typedef struct MemMap_AllocationType_tag
{
/* The pragmas for the implementation of the MemorySelectorKeywords are taken from the MemMapAddressingModeStart
 *  and MemMapAddressingModeStop parameters of the MemMapAddressingModeSet for the individual alignments.
 * 
 *                                         That this mapping becomes valid requires matching MemMapSupportedSectionType's,
 *  MemMapSupportedSectionInitializationPolicy's and MemMapSupportedAddressingMethodOption's.
 * 
 *                                         The MemMapGenericMapping applies only if it is not overruled
 *  by an MemMapSectionSpecificMapping
 */
	MemMap_GenericMappingType* MemMapGenericMapping ;
/* The pragmas for the implementation of the MemorySelectorKeywords are taken from the MemMapAddressingModeStart
 *  and MemMapAddressingModeStop parameters of the MemMapAddressingModeSet for the specific alignment
 *  of the MemorySection.
 * 
 *                                         The MemMapSectionSpecificMapping precedes a mapping
 *  defined by MemMapGenericMapping.
 */
	MemMap_SectionSpecificMappingType* MemMapSectionSpecificMapping ;
} MemMap_AllocationType ;

/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __cplusplus
}}  /* name space */
#endif
#endif /* MEMMAP_TYPES_H */

