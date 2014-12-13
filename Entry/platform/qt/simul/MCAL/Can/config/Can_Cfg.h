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

#define CAN0_OBJECT_RX   (Can_HwHandleType )0
#define CAN1_OBJECT_RX   (Can_HwHandleType )1

#define CAN0_OBJECT_TX   (Can_HwHandleType )0
#define CAN1_OBJECT_TX   (Can_HwHandleType )1
/* ============================ [ TYPES     ] ====================================================== */

/* ============================ [ DATAS     ] ====================================================== */
extern CONST(Can_ControllerType,MEM_CAN_CONFIG) Can_ControllerConfig[];
extern CONST(Can_ConfigSetType,MEM_CAN_CONFIG) Can_Config;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __cplusplus
}}  /* name space */
#endif
#endif /* CAN_CFG_H_ */
