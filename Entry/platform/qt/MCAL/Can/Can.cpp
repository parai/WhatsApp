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
#include "entry.h"
#include "arcan.h"
#include "Can.h"
#include "CanIf.h"
#include "Det.h"
#ifdef __cplusplus
namespace autosar {  extern "C" {
#endif

/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
STATIC const Can_ConfigType *canConfig;
STATIC boolean canInitialised = FALSE;
/* ============================ [ FUNCTIONS ] ====================================================== */
FUNC(void,MEM_Can_Init) Can_Init ( const Can_ConfigType *Config )
{
	uint8 i;
	canConfig = Config;

	canInitialised = TRUE;

    Entry::Self()->registerDevice(new arCan(CAN_DEVICE_NAME,CAN_CTRL_NUM,Entry::Self()));
}

FUNC(void,MEM_Can_DeInit) Can_DeInit ( void )
{
	canInitialised = FALSE;

    Entry::Self()->deleteDevice(CAN_DEVICE_NAME);
}

FUNC(void,MEM_Can_InitController) Can_InitController ( uint8 controller, const Can_ControllerConfigType *config )
{

}

FUNC(Can_ReturnType,MEM_Can_SetControllerMode) Can_SetControllerMode ( uint8 Controller , Can_StateTransitionType transition )
{
	Can_ReturnType ercd = CAN_OK;
	/* simulation implementation */
	switch (transition)
	{
		case CAN_T_START:
			CanIf_ControllerModeIndication(Controller,CANIF_CS_STARTED);
			break;
		case CAN_T_STOP:
			CanIf_ControllerModeIndication(Controller,CANIF_CS_STOPPED);
			break;
		case CAN_T_SLEEP:
			CanIf_ControllerModeIndication(Controller,CANIF_CS_SLEEP);
			break;
		case CAN_T_WAKEUP:
			CanIf_ControllerModeIndication(Controller,CANIF_CS_STOPPED);
			break;
		default:
			ercd = CAN_NOT_OK;
			break;
	}
	return ercd;
}

FUNC(void,MEM_Can_DisableControllerInterrupts) Can_DisableControllerInterrupts( uint8 controller ){}
FUNC(void,MEM_Can_EnableControllerInterrupts) Can_EnableControllerInterrupts( uint8 controller ){}

FUNC(Can_ReturnType,MEM_Can_Write) Can_Write( Can_HwHandleType hwh, Can_PduType *pduInfo )
{
	Can_ReturnType ercd = CAN_NOT_OK;

#if ( CAN_DEV_ERROR_DETECT == 1 )
	if (FALSE == canInitialised)
	{
		Det_ReportError(MODULE_ID_CAN,0,0x06,CAN_E_UNINIT);
	}
	else if (hwh >= CAN_HW_OBJECT_NUM)
	{
		Det_ReportError(MODULE_ID_CAN,0,0x06,CAN_E_PARAM_HANDLE);
	}
	else if (NULL == pduInfo)
	{
		Det_ReportError(MODULE_ID_CAN,0,0x06,CAN_E_PARAM_POINTER);
	}
	else if (pduInfo->length > 8 )
	{
		Det_ReportError(MODULE_ID_CAN,0,0x06,CAN_E_PARAM_DLC);
	}
	else
	{
#endif
		OcMessage* msg= new OcMessage(pduInfo->id,pduInfo->sdu,pduInfo->length,false);
        const Can_HardwareObjectType* hth = &canConfig->CanHardwareObject[hwh];

		msg->setBusId(hth->CanControllerRef->CanControllerId);

		arCan* can = (arCan*)Entry::Self()->getDevice(CAN_DEVICE_NAME);

		if ( NULL != can )
		{
			can->WriteMessage(pduInfo->swPduHandle,msg);
		}
		else
		{
			ercd = CAN_NOT_OK;
		}
#if ( CAN_DEV_ERROR_DETECT == 1 )
	}
#endif
	return ercd;
}

FUNC(void,MEM_Can_TxConfirmation) Can_TxConfirmation ( PduIdType canTxPduId )
{
	CanIf_TxConfirmation(canTxPduId);
}
FUNC(void,MEM_Can_RxIndication)  Can_RxIndication( uint8 bus, Can_IdType CanId, uint8 CanDlc, const uint8 *CanSduPtr )
{
	uint8 hrh;
	switch(bus)
	{
		case CAN_CTRL_0:
			hrh = CAN0_RX_OBJECT;
			break;
		case CAN_CTRL_1:
			hrh = CAN1_RX_OBJECT;
			break;
	}
	CanIf_RxIndication(hrh,CanId,CanDlc,CanSduPtr);
}
#ifdef __cplusplus
} }/* namespace autosar */
#endif
