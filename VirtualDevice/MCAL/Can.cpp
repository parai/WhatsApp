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
#include "CanIf.h"
#include "virtualcan.h"
#ifdef __cplusplus
namespace autosar {  extern "C" {
#endif

/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
STATIC const Can_ConfigType *canConfig;
/* ============================ [ FUNCTIONS ] ====================================================== */
FUNC(void,MEM_Can_Init) Can_Init ( const Can_ConfigType *Config )
{
	uint8 i;
	canConfig = Config;
	for (i=0;i<Config->CanControllerNumber;i++)
	{
		Can_InitController(Config->CanController[i].CanControllerId,&(Config->CanController[i]));
	}
}

FUNC(void,MEM_Can_DeInit) Can_DeInit ( void )
{
	// TODO
}

FUNC(void,MEM_Can_InitController) Can_InitController ( uint8 controller, const Can_ControllerConfigType *config )
{
	uint8 i;
	for(i=0;i<config->CanHardwareObjectNumber;i++)
	{
		// TODO: Initialize each HW object
	}
}

FUNC(Can_ReturnType,MEM_Can_SetControllerMode) Can_SetControllerMode( uint8 Controller, Can_StateTransitionType transition )
{
	Can_ReturnType ercd = CAN_OK;

	return ercd;
}

FUNC(void,MEM_Can_DisableControllerInterrupts) Can_DisableControllerInterrupts( uint8 controller ){}
FUNC(void,MEM_Can_EnableControllerInterrupts) Can_EnableControllerInterrupts( uint8 controller ){}

FUNC(Can_ReturnType,MEM_Can_Write) Can_Write( Can_HwHandleType hwh, Can_PduType *pduInfo )
{
	Can_ReturnType ercd = CAN_OK;

	OcMessage msg(pduInfo->id,pduInfo->sdu,pduInfo->length,false);

	switch (hwh)
	{
		case CAN0_OBJECT_TX:
			msg.setBusId(0);
			break;
		case CAN1_OBJECT_TX:
			msg.setBusId(1);
			break;
		default:
			break;
	}

	VirtualCan::GetInstance()->SendMessage(pduInfo->swPduHandle,&msg);

	return ercd;
}

FUNC(void,MEM_Can_TxConfirmation) Can_TxConfirmation ( PduIdType canTxPduId )
{
	CanIf_TxConfirmation(canTxPduId);
}
FUNC(void,MEM_Can_RxIndication)  Can_RxIndication( uint8 bus, Can_IdType CanId, uint8 CanDlc, const uint8 *CanSduPtr )
{
	uint8 hrh = UINT8_INVALID;
	switch(bus)
	{
		case 0:
			hrh = CAN0_OBJECT_RX;
			break;
		case 1:
			hrh = CAN1_OBJECT_RX;
			break;
		default:
			assert(0);
			break;
	}

	if(hrh != UINT8_INVALID)
	{
		CanIf_RxIndication(hrh,CanId,CanDlc,CanSduPtr);
	}
}
#ifdef __cplusplus
} }/* namespace autosar */
#endif
