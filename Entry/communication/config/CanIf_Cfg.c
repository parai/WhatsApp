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
STATIC CONST(CanIf_CtrlCfgType,MEM_CANIF_CONFIG) CanIf_CtrlCfg[2] =
{
	{	/* HS */
		.CanIfCtrlId = CAN_CTRL_0,
		.CanIfCtrlWakeupSupport = TRUE,
		.CanIfCtrlCanCtrlRef = &Can_ControllerConfig[CAN_CTRL_0]
	},
	{	/* LS */
		.CanIfCtrlId = CAN_CTRL_1,
		.CanIfCtrlWakeupSupport = TRUE,
		.CanIfCtrlCanCtrlRef = &Can_ControllerConfig[CAN_CTRL_1]
	},
};
STATIC CONST(CanIf_HrhRangeCfgType,MEM_CANIF_CONFIG) CanIf_HrhRangeCfgNormal =
{
	.CanIfHrhRangeRxPduLowerCanId = 0,
	.CanIfHrhRangeRxPduRangeCanIdType = CANIF_HRHRANGERXPDURANGECANIDTYPE_STANDARD,
	.CanIfHrhRangeRxPduUpperCanId = 0x7FF
};
STATIC CONST(CanIf_HrhCfgType,MEM_CANIF_CONFIG) CanIfHrhCfg_HS =
{
	.CanIfHrhRangeCfg = &CanIf_HrhRangeCfgNormal,
	.CanIfHrhSoftwareFilter = TRUE,	/* use CanIf_HrhRangeCfgNormal to do SW filtering */
	.CanIfHrhCanCtrlIdRef = &CanIf_CtrlCfg[CANIF_CHL_HS],
	.CanIfHrhIdSymRef         = &Can_HardwareObject[CAN0_RX_OBJECT]
};

STATIC CONST(CanIf_HthCfgType,MEM_CANIF_CONFIG) CanIfHthCfg_HS =
{
	.CanIfHthCanCtrlIdRef = &CanIf_CtrlCfg[CANIF_CHL_HS],
	.CanIfHthIdSymRef         = &Can_HardwareObject[CAN0_TX_OBJECT]
};

STATIC CONST(CanIf_HrhCfgType,MEM_CANIF_CONFIG) CanIfHrhCfg_LS =
{
	.CanIfHrhRangeCfg = &CanIf_HrhRangeCfgNormal,
	.CanIfHrhSoftwareFilter = TRUE,	/* use CanIf_HrhRangeCfgNormal to do SW filtering */
	.CanIfHrhCanCtrlIdRef = &CanIf_CtrlCfg[CANIF_CHL_LS],
	.CanIfHrhIdSymRef         = &Can_HardwareObject[CAN1_RX_OBJECT]
};

