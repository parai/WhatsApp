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
#include "CanTp.h"
#ifdef __cplusplus
namespace autosar {
#endif

/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
STATIC CONST(CanTp_RxNPduType,MEM_CANTP_CFG) CanTpRxNPduP2P =
{
	.CanTpRxNPduId = CANTP_RX_P2P,
	.CanTpRxNPduRef = NULL
};
STATIC CONST(CanTp_TxFcNPduType,MEM_CANTP_CFG) CanTpTxFcNPduP2P =
{
	.CanTpTxFcNPduConfirmationPduId = CANTP_TX_P2P,
	.CanTpTxFcNPduRef = NULL
};
STATIC CONST(CanTp_RxNSduType,MEM_CANTP_CFG) CanTpRxNSduP2P =
{
	.CanTpNAe = 0,
	.CanTpNSa = 0,
	.CanTpNTa = 0,
	.CanTpRxNPdu = &CanTpRxNPduP2P,
	.CanTpTxFcNPdu = &CanTpTxFcNPduP2P,
	.CanTpBs    = 8,
	.CanTpNar = 5,
	.CanTpNbr = 50,
	.CanTpNcr   = 150,
	.CanTpRxAddressingFormat = CANTP_RX_ADDRESSING_FORMAT_STANDARD,
	.CanTpRxDl = 1,
	.CanTpRxNSduId = CANTP_RX_P2P,
	.CanTpRxPaddingActivation = CANTP_RX_PADDING_OFF,
	.CanTpRxTaType = CANTP_RX_TYPE_PHYSICAL,
	.CanTpRxWftMax = 10,
	.CanTpSTmin = 10,
	.CanTpRxNSduRef = NULL
};
STATIC CONST(CanTp_RxNPduType,MEM_CANTP_CFG) CanTpRxNPduP2A =
{
	.CanTpRxNPduId = CANTP_RX_P2A,
	.CanTpRxNPduRef = NULL
};
STATIC CONST(CanTp_TxFcNPduType,MEM_CANTP_CFG) CanTpTxFcNPduP2A =
{
	.CanTpTxFcNPduConfirmationPduId = CANTP_TX_P2A,
	.CanTpTxFcNPduRef = NULL
};
STATIC CONST(CanTp_RxNSduType,MEM_CANTP_CFG) CanTpRxNSduP2A =
{
	.CanTpNAe = 0,
	.CanTpNSa = 0,
	.CanTpNTa = 0,
	.CanTpRxNPdu = &CanTpRxNPduP2A,
	.CanTpTxFcNPdu = &CanTpTxFcNPduP2A,
	.CanTpBs    = 8,
	.CanTpNar = 5,
	.CanTpNbr = 50,
	.CanTpNcr   = 150,
	.CanTpRxAddressingFormat = CANTP_RX_ADDRESSING_FORMAT_STANDARD,
	.CanTpRxDl = 1,
	.CanTpRxNSduId = CANTP_RX_P2A,
	.CanTpRxPaddingActivation = CANTP_RX_PADDING_OFF,
	.CanTpRxTaType = CANTP_RX_TYPE_PHYSICAL,
	.CanTpRxWftMax = 10,
	.CanTpSTmin = 10,
	.CanTpRxNSduRef = NULL
};
STATIC  CONST(CanTp_RxFcNPduType,MEM_CANTP_CFG) CanTpRxFcNPduP2P =
{
	.CanTpRxFcNPduId = CANTP_RX_P2P,
	.CanTpRxFcNPduRef = NULL
};
STATIC  CONST(CanTp_TxNPduType,MEM_CANTP_CFG) CanTpTxNPduP2P =
{
	.CanTpTxNPduConfirmationPduId = CANTP_TX_P2P,
	.CanTpTxNPduRef = NULL
};
STATIC  CONST(CanTp_TxNSduType,MEM_CANTP_CFG) CanTpTxNSduP2P =
{
	.CanTpNAe = 0,
	.CanTpNSa = 0,
	.CanTpNTa = 0,
	.CanTpRxFcNPdu = &CanTpRxFcNPduP2P,
	.CanTpTxNPdu  = &CanTpTxNPduP2P,
	.CanTpNas = 5,
	.CanTpNbs = 150,
	.CanTpNcs = 50,
	.CanTpTc = TRUE,
	.CanTpTxAddressingFormat = CANTP_TX_ADDRESSING_FORMAT_STANDARD,
	.CanTpTxDl = 1,
	.CanTpTxNSduId = CANTP_TX_P2P,
	.CanTpTxPaddingActivation = CANTP_TX_PADDING_ON,
	.CanTpTxTaType = CANTP_TX_TYPE_PHYSICAL,
	.CanTpTxNSduRef = NULL
};
STATIC  CONST(CanTp_RxFcNPduType,MEM_CANTP_CFG) CanTpRxFcNPduP2A =
{
	.CanTpRxFcNPduId = CANTP_RX_P2A,
	.CanTpRxFcNPduRef = NULL
};
STATIC  CONST(CanTp_TxNPduType,MEM_CANTP_CFG) CanTpTxNPduP2A =
{
	.CanTpTxNPduConfirmationPduId = CANTP_TX_P2A,
	.CanTpTxNPduRef = NULL
};
STATIC  CONST(CanTp_TxNSduType,MEM_CANTP_CFG) CanTpTxNSduP2A =
{
	.CanTpNAe = 0,
	.CanTpNSa = 0,
	.CanTpNTa = 0,
	.CanTpRxFcNPdu = &CanTpRxFcNPduP2A,
	.CanTpTxNPdu  = &CanTpTxNPduP2A,
	.CanTpNas = 5,
	.CanTpNbs = 150,
	.CanTpNcs = 50,
	.CanTpTc = TRUE,
	.CanTpTxAddressingFormat = CANTP_TX_ADDRESSING_FORMAT_STANDARD,
	.CanTpTxDl = 1,
	.CanTpTxNSduId = CANTP_TX_P2A,
	.CanTpTxPaddingActivation = CANTP_TX_PADDING_ON,
	.CanTpTxTaType = CANTP_TX_TYPE_FUNCTIONAL,
	.CanTpTxNSduRef = NULL
};
STATIC CONST(CanTp_ChannelType,MEM_CANTP_CFG) CanTp_ChannelConfig[CANTP_CHL_NUM] =
{
	{
		.CanTpRxNSdu = &CanTpRxNSduP2P,
		.CanTpTxNSdu = &CanTpTxNSduP2P,
		.CanTpChannelMode = CANTP_MODE_FULL_DUPLEX
	},
	{
		.CanTpRxNSdu = &CanTpRxNSduP2A,
		.CanTpTxNSdu = &CanTpTxNSduP2A,
		.CanTpChannelMode = CANTP_MODE_FULL_DUPLEX
	}
};
CONST(CanTp_ConfigType,MEM_CANTP_CFG) CanTp_Config =
{
	.CanTpChannel = CanTp_ChannelConfig,
	.CanTpMainFunctionPeriod = 10	/* ms */
};
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */


#ifdef __cplusplus
} /* namespace autosar */
#endif
