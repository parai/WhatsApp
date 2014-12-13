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

#ifndef CAN_H_
#define CAN_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Modules.h"
#include "ComStack_Types.h"
#ifdef __cplusplus
namespace autosar { extern "C" {
#endif
/* ============================ [ MACROS    ] ====================================================== */
#define CAN_VENDOR_ID			    VENDOR_ID_WHATSAPP
#define CAN_MODULE_ID			    MODULE_ID_CAN

/* can version 00.01#00 */
#define CAN_AR_MAJOR_VERSION	0
#define CAN_AR_MINOR_VERSION	1
#define CAN_AR_PATCH_VERSION	0

/* can sw version 00.01#00 */
#define CAN_SW_MAJOR_VERSION	0
#define CAN_SW_MINOR_VERSION 	1
#define CAN_SW_PATCH_VERSION	0

#define CAN_E_PARAM_POINTER     0x01
#define CAN_E_PARAM_HANDLE      0x02
#define CAN_E_PARAM_DLC     	0x03
#define CAN_E_PARAM_CONTROLLER  0x04
/* API service used without initialization */
#define CAN_E_UNINIT           0x05
/* Init transition for current mode */
#define CAN_E_TRANSITION       0x06

#define CAN_E_DATALOST         0x07     /** @req 4.0.3/CAN395 */

/** @name Service id's */
#define CAN_INIT_SERVICE_ID                         0x00
#define CAN_MAINFUNCTION_WRITE_SERVICE_ID           0x01
#define CAN_INITCONTROLLER_SERVICE_ID               0x02
#define CAN_SETCONTROLLERMODE_SERVICE_ID            0x03
#define CAN_DISABLECONTROLLERINTERRUPTS_SERVICE_ID  0x04
#define CAN_ENABLECONTROLLERINTERRUPTS_SERVICE_ID   0x05
#define CAN_WRITE_SERVICE_ID                        0x06
#define CAN_GETVERSIONINFO_SERVICE_ID               0x07
#define CAN_MAINFUNCTION_READ_SERVICE_ID            0x08
#define CAN_MAINFUNCTION_BUSOFF_SERVICE_ID          0x09
#define CAN_MAINFUNCTION_WAKEUP_SERVICE_ID          0x0a
#define CAN_CBK_CHECKWAKEUP_SERVICE_ID              0x0b
/* ============================ [ TYPES     ] ====================================================== */
typedef uint32 Can_IdType;

typedef struct Can_PduType_s {
    /* the CAN ID, 29 or 11-bit */
	Can_IdType 	id;
	uint8		length;
	uint8 		*sdu;
    PduIdType   swPduHandle; 	/* private data for CanIf,just save and use for callback */
} Can_PduType;

typedef uint16 Can_HwHandleType;

typedef enum {
	CAN_T_START,
	CAN_T_STOP,
	CAN_T_SLEEP,
	CAN_T_WAKEUP
} Can_StateTransitionType;

typedef enum {
	CAN_OK,
	CAN_NOT_OK,
	CAN_BUSY
} Can_ReturnType;

#ifdef __cplusplus
}}
#endif
#include "Can_Types.h"
#include "Can_Cfg.h"

#ifdef __cplusplus
namespace autosar { extern "C" {
#endif
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
FUNC(void,MEM_Can_Init)   Can_Init   ( const Can_ConfigType *Config );
FUNC(void,MEM_Can_DeInit) Can_DeInit ( void );

FUNC(void,MEM_Can_InitController) 				Can_InitController    ( uint8 controller, const Can_ControllerConfigType *config );
FUNC(Can_ReturnType,MEM_Can_SetControllerMode) 	Can_SetControllerMode ( uint8 Controller, Can_StateTransitionType transition );
FUNC(void,MEM_Can_DisableControllerInterrupts)  Can_DisableControllerInterrupts ( uint8 controller );
FUNC(void,MEM_Can_EnableControllerInterrupts)   Can_EnableControllerInterrupts  ( uint8 controller );

FUNC(Can_ReturnType,MEM_Can_Write) Can_Write( Can_HwHandleType hwh, Can_PduType *pduInfo );

FUNC(void,MEM_Can_Cbk_CheckWakeup)     Can_Cbk_CheckWakeup     ( uint8 controller );
FUNC(void,MEM_Can_MainFunction_Write)  Can_MainFunction_Write  ( void );
FUNC(void,MEM_Can_MainFunction_Read)   Can_MainFunction_Read   ( void );
FUNC(void,MEM_Can_MainFunction_BusOff) Can_MainFunction_BusOff ( void );
FUNC(void,MEM_Can_MainFunction_Error)  Can_MainFunction_Error  ( void );
FUNC(void,MEM_Can_MainFunction_Wakeup) Can_MainFunction_Wakeup ( void );

FUNC(void,MEM_Can_TxConfirmation) Can_TxConfirmation ( PduIdType canTxPduId );
FUNC(void,MEM_Can_RxIndication)   Can_RxIndication( uint8 bus, Can_IdType CanId, uint8 CanDlc, const uint8 *CanSduPtr );

#ifdef __cplusplus
}}
#endif

#endif /*CAN_H_*/