STATIC CONST(CanIf_HthCfgType,MEM_CANIF_CONFIG) CanIfHthCfg_LS =
{
	.CanIfHthCanCtrlIdRef = &CanIf_CtrlCfg[CANIF_CHL_LS],
	.CanIfHthIdSymRef         = &Can_HardwareObject[CAN1_TX_OBJECT]
};
STATIC CONST(CanIf_InitHohCfgType,MEM_CANIF_CONFIG) CanIf_InitHohCfg[] =
{
	{	/* CANIF_CHL_HS */
		.CanIfHrhCfg = &CanIfHrhCfg_HS,
		.CanIfHthCfg = &CanIfHthCfg_HS,
		.CanCtrlCfg = &Can_ControllerConfig[CAN_CTRL_0]
	},
	{	/* CANIF_CHL_LS */
        .CanIfHrhCfg = &CanIfHrhCfg_LS,
        .CanIfHthCfg = &CanIfHthCfg_LS,
		.CanCtrlCfg = &Can_ControllerConfig[CAN_CTRL_1]
	}
};
STATIC CONST(CanIf_RxPduCfgType,MEM_CANIF_CONFIG) CanIf_RxPduCfg[] =
{
	{
		.CanIfRxPduCanIdRange = NULL,	/* FULL */
		.CanIfTTRxFrameTriggering = NULL,
		.CanIfRxPduCanId = 0x700,
		.CanIfRxPduCanIdType = CANIF_RXPDUCANIDTYPE_STANDARD_CAN,
		.CanIfRxPduDlc = 8,
		.CanIfRxPduId = 0,	/* TODO:CANTP */
		.CanIfRxPduReadData= FALSE,
		.CanIfRxPduReadNotifyStatus = FALSE,
		.CanIfRxPduUserRxIndicationName = NULL,
		.CanIfRxPduUserRxIndicationUL = CANIF_RXPDUUSERRXINDICATIONUL_CAN_TP,
		.CanIfRxPduBswSchExclAreaIdRef = NULL,
		.CanIfRxPduHrhIdRef = &CanIfHrhCfg_HS,
		.CanIfRxPduRef = NULL
	},
	{
		.CanIfRxPduCanIdRange = NULL,	/* FULL */
		.CanIfTTRxFrameTriggering = NULL,
		.CanIfRxPduCanId = 0x700,
		.CanIfRxPduCanIdType = CANIF_RXPDUCANIDTYPE_STANDARD_CAN,
		.CanIfRxPduDlc = 8,
		.CanIfRxPduId = 1,	/* TODO:CANTP */
		.CanIfRxPduReadData= FALSE,
		.CanIfRxPduReadNotifyStatus = FALSE,
		.CanIfRxPduUserRxIndicationName = NULL,
		.CanIfRxPduUserRxIndicationUL = CANIF_RXPDUUSERRXINDICATIONUL_CAN_TP,
		.CanIfRxPduBswSchExclAreaIdRef = NULL,
		.CanIfRxPduHrhIdRef = &CanIfHrhCfg_LS,
		.CanIfRxPduRef = NULL
	}
};
STATIC CONST(CanIf_TxPduCfgType,MEM_CANIF_CONFIG) CanIf_TxPduCfg[] =
{
	{
		.CanIfTTTxFrameTriggering = NULL,
		.CanIfTxPduCanId = 0x701,
		.CanIfTxPduCanIdType = CANIF_TXPDUCANIDTYPE_STANDARD_CAN,
		.CanIfTxPduDlc = 8,
		.CanIfTxPduId = 0, /* TODO:CANTP */
		.CanIfTxPduPnFilterPdu = FALSE,
		.CanIfTxPduReadNotifyStatus= FALSE,
		.CanIfTxPduType = CANIF_TXPDUTYPE_STATIC,	/* ID not changeable */
		.CanIfTxPduUserTxConfirmationName = NULL,
		.CanIfTxPduUserTxConfirmationUL = CANIF_TXPDUUSERTXCONFIRMATIONUL_CAN_TP,
		.CanIfTxPduBswSchExclAreaIdRef = NULL,
		.CanIfTxPduHthIdRef = &CanIfHthCfg_HS,
		.CanIfTxPduBufferRef = NULL,
		.CanIfTxPduRef = NULL
	},
	{
		.CanIfTTTxFrameTriggering = NULL,
		.CanIfTxPduCanId = 0x701,
		.CanIfTxPduCanIdType = CANIF_TXPDUCANIDTYPE_STANDARD_CAN,
		.CanIfTxPduDlc = 8,
		.CanIfTxPduId = 1, /* TODO:CANTP */
		.CanIfTxPduPnFilterPdu = FALSE,
		.CanIfTxPduReadNotifyStatus= FALSE,
		.CanIfTxPduType = CANIF_TXPDUTYPE_STATIC,	/* ID not changeable */
		.CanIfTxPduUserTxConfirmationName = NULL,
		.CanIfTxPduUserTxConfirmationUL = CANIF_TXPDUUSERTXCONFIRMATIONUL_CAN_TP,
		.CanIfTxPduBswSchExclAreaIdRef = NULL,
		.CanIfTxPduHthIdRef = &CanIfHthCfg_LS,
		.CanIfTxPduBufferRef = NULL,
		.CanIfTxPduRef = NULL
	}
};
CONST(CanIf_ConfigType,MEM_CANIF_CONFIG) CanIf_Config =
{
		.CanIfBufferCfg = NULL,
		.CanIfInitHohCfg = CanIf_InitHohCfg,
		.CanIfInitHohNum = 2,
		.CanIfRxPduCfg = CanIf_RxPduCfg,
		.CanIfRxPduNum = 2,
		.CanIfTxPduCfg = CanIf_TxPduCfg,
		.CanIfTxPduNum = 2
};
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */


#ifdef __cplusplus
} /* namespace autosar */
#endif
