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
typedef enum {
    CAN_HANDE_TYPE_BASIC,
    CAN_HANDLE_TYPE_FULL
} Can_HandleType;

typedef enum {
    CAN_ID_TYPE_EXTENDED,
    CAN_ID_TYPE_MIXED,
    CAN_ID_TYPE_STANDARD
} Can_IdTypeType;

typedef enum {
    CAN_OBJECT_TYPE_RECEIVE,
    CAN_OBJECT_TYPE_TRANSMIT
} Can_ObjectTypeType;

/* What is a hardware object and how to use it?
 * This is the most important question.For most of ECU, such as 9s12xep100, a hardware object
 * is a message box, and it has 3 TX message box and a 5 message buffers FIFO for Rx message.
 * and how to use it, what I think is that it always has something to do with APP.
 * Here would like to use this simulation platform on Qt to give an example.  */
typedef struct Can_HardwareObjectStruct {
	Can_HandleType CanHandleType;
    Can_IdTypeType CanIdType;
    Can_IdType CanIdValue;
    Can_HwHandleType  CanObjectId;
    Can_ObjectTypeType CanObjectType;
} Can_HardwareObjectType;

typedef enum {
    CAN_CTRL_0 = 0,
    CAN_CTRL_1,
    CAN_CONTROLLER_CNT
}Can_ControllerIdType;
typedef enum {
    CAN_EVENT_PROCESS_TYPE_INTERRUPT,
    CAN_EVENT_PROCESS_TYPE_POLLING
} Can_EventProcessType;

typedef struct
{
    Can_ControllerIdType  CanControllerId;
    Can_EventProcessType CanRxProcessing;
    Can_EventProcessType CanTxProcessing;
    Can_EventProcessType CanWakeupProcessing;
    Can_EventProcessType CanBusOffProcessing;
    uint16          CanControllerBaudRate;
    uint16          CanControllerPropSeg;
    uint16          CanControllerSeg1;
    uint16          CanControllerSeg2;
    const Can_HardwareObjectType  *CanHardwareObject;
    uint16 CanHardwareObjectNumber;
}Can_ControllerConfigType;
typedef struct
{
	const Can_ControllerConfigType *CanController;
	uint32 CanControllerNumber;
}Can_ConfigType;
/* ============================ [ DATAS     ] ====================================================== */
extern CONST(Can_ControllerConfigType,MEM_CAN_CONFIG) Can_ControllerConfig[CAN_CONTROLLER_CNT];
extern CONST(Can_ConfigType,MEM_CAN_CONFIG) Can_Config;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __cplusplus
}}  /* name space */
#endif
#endif /* CAN_CFG_H_ */
