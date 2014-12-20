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
STATIC CONST(Can_FilterMaskType,MEM_CAN_CONFIG) Can_FilterMask[1] =
{
	{
		.CanFilterMaskValue = 0	/* no filter */
	}
};
STATIC CONST(Can_ControllerBaudrateConfigType,MEM_CAN_CONFIG) Can_ControllerBaudrateConfig[2] =
{	/* just example, maybe with wrong parameter */
	{
		.CanControllerBaudRate = 250,
		.CanControllerPropSeg  = 1,
		.CanControllerSeg1     = 12,
		.CanControllerSeg2	   = 1,
		.CanControllerSyncJumpWidth = 1
	},
	{
		.CanControllerBaudRate = 500,
		.CanControllerPropSeg  = 1,
		.CanControllerSeg1     = 3,
		.CanControllerSeg2	   = 8,
		.CanControllerSyncJumpWidth = 1
	}
};
CONST(Can_ControllerConfigType,MEM_CAN_CONFIG) Can_ControllerConfig[CAN_CTRL_NUM] =
{
	{
		.CanControllerBaudrateConfig = &Can_ControllerBaudrateConfig[0],
		.CanFilterMask	= &Can_FilterMask[0],
		.CanTTController = NULL,
		.CanBusoffProcessing = CAN_BUSOFFPROCESSING_INTERRUPT,
		.CanControllerActivation = TRUE,
		.CanControllerBaseAddress = 0,
		.CanControllerId = CAN_CTRL_0,
		.CanRxProcessing = CAN_RXPROCESSING_INTERRUPT,
		.CanTxProcessing = CAN_TXPROCESSING_INTERRUPT,
		.CanWakeupProcessing = CAN_WAKEUPPROCESSING_INTERRUPT,
		.CanWakeupSupport = TRUE,
		.CanControllerDefaultBaudrate = &Can_ControllerBaudrateConfig[0],
		.CanCpuClockRef = NULL,	/* TODO */
		.CanWakeupSourceRef = NULL	/* TODO */
	},
	{
		.CanControllerBaudrateConfig = &Can_ControllerBaudrateConfig[1],
		.CanFilterMask	= &Can_FilterMask[0],
		.CanTTController = NULL,
		.CanBusoffProcessing = CAN_BUSOFFPROCESSING_INTERRUPT,
		.CanControllerActivation = TRUE,
		.CanControllerBaseAddress = 0,
		.CanControllerId = CAN_CTRL_1,
		.CanRxProcessing = CAN_RXPROCESSING_INTERRUPT,
		.CanTxProcessing = CAN_TXPROCESSING_INTERRUPT,
		.CanWakeupProcessing = CAN_WAKEUPPROCESSING_INTERRUPT,
		.CanWakeupSupport = TRUE,
		.CanControllerDefaultBaudrate = &Can_ControllerBaudrateConfig[1],
		.CanCpuClockRef = NULL,	/* TODO */
		.CanWakeupSourceRef = NULL	/* TODO */
	}
};

CONST(Can_HardwareObjectType,MEM_CAN_CONFIG) Can_HardwareObject[CAN_HW_OBJECT_NUM] =
{
	{
		.CanTTHardwareObjectTrigger = NULL,
		.CanHandleType = CAN_HANDLETYPE_BASIC,
		.CanIdType = CAN_IDTYPE_STANDARD,
		.CanIdValue = 0,
		.CanObjectType = CAN_OBJECTTYPE_RECEIVE,
		.CanControllerRef = &Can_ControllerConfig[CAN_CTRL_0],
		.CanFilterMaskRef = NULL,
		.CanMainFunctionRWPeriodRef = NULL
	},
	{
		.CanTTHardwareObjectTrigger = NULL,
		.CanHandleType = CAN_HANDLETYPE_BASIC,
		.CanIdType = CAN_IDTYPE_STANDARD,
		.CanIdValue = 0,
		.CanObjectType = CAN_OBJECTTYPE_TRANSMIT,
		.CanControllerRef = &Can_ControllerConfig[CAN_CTRL_0],
		.CanFilterMaskRef = NULL,
		.CanMainFunctionRWPeriodRef = NULL
	},
	{
		.CanTTHardwareObjectTrigger = NULL,
		.CanHandleType = CAN_HANDLETYPE_BASIC,
		.CanIdType = CAN_IDTYPE_STANDARD,
		.CanIdValue = 0,
		.CanObjectType = CAN_OBJECTTYPE_RECEIVE,
		.CanControllerRef = &Can_ControllerConfig[CAN_CTRL_1],
		.CanFilterMaskRef = NULL,
		.CanMainFunctionRWPeriodRef = NULL
	},
	{
		.CanTTHardwareObjectTrigger = NULL,
		.CanHandleType = CAN_HANDLETYPE_BASIC,
		.CanIdType = CAN_IDTYPE_STANDARD,
		.CanIdValue = 0,
		.CanObjectType = CAN_OBJECTTYPE_TRANSMIT,
		.CanControllerRef = &Can_ControllerConfig[CAN_CTRL_1],
		.CanFilterMaskRef = NULL,
		.CanMainFunctionRWPeriodRef = NULL
	}
};
CONST(Can_ConfigType,MEM_CAN_CONFIG) Can_Config	=
{
	.CanController = Can_ControllerConfig,
	.CanHardwareObject = Can_HardwareObject
};
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */


#ifdef __cplusplus
} /* namespace autosar */
#endif
