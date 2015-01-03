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
STATIC CanIf_ControllerModeType canIfControllerMode[CANIF_CHL_NUM];
STATIC CanIf_ChannelGetModeType canIfChannelGetPduMode[CANIF_CHL_NUM];
STATIC CanIf_ConfigType* canIfConfig;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
static const CanIf_RxPduCfgType* find_rxpdu(uint32 CanId,uint8 Hrh)
{
	uint16 i;
	const CanIf_RxPduCfgType* targetRxPdu = NULL;
	for (i = 0; i < canIfConfig->CanIfRxPduNum; i++)
	{
		const CanIf_RxPduCfgType *rxPdu = &(canIfConfig->CanIfRxPduCfg[i]);
		if ( rxPdu->CanIfRxPduHrhIdRef->CanIfHrhIdSymRef->CanObjectId == Hrh)
		{
			if (CAN_HANDLETYPE_BASIC == (rxPdu->CanIfRxPduHrhIdRef->CanIfHrhIdSymRef->CanHandleType))
			{	/* basic can, do sw filter */
				if (rxPdu->CanIfRxPduHrhIdRef->CanIfHrhSoftwareFilter)
				{
					if (rxPdu->CanIfRxPduCanIdRange != NULL)
					{
						if ((rxPdu->CanIfRxPduCanIdRange->CanIfRxPduCanIdRangeLowerCanId<=CanId) &&
							(rxPdu->CanIfRxPduCanIdRange->CanIfRxPduCanIdRangeUpperCanId>=CanId))
						{
							targetRxPdu = rxPdu;
							break;
						}
						else
						{
							continue;
						}
					}
					else
					{
						if(rxPdu->CanIfRxPduCanId==CanId)
						{
							targetRxPdu = rxPdu;
							break;
						}
						else
						{
							continue;
						}
					}
				}
				else
				{	/* the way that do mask filter should be done by CAN Hardware object itself */
					if(rxPdu->CanIfRxPduCanId==CanId)
					{
						targetRxPdu = rxPdu;
						break;
					}
					else
					{
						continue;
					}
				}
			}
			else
			{	/* full can. no filter */
				if(rxPdu->CanIfRxPduCanId==CanId)
				{
					targetRxPdu = rxPdu;
					break;
				}
				else
				{
					continue;
				}
			}
		}
	}

	return targetRxPdu;
}
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
        for(chlid=0;chlid<CANIF_CHL_NUM;chlid++)
		{
			uint8 canControllerId;
			const Can_ControllerConfigType * canConfig;
			canControllerId = ConfigPtr->CanIfInitHohCfg->CanCtrlCfg->CanControllerId;
			canConfig = ConfigPtr->CanIfInitHohCfg->CanCtrlCfg;
			Can_InitController(canControllerId, canConfig);
			canIfControllerMode[chlid] = CANIF_CS_STOPPED;
			canIfChannelGetPduMode[chlid] = CANIF_GET_OFFLINE;
		}
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
    else if ( ControllerId >= CANIF_CHL_NUM)
	{
		Det_ReportError(MODULE_ID_CANIF,0,0x03,CANIF_E_PARAM_CONTROLLERID);
	}
	else
	{
#endif
        uint8 canControllerId = canIfConfig->CanIfInitHohCfg->CanCtrlCfg->CanControllerId;
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
    else if ( ControllerId >= CANIF_CHL_NUM )
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
FUNC(Std_ReturnType,MEM_CanIf_SetPduMode) CanIf_SetPduMode(uint8 ControllerId, CanIf_ChannelSetModeType PduModeRequest)
{
	Std_ReturnType ercd = E_NOT_OK;
#if ( CANIF_DEV_ERROR_DETECT == 1 )
	if ( FALSE == canIfInitialized )
	{
		Det_ReportError(MODULE_ID_CANIF,0,0x09,CANIF_E_UNINIT);
	}
    else if ( ControllerId >= CANIF_CHL_NUM )
	{
		Det_ReportError(MODULE_ID_CANIF,0,0x09,CANIF_E_PARAM_CONTROLLERID);
	}
	else
	{
#endif
		CanIf_ChannelGetModeType oldMode = canIfChannelGetPduMode[ControllerId];
		switch ( PduModeRequest )
		{
			case CANIF_SET_OFFLINE:
				canIfChannelGetPduMode[ControllerId] = CANIF_GET_OFFLINE;
				break;
			case CANIF_SET_RX_OFFLINE:
				if ( oldMode == CANIF_GET_RX_ONLINE )
				{
					canIfChannelGetPduMode[ControllerId] = CANIF_GET_OFFLINE;
				}
				else if ( oldMode == CANIF_GET_ONLINE )
				{
					canIfChannelGetPduMode[ControllerId] = CANIF_GET_TX_ONLINE;
				}
				else if ( oldMode == CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE )
				{
					canIfChannelGetPduMode[ControllerId] = CANIF_GET_OFFLINE_ACTIVE;
				}

				// Other oldmodes don't care
				break;
			case CANIF_SET_RX_ONLINE:
				if ( oldMode == CANIF_GET_OFFLINE )
				{
					canIfChannelGetPduMode[ControllerId] = CANIF_GET_RX_ONLINE;
				}
				else if ( oldMode == CANIF_GET_TX_ONLINE )
				{
					canIfChannelGetPduMode[ControllerId] = CANIF_GET_ONLINE;
				}
				else if ( oldMode == CANIF_GET_OFFLINE_ACTIVE )
				{
					canIfChannelGetPduMode[ControllerId] = CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE;
				}

				// Other oldmodes don't care
				break;
			case CANIF_SET_TX_OFFLINE:
				if ( oldMode == CANIF_GET_TX_ONLINE )
				{
					canIfChannelGetPduMode[ControllerId] = CANIF_GET_OFFLINE;
				}
				else if ( oldMode == CANIF_GET_ONLINE )
				{
					canIfChannelGetPduMode[ControllerId] = CANIF_GET_RX_ONLINE;
				}
				else if ( oldMode == CANIF_GET_OFFLINE_ACTIVE )
				{
					canIfChannelGetPduMode[ControllerId] = CANIF_GET_OFFLINE;
				}
				else if ( oldMode == CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE )
				{
					canIfChannelGetPduMode[ControllerId] = CANIF_GET_RX_ONLINE;
				}

				// Other oldmodes don't care
				break;
			case CANIF_SET_TX_ONLINE:
				if ( oldMode == CANIF_GET_OFFLINE )
				{
					canIfChannelGetPduMode[ControllerId] = CANIF_GET_TX_ONLINE;
				}
				else if ( oldMode == CANIF_GET_RX_ONLINE )
				{
					canIfChannelGetPduMode[ControllerId] = CANIF_GET_ONLINE;
				}
				else if ( oldMode == CANIF_GET_OFFLINE_ACTIVE )
				{
					canIfChannelGetPduMode[ControllerId] = CANIF_GET_TX_ONLINE;
				}
				else if ( oldMode == CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE )
				{
					canIfChannelGetPduMode[ControllerId] = CANIF_GET_ONLINE;
				}

				// Other oldmodes don't care
				break;
			case CANIF_SET_ONLINE:
				canIfChannelGetPduMode[ControllerId] = CANIF_GET_ONLINE;
				break;

			case CANIF_SET_TX_OFFLINE_ACTIVE:
				if ( oldMode == CANIF_GET_OFFLINE )
				{
					canIfChannelGetPduMode[ControllerId] = CANIF_GET_OFFLINE_ACTIVE;
				}
				else if ( oldMode == CANIF_GET_RX_ONLINE )
				{
					canIfChannelGetPduMode[ControllerId] = CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE;
				}
				else if ( oldMode == CANIF_GET_TX_ONLINE )
				{
					canIfChannelGetPduMode[ControllerId] = CANIF_GET_OFFLINE_ACTIVE;
				}
				else if ( oldMode == CANIF_GET_ONLINE )
				{
					canIfChannelGetPduMode[ControllerId] = CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE;
				}

				// Other oldmodes don't care
				break;
		}

		ercd = E_OK;
#if ( CANIF_DEV_ERROR_DETECT == 1 )
	}
#endif
  return ercd;
}

FUNC(Std_ReturnType,MEM_CanIf_GetPduMode) CanIf_GetPduMode(uint8 ControllerId,CanIf_ChannelGetModeType *PduModePtr)
{
	Std_ReturnType ercd = E_NOT_OK;
#if ( CANIF_DEV_ERROR_DETECT == 1 )
	if ( FALSE == canIfInitialized )
	{
		Det_ReportError(MODULE_ID_CANIF,0,0x0A,CANIF_E_UNINIT);
	}
    else if ( ControllerId >= CANIF_CHL_NUM )
	{
		Det_ReportError(MODULE_ID_CANIF,0,0x0A,CANIF_E_PARAM_CONTROLLERID);
	}
	else
	{
#endif
		*PduModePtr = canIfChannelGetPduMode[ControllerId];
#if ( CANIF_DEV_ERROR_DETECT == 1 )
	}
#endif


  return E_OK;
}

FUNC(Std_ReturnType,MEM_CanIf_Transmit) CanIf_Transmit ( PduIdType CanTxPduId , const PduInfoType* PduInfoPtr )
{
	Std_ReturnType ercd = E_NOT_OK;
#if ( CANIF_DEV_ERROR_DETECT == 1 )
	if ( FALSE == canIfInitialized )
	{
		Det_ReportError(MODULE_ID_CANIF,0,0x05,CANIF_E_UNINIT);
	}
	else if ( CanTxPduId >= (canIfConfig->CanIfTxPduNum) )
	{
		Det_ReportError(MODULE_ID_CANIF,0,0x05,CANIF_E_INVALID_TXPDUID);
	}
	else if ( NULL == PduInfoPtr )
	{
		Det_ReportError(MODULE_ID_CANIF,0,0x05,CANIF_E_PARAM_POINTER);
	}
	else
	{
#endif
		const CanIf_TxPduCfgType* txPduCfg = &canIfConfig->CanIfTxPduCfg[CanTxPduId];
		uint8 chlid = txPduCfg->CanIfTxPduHthIdRef->CanIfHthCanCtrlIdRef->CanIfCtrlId;
		if ( (CANIF_CS_STARTED == canIfControllerMode[chlid]) &&
			 ((CANIF_GET_ONLINE == canIfChannelGetPduMode[chlid]) || (CANIF_GET_TX_ONLINE == canIfChannelGetPduMode[chlid])) )
		{
			Can_PduType pdu;
			Can_ReturnType result;

			Can_HwHandleType hth = txPduCfg->CanIfTxPduHthIdRef->CanIfHthIdSymRef->CanObjectId;
			if ( CANIF_TXPDUTYPE_DYNAMIC == txPduCfg->CanIfTxPduType )
			{ /* configuration tool should make sure all the dynamic PDUs in the front of the list of CanIfTxPduCfg */
				/* TODO */
				assert(0);
			}
			else
			{
				pdu.id = txPduCfg->CanIfTxPduCanId;
			}

			if ( CANIF_TXPDUCANIDTYPE_EXTENDED_CAN == txPduCfg->CanIfTxPduCanIdType )
			{
				pdu.id |= 0x80000000UL; /* indicate CAN that id is 29 bits long */
			}
			pdu.length = PduInfoPtr->SduLength;
			pdu.sdu    = PduInfoPtr->SduDataPtr;
			pdu.swPduHandle = CanTxPduId;

			result = Can_Write(hth,&pdu);

			if ( CAN_OK == result )
			{
				ercd = E_OK;
			}
		}
		else
		{
			/* not on line */
		}
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
    for (i=0;i<CANIF_CHL_NUM;i++)
	{
		if(Controller==(canIfConfig->CanIfInitHohCfg->CanCtrlCfg->CanControllerId))
		{
			chlid = i;
			break;
		}
	}
#if ( CANIF_DEV_ERROR_DETECT == 1 )
	if ( FALSE == canIfInitialized )
	{
		Det_ReportError(MODULE_ID_CANIF,0,0x17,CANIF_E_UNINIT);
	}
	else if ( chlid == UINT8_INVALID)
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
#if ( CANIF_DEV_ERROR_DETECT == 1 )
	if ( FALSE == canIfInitialized )
	{
		Det_ReportError(MODULE_ID_CANIF,0,0x13,CANIF_E_UNINIT);
	}
	else if ( canTxPduId > (canIfConfig->CanIfTxPduNum) )
	{
		Det_ReportError(MODULE_ID_CANIF,0,0x13,CANIF_E_PARAM_LPDU);
	}
	else
	{
#endif
#if ( CANIF_DEV_ERROR_DETECT == 1 )
	}
#endif
}
FUNC(void,MEM_CanIf_RxIndication) CanIf_RxIndication ( uint8 Hrh , Can_IdType CanId , uint8 CanDlc ,
		const uint8 *CanSduPtr )
{
#if ( CANIF_DEV_ERROR_DETECT == 1 )
	if ( FALSE == canIfInitialized )
	{
		Det_ReportError(MODULE_ID_CANIF,0,0x14,CANIF_E_UNINIT);
	}
	else if ( Hrh > (canIfConfig->CanIfInitHohNum) )
	{
/* TODO: This is a simple CanIf implementation,Hrh represents the ControllerID as when do configuration, each Controller
 * Just has 1 hoh<1 hrh and 1 hth> */
		Det_ReportError(MODULE_ID_CANIF,0,0x14,CANIF_E_PARAM_HRH);
	}
	else if (NULL == CanSduPtr )
	{
		Det_ReportError(MODULE_ID_CANIF,0,0x14,CANIF_E_PARAM_POINTER);
	}
	else
	{
#endif
		CanIf_ChannelGetModeType mode = canIfChannelGetPduMode[Hrh];
		if ( (mode == CANIF_GET_OFFLINE) || (mode == CANIF_GET_TX_ONLINE) ||
		     (mode == CANIF_GET_OFFLINE_ACTIVE) )
		{
			/* drop this message as not on Line */
		}
		else
		{
			const CanIf_RxPduCfgType* rxPdu = find_rxpdu(CanId,Hrh);

			if(NULL == rxPdu)
			{
#if ( CANIF_DEV_ERROR_DETECT == 1 )
				Det_ReportError(MODULE_ID_CANIF,0,0x14,CANIF_E_PARAM_CANID);
#endif
			}
			else
			{
				if(rxPdu->CanIfRxPduDlc != CanDlc)
				{
#if ( CANIF_DEV_ERROR_DETECT == 1 )
					Det_ReportError(MODULE_ID_CANIF,0,0x14,CANIF_E_PARAM_DLC);
#endif
				}
				else
				{
					switch(rxPdu->CanIfRxPduUserRxIndicationUL)
					{
						case CANIF_RXPDUUSERRXINDICATIONUL_CAN_TP:
						{
							PduInfoType pdu;
							pdu.SduDataPtr=CanSduPtr;
							pdu.SduLength=CanDlc;
							CanTp_RxIndication(rxPdu->CanIfRxPduCanId,&pdu);
							break;
						}
						default:
							assert(0);
							break;
					}
				}
			}

		}
#if ( CANIF_DEV_ERROR_DETECT == 1 )
	}
#endif
}

#ifdef __cplusplus
} /* namespace autosar */
#endif
