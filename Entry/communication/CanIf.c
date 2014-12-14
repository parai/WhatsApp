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
#include "Det.h"
#ifdef __cplusplus
namespace autosar {
#endif

/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
#if ( CANIF_DEV_ERROR_DETECT == 1 )
STATIC boolean canIfInitialized = FALSE;
#endif
STATIC CanIf_ControllerModeType canIfControllerMode[CANIF_CHL_NUMBER];
STATIC CanIf_ChannelGetModeType canIfPduMode[CANIF_CHL_NUMBER];
STATIC CanIf_ConfigType* canIfConfig;
#if (CANIF_DYNAMIC_CAN_TX_PDUID_NUMBER > 0)
STATIC Can_IdType canIfDynamicIds[CANIF_DYNAMIC_CAN_TX_PDUID_NUMBER];
#endif
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
FUNC(void,MEM_CanIf_Init) CanIf_Init ( const CanIf_ConfigType* ConfigPtr )
{
	CanIf_ChannelIdType chlid;
#if ( CANIF_DEV_ERROR_DETECT == 1 )
	if ( NULL == ConfigPtr )
	{
		Det_ReportError(MODULE_ID_CANIF,0,0x01,CANIF_E_PARAM_POINTER);
	}
	else
	{
		canIfInitialized = TRUE;
#endif
		canIfConfig = ConfigPtr;
		for(chlid=0;chlid<CANIF_CHL_NUMBER;chlid++)
		{
			uint8 canControllerId;
			const Can_ControllerConfigType * canConfig;
//			canControllerId = ConfigPtr->CanIfInitConfig->CanIfCtrlCfg[chlid].CanIfCtrlId;
//			canConfig = ConfigPtr->CanIfInitConfig->CanIfCtrlCfg[chlid].CanIfCtrlCanCtrlIdRef;
			Can_InitController(canControllerId, canConfig);
			canIfControllerMode[chlid] = CANIF_CS_STOPPED;
			canIfPduMode[chlid] = CANIF_GET_OFFLINE;
		}

#if (CANIF_DYNAMIC_CAN_TX_PDUID_NUMBER > 0)
		{   /* dynamic L-PDU's ID in CANIF must <= CanIfInitNumberOfDynamicCanTxPduIds */
			PduIdType i;
//			for(i=0;i<ConfigPtr->CanIfInitConfig->CanIfInitNumberOfDynamicCanTxPduIds;i++)
//			{
//				canIfDynamicIds[i] = ConfigPtr->CanIfInitConfig->CanIfTxPduCfg[i].CanIfTxPduCanId;
//			}
		}
#endif
#if ( CANIF_DEV_ERROR_DETECT == 1 )
	}
#endif
}

FUNC(Std_ReturnType,MEM_CanIf_SetControllerMode) CanIf_SetControllerMode ( uint8 ControllerId ,
		CanIf_ControllerModeType ControllerMode )
{
	Std_ReturnType ercd = E_NOT_OK;
#if ( CANIF_DEV_ERROR_DETECT == 1 )
	if ( FALSE == canIfInitialized )
	{
		Det_ReportError(MODULE_ID_CANIF,0,0x03,CANIF_E_UNINIT);
	}
	else if ( ControllerId >= CANIF_CHL_NUMBER)
	{
		Det_ReportError(MODULE_ID_CANIF,0,0x03,CANIF_E_PARAM_CONTROLLERID);
	}
	else
	{
#endif
        uint8 canControllerId = 0;  //canIfConfig->CanIfInitConfig->CanIfCtrlCfg[ControllerId].CanIfCtrlCanCtrlIdRef->CanControllerId;
		/* According to Figure 30 Start CAN network,AUTOSAR 4.0 */
		switch (ControllerMode)
		{
			case CANIF_CS_SLEEP:
			{
				Can_ReturnType result = Can_SetControllerMode(canControllerId,CAN_T_SLEEP);
				if (CAN_OK == result)
				{
					ercd = E_OK;
				}
				break;
			}
			case CANIF_CS_STARTED:
			{
				Can_ReturnType result = Can_SetControllerMode(canControllerId,CAN_T_START);
				if (CAN_OK == result)
				{
					ercd = E_OK;
				}
				break;
			}
			case CANIF_CS_STOPPED:
			{
				Can_ReturnType result;
				/* see CAN417 */
				if (CANIF_CS_SLEEP == canIfControllerMode[ControllerId])
				{
					result = Can_SetControllerMode(canControllerId,CAN_T_WAKEUP);
				}
				else
				{
					result = Can_SetControllerMode(canControllerId,CAN_T_STOP);
				}
				if (CAN_OK == result)
				{
					ercd = E_OK;
				}
				break;
			}
		}
#if ( CANIF_DEV_ERROR_DETECT == 1 )
	}
#endif
	return ercd;
}
FUNC(Std_ReturnType,MEM_CanIf_GetControllerMode) CanIf_GetControllerMode ( uint8 ControllerId ,
		CanIf_ControllerModeType* ControllerModePtr )
{
	Std_ReturnType ercd = E_NOT_OK;
#if ( CANIF_DEV_ERROR_DETECT == 1 )
	if ( FALSE == canIfInitialized )
	{
		Det_ReportError(MODULE_ID_CANIF,0,0x04,CANIF_E_UNINIT);
	}
	else if ( ControllerId >= CANIF_CHL_NUMBER )
	{
		Det_ReportError(MODULE_ID_CANIF,0,0x04,CANIF_E_PARAM_CONTROLLERID);
	}
	else if ( NULL == ControllerModePtr )
	{
		Det_ReportError(MODULE_ID_CANIF,0,0x04,CANIF_E_PARAM_POINTER);
	}
	else
	{
#endif
		ercd = E_OK;
		*ControllerModePtr = canIfControllerMode[ControllerId];
#if ( CANIF_DEV_ERROR_DETECT == 1 )
	}
#endif
	return ercd;
}

FUNC(Std_ReturnType,MEM_CanIf_Transmit) CanIf_Transmit ( PduIdType CanTxPduId , const PduInfoType* PduInfoPtr )
{
	Std_ReturnType ercd = E_NOT_OK;
#if ( CANIF_DEV_ERROR_DETECT == 1 )
	if ( FALSE == canIfInitialized )
	{
		Det_ReportError(MODULE_ID_CANIF,0,0x05,CANIF_E_UNINIT);
	}
//	else if ( CanTxPduId >= (canIfConfig->CanIfInitConfig->CanIfInitNumberOfStaticCanTXPduIds
//							 + canIfConfig->CanIfInitConfig->CanIfInitNumberOfDynamicCanTxPduIds) )
//	{
//		Det_ReportError(MODULE_ID_CANIF,0,0x05,CANIF_E_INVALID_TXPDUID);
//	}
	else if ( NULL == PduInfoPtr )
	{
		Det_ReportError(MODULE_ID_CANIF,0,0x05,CANIF_E_PARAM_POINTER);
	}
	else
	{
#endif
//		const CanIf_TxPduConfigType* txPduCfg = &canIfConfig->CanIfInitConfig->CanIfTxPduCfg[CanTxPduId];
//		uint8 chlid = txPduCfg->CanIfTxPduHthIdRef->CanIfHthCanCtrlIdRef->CanIfCtrlId;
//		if ( (CANIF_CS_STARTED == canIfControllerMode[chlid]) &&
//			 ((CANIF_GET_ONLINE == canIfPduMode[chlid]) || (CANIF_GET_TX_ONLINE == canIfPduMode[chlid])) )
//		{
//			Can_PduType pdu;
//			Can_ReturnType result;

//			Can_HwHandleType hth = txPduCfg->CanIfTxPduHthIdRef->CanIfHthIdSymRef;
//			if ( CANIF_PDU_TYPE_DYNAMIC == txPduCfg->CanIfTxPduType )
//			{ /* configuration tool should make sure all the dynamic PDUs in the front of the list of CanIfTxPduCfg */
//				pdu.id = canIfDynamicIds[CanTxPduId];
//			}
//			else
//			{
//				pdu.id = txPduCfg->CanIfTxPduCanId;
//			}

//			if ( CANIF_ID_TYPE_EXTENDED == txPduCfg->CanIfTxPduCanIdType )
//			{
//				pdu.id |= 0x80000000UL; /* indicate CAN that id is 29 bits long */
//			}
//			pdu.length = PduInfoPtr->SduLength;
//			pdu.sdu    = PduInfoPtr->SduDataPtr;
//			pdu.swPduHandle = CanTxPduId;

//			result = Can_Write(hth,&pdu);

//			if ( CAN_OK == result )
//			{
//				ercd = E_OK;
//			}
//		}
//		else
//		{
//			/* not on line */
//		}
#if ( CANIF_DEV_ERROR_DETECT == 1 )
	}
#endif
	return ercd;
}
FUNC(void,MEM_CanIf_ControllerModeIndication) CanIf_ControllerModeIndication ( uint8 Controller ,
		CanIf_ControllerModeType ControllerMode )
{
	uint8 chlid = UINT8_INVALID;
	uint8 i;
	/* change parameter CAN Controller to CANIF channel Id */
	for (i=0;i<CANIF_CHL_NUMBER;i++)
	{
//		if(Controller==(canIfConfig->CanIfInitConfig->CanIfCtrlCfg[i].CanIfCtrlCanCtrlIdRef->CanControllerId))
//		{
//			chlid = i;
//			break;
//		}
	}
#if ( CANIF_DEV_ERROR_DETECT == 1 )
	if ( FALSE == canIfInitialized )
	{
		Det_ReportError(MODULE_ID_CANIF,0,0x17,CANIF_E_UNINIT);
	}
	else if ( chlid != UINT8_INVALID)
	{
		Det_ReportError(MODULE_ID_CANIF,0,0x17,CANIF_E_PARAM_CONTROLLER);
	}
	else
	{
#endif
		canIfControllerMode[chlid] = ControllerMode;
		// TODO: UL notify
#if ( CANIF_DEV_ERROR_DETECT == 1 )
	}
#endif
}
FUNC(void,MEM_CanIf_TxConfirmation) CanIf_TxConfirmation ( PduIdType canTxPduId )
{

}
FUNC(void,MEM_CanIf_RxIndication) CanIf_RxIndication ( uint8 Hrh , Can_IdType CanId , uint8 CanDlc ,
		const uint8 *CanSduPtr )
{

}

#ifdef __cplusplus
} /* namespace autosar */
#endif
