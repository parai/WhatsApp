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
#include "Can.h"
#ifdef __cplusplus
namespace autosar {
#endif

/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
STATIC CONST(Can_HardwareObjectType,MEM_CAN_CONFIG) Can_Controller0HwObject[2] =
{
	{
		CAN_HANDE_TYPE_BASIC,
		CAN_ID_TYPE_STANDARD,
		0xFFFF,	/* For Tx, means nothing */
		CAN0_OBJECT_TX,
		CAN_OBJECT_TYPE_TRANSMIT
	},
	{
		CAN_HANDE_TYPE_BASIC,
		CAN_ID_TYPE_STANDARD,
		0xFFFF,	/* For Rx, let all in, do SW filter */
		CAN0_OBJECT_RX,
		CAN_OBJECT_TYPE_TRANSMIT
	}
};

STATIC CONST(Can_HardwareObjectType,MEM_CAN_CONFIG) Can_Controller1HwObject[2] =
{
	{
		CAN_HANDE_TYPE_BASIC,
		CAN_ID_TYPE_STANDARD,
		0xFFFF,	/* For Tx, means nothing */
		CAN1_OBJECT_TX,
		CAN_OBJECT_TYPE_TRANSMIT
	},
	{
		CAN_HANDE_TYPE_BASIC,
		CAN_ID_TYPE_STANDARD,
		0xFFFF,	/* For Rx, let all in, do SW filter */
		CAN1_OBJECT_RX,
		CAN_OBJECT_TYPE_TRANSMIT
	}
};
CONST(Can_ControllerConfigType,MEM_CAN_CONFIG) Can_ControllerConfig[CAN_CONTROLLER_CNT] =
{
	{
		CAN_CTRL_0,
		CAN_EVENT_PROCESS_TYPE_INTERRUPT,
		CAN_EVENT_PROCESS_TYPE_INTERRUPT,
		CAN_EVENT_PROCESS_TYPE_INTERRUPT,
		CAN_EVENT_PROCESS_TYPE_INTERRUPT,
		500000,	/* 500 kbps */
		12,
		1,
		3,
		Can_Controller0HwObject,
		2
	},
	{
		CAN_CTRL_1,
		CAN_EVENT_PROCESS_TYPE_INTERRUPT,
		CAN_EVENT_PROCESS_TYPE_INTERRUPT,
		CAN_EVENT_PROCESS_TYPE_INTERRUPT,
		CAN_EVENT_PROCESS_TYPE_INTERRUPT,
		500000,	/* 500 kbps */
		12,
		1,
		3,
		Can_Controller1HwObject,
		2
	}
};

CONST(Can_ConfigType,MEM_CAN_CONFIG) Can_Config =
{
		Can_ControllerConfig,
		2
};
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */


#ifdef __cplusplus
} /* namespace autosar */
#endif
