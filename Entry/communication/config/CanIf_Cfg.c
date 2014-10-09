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
/* ============================ [ INCLUDES  ] ====================================================== */
#include "CanIf.h"

#include "CanTp.h"

#ifdef __cplusplus
namespace autosar {
#endif

/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
STATIC CONST(CanIf_ControllerConfigType,MEM_CANIF_CONFIG) CanIf_ControllerConfig[CANIF_CHL_NUMBER] =
{
	{
		CANIF_CHL_LS,
		TRUE,
		&Can_ControllerConfig[CAN_CTRL_0]
	},
	{
		CANIF_CHL_HS,
		TRUE,
		&Can_ControllerConfig[CAN_CTRL_1]
	}
};
STATIC CONST(CanIf_HthConfigType,MEM_CANIF_CONFIG) CanIf_HthConfig[2] =
{
	{
		&CanIf_ControllerConfig[CANIF_CHL_LS],
		CAN0_OBJECT_TX,
		CAN_HANDE_TYPE_BASIC
	},
	{
		&CanIf_ControllerConfig[CANIF_CHL_HS],
		CAN1_OBJECT_TX,
		CAN_HANDE_TYPE_BASIC
	}
};
STATIC CONST(CanIf_HrhConfigType,MEM_CANIF_CONFIG) CanIf_HrhConfig[2] =
{
	{
		&CanIf_ControllerConfig[CANIF_CHL_LS],
		CAN0_OBJECT_RX,
		CAN_HANDE_TYPE_BASIC,
		TRUE
	},
	{
		&CanIf_ControllerConfig[CANIF_CHL_HS],
		CAN1_OBJECT_RX,
		CAN_HANDE_TYPE_BASIC,
		TRUE
	}
};
STATIC CONST(CanIf_InitHohConfigType,MEM_CANIF_CONFIG) CanIf_InitHohConfig =
{
	&Can_Config,
	CanIf_HrhConfig,
	2,
	CanIf_HthConfig,
	2
};
STATIC CONST(CanIf_TxPduConfigType,MEM_CANIF_CONFIG) CanIf_TxPduConfig[] =
{
	{
		0x702,	/* DIAG_LS */
		CANIF_ID_TYPE_STANDARD,
		8,
		CANTP_TX_DIAG_LS_MSG,
		FALSE,
		CANIF_PDU_TYPE_STATIC,
		CANIF_TXCONFIRMATION_UL_CAN_TP,
		NULL,
		&CanIf_HthConfig[0]	/* on LS */
	},
	{
		0x712,	/* DIAG_HS */
		CANIF_ID_TYPE_STANDARD,
		8,
		CANTP_TX_DIAG_HS_MSG,
		FALSE,
		CANIF_PDU_TYPE_STATIC,
		CANIF_TXCONFIRMATION_UL_CAN_TP,
		NULL,
		&CanIf_HthConfig[1]	/* on HS */
	}
};

STATIC CONST(CanIf_RxPduConfigType,MEM_CANIF_CONFIG) CanIf_RxPduConfig[] =
{
	{
		0x701,	/* DIAG_LS */
		CANIF_ID_TYPE_STANDARD,
		8,
		CANTP_RX_DIAG_LS_MSG,
		FALSE,
		FALSE,
		CANIF_PDU_TYPE_STATIC,
		PDUID_SDUDATAPTR,
		CANIF_RXINDICATION_UL_CAN_TP,
		NULL,
		&CanIf_HrhConfig[0]	/* on LS */
	},
	{
		0x711,	/* DIAG_HS */
		CANIF_ID_TYPE_STANDARD,
		8,
		CANTP_RX_DIAG_HS_MSG,
		FALSE,
		FALSE,
		CANIF_PDU_TYPE_STATIC,
		PDUID_SDUDATAPTR,
		CANIF_RXINDICATION_UL_CAN_TP,
		NULL,
		&CanIf_HrhConfig[1]	/* on HS */
	},
};

STATIC CONST(CanIf_InitConfigType,MEM_CANIF_CONFIG) CanIf_InitConfig =
{
	2,
	0,
	2,
	&CanIf_InitHohConfig,
	CanIf_RxPduConfig,
	CanIf_TxPduConfig
};
CONST(CanIf_ConfigType,MEM_CANIF_CONFIG) CanIf_Config =
{
	&CanIf_InitConfig
};
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */


#ifdef __cplusplus
} /* namespace autosar */
#endif
