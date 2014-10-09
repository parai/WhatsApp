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
 */
#ifndef CANIF_CFG_H_
#define CANIF_CFG_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"

#ifdef __cplusplus
namespace autosar { extern "C" {
#endif
/* ============================ [ MACROS    ] ====================================================== */
/* by default: 0=Disable, 1=Enable */
#define CANIF_PRIVATE_DLC_CHECK           		1
/* 0=BINARY,1=INDEX,3=LINEAR,4=TABLE,others=NOT USED */
#define CANIF_PRIVATE_SOFTWARE_FILTER_TYPE 		0

#define CANIF_PUBLIC_CANCEL_TRANSMIT_SUPPORT 	1
#define CANIF_PUBLIC_CDD_HEADERFILE				32
#define CANIF_PUBLIC_DEV_ERROR_DETECT			1
#define CANIF_PUBLIC_MULTIPLE_DRV_SUPPORT		0
#define CANIF_PUBLIC_NUMBER_OF_CAN_HW_UNITS     2	/* CAN0 and CAN1 */
#define CANIF_PUBLIC_READRXPDU_DATA_API			1
#define CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API	1
#define CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API	1
#define CANIF_PUBLIC_SETDYNAMICTXID_API				1
#define CANIF_PUBLIC_TX_BUFFERING					1
#define CANIF_PUBLIC_VERSION_INFO_API				1
#define CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_API	1

#define CANIF_CHL_LS		(CanIf_ChannelIdType)0
#define CANIF_CHL_HS		(CanIf_ChannelIdType)1
#define CANIF_CHL_NUMBER	(CanIf_ChannelIdType)2
/* ============================ [ TYPES     ] ====================================================== */

/* ============================ [ DATAS     ] ====================================================== */
extern CONST(CanIf_ConfigType,MEM_CANIF_CONFIG) CanIf_Config;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __cplusplus
}}  /* name space */
#endif
#endif /* CANIF_CFG_H_ */
