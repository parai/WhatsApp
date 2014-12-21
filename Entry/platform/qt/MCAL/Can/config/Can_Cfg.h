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
#ifndef CAN_CFG_H_
#define CAN_CFG_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#ifdef __cplusplus
namespace autosar { extern "C" {
#endif
/* ============================ [ MACROS    ] ====================================================== */
#define CAN_DEVICE_NAME   "Can"

enum
{
	CAN_CTRL_0 = 0,
	CAN_CTRL_1,
	CAN_CTRL_NUM
};

enum
{
	CAN0_RX_OBJECT = 0,
	CAN0_TX_OBJECT,
	CAN1_RX_OBJECT,
	CAN1_TX_OBJECT,
	CAN_HW_OBJECT_NUM
};

#define CAN_DEV_ERROR_DETECT			1
/* ============================ [ TYPES     ] ====================================================== */

/* ============================ [ DATAS     ] ====================================================== */
extern CONST(Can_ControllerConfigType,MEM_CAN_CONFIG) Can_ControllerConfig[];
extern CONST(Can_ConfigType,MEM_CAN_CONFIG) Can_Config;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __cplusplus
}}  /* name space */
#endif
#endif /* CAN_CFG_H_ */
