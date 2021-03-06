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
#ifndef NVM_TYPES_H
#define NVM_TYPES_H

/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
#include "Dem.h"
#ifdef __cplusplus
namespace autosar {
extern "C" {
#endif
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* This parameter is just a container for the parameters for EA and FEE */
typedef struct NvM_TargetBlockReferenceType_tag
{
} NvM_TargetBlockReferenceType ;

/* Defines CRC data width for the NVRAM block. Default: NVM_CRC16, i.e. CRC16 will be used  if
 *  NVM_BLOCK_USE_CRC==true
 */
typedef enum
{
	NVM_CRC16,
	NVM_CRC32,
	NVM_CRC8
} NvM_BlockCrcTypeType ;

/* Defines the block management type for the NVRAM block.[NVM137] */
typedef enum
{
	NVM_BLOCK_DATASET,
	NVM_BLOCK_NATIVE,
	NVM_BLOCK_REDUNDANT
} NvM_BlockManagementTypeType ;

/* Entry address of a block specific callback routine which shall be called if no ROM data is available
 *  for initialization of the NVRAM block.
 */
/* TODO:*/
typedef void (*NvM_InitBlockCallbackType)(void);

/* Entry address of a block specific callback routine which shall be called in order to let the
 *  application copy data from the NvM module's mirror to RAM block.
 */
/* TODO: */
typedef void (*NvM_ReadRamBlockFromNvCallbackType)(void);

/* Entry address of the block specific callback routine which shall be invoked on termination of
 *  each asynchronous single block request [NVM113].
 */
/* TODO: */
typedef void (*NvM_SingleBlockCallbackType)(void);

/* Entry address of a block specific callback routine which shall be called in order to let the
 *  application copy data from RAM block to NvM module's mirror.
 */
/* TODO: */
typedef void (*NvM_WriteRamBlockToNvCallbackType)(void);

/* Preprocessor switch to enable some API calls which are related to NVM API configuration classes. */
typedef enum
{
	NVM_API_CONFIG_CLASS_1,
	NVM_API_CONFIG_CLASS_2,
	NVM_API_CONFIG_CLASS_3
} NvM_ApiConfigClassType ;

/* Entry address of the common callback routine which shall be invoked on termination of each asynchronous
 *  multi block request
 */
/* TODO: */
typedef void (*NvM_MultiBlockCallbackType)(void);

/* Container for a management structure to configure the composition of a given NVRAM Block Management
 *  Type. Its multiplicity describes the number of configured NVRAM blocks, one block is required
 *  to be configured. The NVRAM block descriptors are condensed in the NVRAM block descriptor table.
 */
typedef struct NvM_BlockDescriptorType_tag
{
	NvM_TargetBlockReferenceType* NvMTargetBlockReference ;
	NvM_BlockCrcTypeType NvMBlockCrcType ;
/* Defines the job priority for a NVRAM block (0 = Immediate priority). */
	uint8 NvMBlockJobPriority ;
	NvM_BlockManagementTypeType NvMBlockManagementType ;
/* true:     	CRC will be used for this NVRAM block.
 *                                         false:     	CRC will not be used for this NVRAM block.
 */
/* Defines CRC usage for the NVRAM block, i.e. memory space for CRC is reserved in RAM and NV memory. */
	boolean NvMBlockUseCrc ;
/* Defines whether an explicit synchronization mechanism with a RAM mirror and callback routiness
 *  for transferring data to and from NvM module's RAM mirror is used for NV block. true if synchronization
 *  mechanism is used, false otherwise.
 */
	boolean NvMBlockUseSyncMechanism ;
/* true:	Initial block write protection is enabled.
 *                                         false:	Initial block write protection is disabled.
 */
/* Defines an initial write protection of the NV block */
	boolean NvMBlockWriteProt ;
/* True: Call BswM_NvM_CurrentBlockMode on changes
 *                                         False: Don&rsquo;t inform BswM at all
 */
/* This parameter specifies whether BswM is informed about the current status of the specified block. */
	boolean NvMBswMBlockStatusInformation ;
/* true:	CRC will be (re)calculated for this permanent RAM block.
 *                                         false: 	CRC will not be (re)calculated for this permanent
 *  RAM block.
 */
/* Defines CRC (re)calculation for the permanent RAM block */
	boolean NvMCalcRamBlockCrc ;
/* If not configured, no specific callback routine shall be called for initialization of the NVRAM
 *  block with default data.
 */
	NvM_InitBlockCallbackType NvMInitBlockCallback ;
/* Defines the maximum number of read retries. */
	uint8 NvMMaxNumOfReadRetries ;
/* Defines the maximum number of write retries for a NVRAM block with [NVM061_Conf]. Regardless
 *  of configuration a consistency check (and maybe write retries) are always forced for each block
 *  which is processed by the request NvM_WriteAll and NvM_WriteBlock.
 */
	uint8 NvMMaxNumOfWriteRetries ;
/* Calculation Formula:
 *                                         value = TargetBlockReference.[Ea/Fee]BlockConfiguration.[Ea/Fee]BlockNumber
 *  >> NvMDatasetSelectionBits
 */
/* Configuration parameter to perform the link between the NVM_NVRAM_BLOCK_IDENTIFIER used by the
 *  SW-Cs and the FEE_BLOCK_NUMBER expected by the memory abstraction modules. The parameter value
 *  equals the FEE_BLOCK_NUMBER or EA_BLOCK_NUMBER shifted to the right by NvMDatasetSelectionBits
 *  bits. (ref. to chapter 7.1.2.1).
 */
	uint16 NvMNvBlockBaseNumber ;
/* Note: 
 *                                         The implementer can add the attribute 'withAuto' to
 *  the parameter definition which indicates that the length can be calculated by the generator
 *  automatically (e.g. by using the sizeof operator). 
 *                                         When 'withAuto' is set to 'true' for this parameter
 *  definition the 'isAutoValue' can be set to 'true'. 
 *                                         If 'isAutoValue' is set to 'true' the actual value will
 *  not be considered during ECU Configuration but will be (re-)calculated by the code generator
 *  and stored in the value attribute afterwards.
 */
/* Defines the NV block data length in bytes. */
	uint16 NvMNvBlockLength ;
/* 1-255	For NVRAM blocks to be configured of block management type NVM_BLOCK_DATASET. The actual
 *  range is limited according to NVM444.
 * 
 *                                         1	For NVRAM blocks to be configured of block management
 *  type NVM_BLOCK_NATIVE
 * 
 *                                         2	For NVRAM blocks to be configured of block management
 *  type NVM_BLOCK_REDUNDANT
 */
/* Defines the number of multiple NV blocks in a contiguous area according to the given block management
 *  type.
 */
	uint8 NvMNvBlockNum ;
/* Implementation Type: NvM_BlockIdType.
 * 
 *                                         min = 2
 *                                         max = 2^(16- NVM_DATASET_SELECTION_BITS)-1
 * 
 *                                         Reserved NVRAM block IDs:
 *                                         0 -> to derive multi block request results via NvM_GetErrorStatus
 *                                         1 -> redundant NVRAM block which holds the configuration
 *  ID
 */
/* Identification of a NVRAM block via a unique block identifier. */
	uint16 NvMNvramBlockIdentifier ;
/* Calculation Formula:
 *                                         value = TargetBlockReference.[Ea/Fee]BlockConfiguration.[Ea/Fee]DeviceIndex
 */
/* Defines the NVRAM device ID where the NVRAM block is located. */
	uint8 NvMNvramDeviceId ;
/* If this is not configured, no permanent RAM data block is available for the selected block management
 *  type.
 */
/* Defines the start address of the RAM block data. */
	char* NvMRamBlockDataAddress ;
/* Implementation type: Std_ReturnType
 * 
 *                                         E_OK: copy was successful
 *                                         E_NOT_OK: copy was not successful, callback routine
 *  to be called again
 */
	NvM_ReadRamBlockFromNvCallbackType NvMReadRamBlockFromNvCallback ;
/* true: 	NVRAM block is resistant to changed software.
 *                                         false: 	NVRAM block is not resistant to changed software.
 */
/* Defines whether a NVRAM block shall be treated resistant to configuration changes or not. If
 *  there is no default data available at configuration time then the application shall be responsible
 *  for providing the default initialization data. In this case the application has to use NvM_GetErrorStatus()to
 *  be able to distinguish between first initialization and corrupted data.
 */
	boolean NvMResistantToChangedSw ;
/* If not configured, no ROM block is available for the selected block management type. */
/* Defines the start address of the ROM block data. */
	char* NvMRomBlockDataAddress ;
/* 0-255	For NVRAM blocks to be configured of block management type NVM_BLOCK_DATASET. The actual
 *  range is limited according to NVM444.
 * 
 *                                         0-1	For NVRAM blocks to be configured of block management
 *  type NVM_BLOCK_NATIVE
 * 
 *                                         0-1	For NVRAM blocks to be configured of block management
 *  type NVM_BLOCK_REDUNDANT
 */
/* Defines the number of multiple ROM blocks in a contiguous area according to the given block
 *  management type.
 */
	uint8 NvMRomBlockNum ;
/* true:	NVRAM block shall be processed by NvM_ReadAll
 *                                         false:	NVRAM block shall not be processed by NvM_ReadAll
 */
/* NVM117: Defines whether a NVRAM block shall be processed during NvM_ReadAll or not. This configuration
 *  parameter has only influence on those NVRAM blocks which are configured to have a permanent
 *  RAM block.
 */
	boolean NvMSelectBlockForReadAll ;
/* true: NVRAM block shall be processed by NvM_WriteAll
 *                                         false: NVRAM block shall not be processed by NvM_WriteAll
 */
/* Defines whether a NVRAM block shall be processed during NvM_WriteAll or not. This configuration
 *  parameter has only influence on those NVRAM blocks which are configured to have a permanent
 *  RAM block.
 */
	boolean NvMSelectBlockForWriteAll ;
	NvM_SingleBlockCallbackType NvMSingleBlockCallback ;
/* false: Static Block ID check is disabled.
 *                                         true: Static Block ID check is enabled.
 */
/* Defines if the Static Block ID check is enabled. */
	boolean NvMStaticBlockIDCheck ;
/* true: 	Defines write protection after first write is enabled.
 *                                         false: 	Defines write protection after first write is
 *  disabled.
 */
/* Defines write protection after first write. The NVRAM manager sets the write protection bit
 *  after the NV block was written the first time. This means that some of the NV blocks in the
 *  NVRAM should never be erased nor be replaced with the default ROM data after first initialization.
 *  [NVM276].
 */
	boolean NvMWriteBlockOnce ;
/* Implementation type: Std_ReturnType
 * 
 *                                         E_OK: copy was successful
 *                                         E_NOT_OK: copy was not successful, callback routine
 *  to be called again
 */
	NvM_WriteRamBlockToNvCallbackType NvMWriteRamBlockToNvCallback ;
/* false: Write verification is disabled.
 *                                         true: Write Verification is enabled.
 */
/* Defines if Write Verification is enabled. */
	boolean NvMWriteVerification ;
/* Defines the number of bytes to compare in each step when comparing the content of a RAM Block
 *  and a block read back.
 */
	uint32 NvMWriteVerificationDataSize ;
} NvM_BlockDescriptorType ;

/* Container for common configuration options. */
typedef struct NvM_CommonType_tag
{
	NvM_ApiConfigClassType NvMApiConfigClass ;
/* True: call  BswM_NvM_CurrentJobMode if ReadAll and WriteAll are started, finished, canceled
 *  
 *                                         False: do not inform BswM at all
 */
/* This parameter specifies whether BswM is informed about the current status of the multiblock job. */
	boolean NvMBswMMultiBlockJobStatusInformation ;
/* Configuration ID regarding the NV memory layout. This configuration ID shall be published as
 *  e.g. a SW-C shall have the possibility to write it to NV memory.
 */
	uint16 NvMCompiledConfigId ;
/* If CRC is configured for at least one NVRAM block, this parameter defines the maximum number
 *  of bytes which shall be processed within one cycle of job processing.
 */
	uint16 NvMCrcNumOfBytes ;
/* 0..8: Number of bits which are used for dataset or redundant block addressing. 
 * 
 *                                         0: No dataset or redundant NVRAM blocks are configured
 *  at all, no selection bits required.
 * 
 *                                         1: In case of redundant NVRAM blocks are configured,
 *  but no dataset NVRAM blocks.
 */
/* Defines the number of least significant bits which shall be used to address a certain dataset
 *  of a NVRAM block within the interface to the memory hardware abstraction.
 */
	uint8 NvMDatasetSelectionBits ;
/* true:	Development error detection enabled.
 *                                         false:	Development error detection disabled.
 */
/* Pre-processor switch to enable and disable development error detection. */
	boolean NvMDevErrorDetect ;
/* true:	Fast mode enabled.
                                        false:	Fast mode disabled. */
/* Preprocessor switch to enable switching memory drivers to fast mode during performing NvM_ReadAll
 *  and NvM_WriteAll
 */
	boolean NvMDrvModeSwitch ;
/* true:	Dynamic configuration management handling enabled.
 *                                         false:	Dynamic configuration management handling disabled.
 */
/* Preprocessor switch to enable the dynamic configuration management handling by the NvM_ReadAll
 *  request.
 */
	boolean NvMDynamicConfiguration ;
/* true:	Job prioritization handling enabled.
 *                                         false:	Job prioritization handling disabled.
 */
/* Preprocessor switch to enable job prioritization handling */
	boolean NvMJobPrioritization ;
	NvM_MultiBlockCallbackType NvMMultiBlockCallback ;
/* true:	Polling mode enabled, callback function usage disabled.
 *                                         false:	Polling mode disabled, callback function usage
 *  enabled.
 */
/* Preprocessor switch to enable/disable the polling mode in the NVRAM Manager and at the same
 *  time disable/enable the callback functions useable by lower layers
 */
	boolean NvMPollingMode ;
/* Defines the number of retries to let the application copy data to or from the NvM module's mirror
 *  before postponing the current job.
 */
	uint8 NvMRepeatMirrorOperations ;
/* true:	API NvM_SetRamBlockStatus enabled.
 *                                         false:	API NvM_SetRamBlockStatus disabled.
 */
/* Preprocessor switch to enable the API NvM_SetRamBlockStatus. */
	boolean NvMSetRamBlockStatusApi ;
/* Defines the number of queue entries for the immediate priority job queue. If NVM_JOB_PRIORITIZATION
 *  is switched OFF this parameter shall be out of scope.
 */
	uint8 NvMSizeImmediateJobQueue ;
/* Defines the number of queue entries for the standard job queue. */
	uint8 NvMSizeStandardJobQueue ;
/* true:	Version info API enabled.
 *                                         false:	Version info API disabled.
 */
/* Pre-processor switch to enable / disable the API to read out the modules version information
 *  [NVM285], [NVM286].
 */
	boolean NvMVersionInfoApi ;
} NvM_CommonType ;

/* Container for the references to DemEventParameter elements which shall be invoked using the
 *  API Dem_ReportErrorStatus API in case the corresponding error occurs. The EventId is taken
 *  from the referenced DemEventParameter's DemEventId value. The standardized errors are provided
 *  in the container and can be extended by vendor specific error references.
 */
typedef struct NvM_DemEventParameterRefsType_tag
{
/* Reference to the DemEventParameter which shall be issued when the error "API request integrity
 *  failed" has occured.
 */
/* /AUTOSAR/EcucDefs/Dem/DemConfigSet/DemEventParameter */
    struct Dem_EventParameterType_tag* NVM_E_INTEGRITY_FAILED ;
/* Reference to the DemEventParameter which shall be issued when the error "loss of redundancy"
 *  has occured.
 */
/* /AUTOSAR/EcucDefs/Dem/DemConfigSet/DemEventParameter */
    struct Dem_EventParameterType_tag* NVM_E_LOSS_OF_REDUNDANCY ;
/* Reference to the DemEventParameter which shall be issued when the error "NVRAM Managers job
 *  queue overflow" has occured.
 */
/* /AUTOSAR/EcucDefs/Dem/DemConfigSet/DemEventParameter */
    struct Dem_EventParameterType_tag* NVM_E_QUEUE_OVERFLOW ;
/* Reference to the DemEventParameter which shall be issued when the error "API request failed"
 *  has occured.
 */
/* /AUTOSAR/EcucDefs/Dem/DemConfigSet/DemEventParameter */
    struct Dem_EventParameterType_tag* NVM_E_REQ_FAILED ;
/* Reference to the DemEventParameter which shall be issued when the error "Write Verification
 *  failed" has occured.
 */
/* /AUTOSAR/EcucDefs/Dem/DemConfigSet/DemEventParameter */
    struct Dem_EventParameterType_tag* NVM_E_VERIFY_FAILED ;
/* Reference to the DemEventParameter which shall be issued when the error "write attempt to NVRAM
 *  block with write protection" has occured.
 */
/* /AUTOSAR/EcucDefs/Dem/DemConfigSet/DemEventParameter */
    struct Dem_EventParameterType_tag* NVM_E_WRITE_PROTECTED ;
/* Reference to the DemEventParameter which shall be issued when the error "Static Block ID check
 *  failed" has occured.
 */
/* /AUTOSAR/EcucDefs/Dem/DemConfigSet/DemEventParameter */
    struct Dem_EventParameterType_tag* NVM_E_WRONG_BLOCK_ID ;
} NvM_DemEventParameterRefsType ;

/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __cplusplus
}}  /* name space */
#endif
#endif /* NVM_TYPES_H */

