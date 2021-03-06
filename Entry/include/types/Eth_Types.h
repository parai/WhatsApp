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
#ifndef ETH_TYPES_H
#define ETH_TYPES_H

/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
#ifdef __cplusplus
namespace autosar {
extern "C" {
#endif
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* Container for the references to DemEventParameter elements which shall be invoked using the
 *  API Dem_ReportErrorStatus in case the corresponding error occurs. The EventId is taken from
 *  the referenced DemEventParameter's DemEventId value. The standardized errors are provided in
 *  the container and can be extended by vendor specific error references.
 */
typedef struct Eth_DemEventParameterRefsType_tag
{
/* Reference to the DemEventParameter which shall be issued when the error "Controller access failed"
 *  has occured.
 */
/* /AUTOSAR/EcucDefs/Dem/DemConfigSet/DemEventParameter */
	Dem_EventParameterType* ETH_E_ACCESS ;
} Eth_DemEventParameterRefsType ;

/* Configuration of the individual controller */
typedef struct Eth_CtrlConfigType_tag
{
	Eth_DemEventParameterRefsType* EthDemEventParameterRefs ;
/* Enables / Disables Media Independent Interface (MII) for transceiver access */
	boolean EthCtrlEnableMii ;
/* Enables / Disables receive interrupt */
	boolean EthCtrlEnableRxInterrupt ;
/* Enables / Disables transmit interrupt */
	boolean EthCtrlEnableTxInterrupt ;
/* Specifies the instance ID of the configured controller. */
	uint8 EthCtrlIdx ;
/* Limits the maximum receive buffer length (frame length) in bytes. */
	uint16 EthCtrlRxBufLenByte ;
/* Limits the maximum transmit buffer length (frame length) in bytes. */
	uint16 EthCtrlTxBufLenByte ;
/* Configures the number of receive buffers. */
	uint8 EthRxBufTotal ;
/* Configures the number of transmit buffers. */
	uint8 EthTxBufTotal ;
} Eth_CtrlConfigType ;

/* All included containers and parameters that may be part of a multiple configuration set. */
typedef struct Eth_ConfigSetType_tag
{
	Eth_CtrlConfigType* EthCtrlConfig ;
} Eth_ConfigSetType ;

/* General configuration of Ethernet Driver module */
typedef struct Eth_GeneralType_tag
{
/* Enables / Disables development error detection. */
	boolean EthDevErrorDetect ;
/* Specifies the InstanceId of this module instance. If only one instance is present it shall have
 *  the Id 0.
 */
	uint8 EthIndex ;
/* Limits the total number of supported controllers. */
	uint8 EthMaxCtrlsSupported ;
/* Enables / Disables version info API */
	boolean EthVersionInfoApi ;
/* Enables / Disables version info API macro implementation */
	boolean EthVersionInfoApiMacro ;
} Eth_GeneralType ;

/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __cplusplus
}}  /* name space */
#endif
#endif /* ETH_TYPES_H */

