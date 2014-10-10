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
#ifndef CANIF_H_
#define CANIF_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Modules.h"
#include "ComStack_Types.h"
#include "Can.h"
#ifdef __cplusplus
namespace autosar { extern "C" {
#endif
/* ============================ [ MACROS    ] ====================================================== */
#define CANIF_AR_RELEASE_MAJOR_VERSION 0x00
#define CANIF_AR_RELEASE_MINOR_VERSION 0x01

#define CANIF_SW_MAJOR_VERSION				0x00
#define CANIF_SW_MINOR_VERSION  			0x01
#define CANIF_AR_RELEASE_MAJOR_VERSION		0x00
#define CANIF_AR_RELEASE_MINOR_VERSION		0x01
#define CANIF_AR_RELEASE_REVISION_VERSION	0x00

#define CANIF_E_PARAM_CANID		      		10
#define CANIF_E_PARAM_DLC			      	11
#define CANIF_E_PARAM_HRH			      	12
#define CANIF_E_PARAM_LPDU			    	13
#define CANIF_E_PARAM_CONTROLLER	  		14
#define CANIF_E_PARAM_CONTROLLERID	  		15
#define CANIF_E_PARAM_WAKEUPSOURCE			16
#define CANIF_E_PARAM_TRCV             		17
#define CANIF_E_PARAM_TRCVMODE         		18
#define CANIF_E_PARAM_TRCVWAKEUPMODE        19

#define CANIF_E_PARAM_POINTER 			  	20
#define CANIF_E_UNINIT 				        30
#define CANIF_E_NOK_NOSUPPORT			    40
#define CANIF_E_INVALID_TXPDUID		    	50
#define CANIF_E_INVALID_RXPDUID 		  	60
/* Assigned by DEM:
 * CANIF_E_INVALID_DLC
 * CANIF_E_STOPPED
 * CANIF_E_NOT_SLEEP
 */
/* ============================ [ TYPES     ] ====================================================== */
typedef enum {
	CANIF_CS_UNINIT = 0,
	CANIF_CS_SLEEP,
	CANIF_CS_STARTED,
	CANIF_CS_STOPPED
} CanIf_ControllerModeType;

typedef enum {
	CANIF_SET_OFFLINE = 0,
	CANIF_SET_ONLINE,
	CANIF_SET_RX_OFFLINE,
	CANIF_SET_RX_ONLINE,
	CANIF_SET_TX_OFFLINE,
	CANIF_SET_TX_OFFLINE_ACTIVE,
	CANIF_SET_TX_ONLINE,
} CanIf_ChannelSetModeType;

typedef enum {
	CANIF_GET_OFFLINE = 0,
	CANIF_GET_OFFLINE_ACTIVE,
	CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE,
	CANIF_GET_ONLINE,
	CANIF_GET_RX_ONLINE,
	CANIF_GET_TX_ONLINE,
} CanIf_ChannelGetModeType;

typedef enum {
	CANIF_NO_NOTIFICATION = 0,
	CANIF_TX_RX_NOTIFICATION
} CanIf_NotifStatusType;

typedef enum {
  CANIF_TRCV_MODE_NORMAL = 0,
  CANIF_TRCV_MODE_SLEEP,
  CANIF_TRCV_MODE_STANDBY
} CanIf_TransceiverModeType;

typedef enum {
	CANIF_TRCV_WU_ERROR = 0,
	CANIF_TRCV_WU_BY_BUS,
	CANIF_TRCV_WU_INTERNALLY,
	CANIF_TRCV_WU_NOT_SUPPORTED,
	CANIF_TRCV_WU_POWER_ON,
	CANIF_TRCV_WU_RESET,
} CanIf_TrcvWakeupReasonType;

typedef enum {
	CANIF_TRCV_WU_ENABLE = 0,
	CANIF_TRCV_WU_CLEAR,
	CANIF_TRCV_WU_DISABLE,
} CanIf_TrcvWakeupModeType;

typedef uint16 CanIf_ChannelIdType;

typedef struct
{
	CanIf_ChannelIdType CanIfCtrlId;
	BOOL	CanIfCtrlWakeupSupport;
	const Can_ControllerConfigType* CanIfCtrlCanCtrlIdRef;
}CanIf_ControllerConfigType;

typedef struct
{
	CanIf_ControllerConfigType *CanIfHthCanCtrlIdRef;
	Can_HwHandleType  CanIfHthIdSymRef;
	Can_HandleType CanIfHthCanHandleTypeRef;	/* this attribute is derived from CAN HwObject */
}CanIf_HthConfigType;

typedef struct
{
	CanIf_ControllerConfigType *CanIfHrhCanCtrlIdRef;
	Can_HwHandleType  CanIfHrhIdSymRef;
	Can_HandleType CanIfHrhCanHandleTypeRef;	/* this attribute is derived from CAN HwObject */
	bool CanIfHrhSoftwareFilter;
}CanIf_HrhConfigType;

typedef struct
{
  const Can_ConfigType   *CanConfig;
  const CanIf_HrhConfigType *CanIfHrhConfig;
  uint16	CanIfHrhNumber;
  const CanIf_HthConfigType *CanIfHthConfig;
  uint16	CanIfHthNumber;
} CanIf_InitHohConfigType;

typedef enum
{
    CANIF_ID_TYPE_EXTENDED,
    CANIF_ID_TYPE_STANDARD
} CanIf_IdTypeType;

typedef enum
{
	CANIF_PDU_TYPE_DYNAMIC,
	CANIF_PDU_TYPE_STATIC
}CanIf_PduTypeType;

typedef enum
{
	CANIF_TXCONFIRMATION_UL_CAN_NM,
	CANIF_TXCONFIRMATION_UL_CAN_TP,
	CANIF_TXCONFIRMATION_UL_CDD,	/* Complex Device Driver */
	CANIF_TXCONFIRMATION_UL_J1939_TP,
	CANIF_TXCONFIRMATION_UL_PDUR,
	CANIF_TXCONFIRMATION_UL_XCP
}CanIf_TxConfirmationULType;

typedef enum
{
	PDUID_PDUINFOPTR,
	PDUID_SDUDATAPTR
}CanIf_RxIndicationTypeType;

typedef enum
{
	CANIF_RXINDICATION_UL_CAN_NM,
	CANIF_RXINDICATION_UL_CAN_TP,
	CANIF_RXINDICATION_UL_CDD,	/* Complex Device Driver */
	CANIF_RXINDICATION_UL_J1939_TP,
	CANIF_RXINDICATION_UL_PDUR,
	CANIF_RXINDICATION_UL_XCP
}CanIf_RxIndicationULType;

typedef struct
{
	Can_IdType 		  CanIfTxPduCanId;
	CanIf_IdTypeType  CanIfTxPduCanIdType;
	uint8  CanIfTxPduDlc;
	PduIdType CanIfTxPduId;
	bool CanIfTxPduReadNotifyStatus;
	CanIf_PduTypeType CanIfTxPduType;
	CanIf_TxConfirmationULType CanIfTxPduUserTxConfirmationUL;
	void (*CanIfTxPduUserTxConfirmationName )(PduIdType);
	const CanIf_HthConfigType *CanIfTxPduHthIdRef;
}CanIf_TxPduConfigType;

typedef struct
{
	Can_IdType 		CanIfRxPduCanId;
	CanIf_IdTypeType  CanIfRxPduCanIdType;
	uint8  CanIfRxPduDlc ;
	PduIdType CanIfRxPduId;
	bool CanIfRxPduReadData;
	bool CanIfRxPduReadNotifyStatus;
	CanIf_PduTypeType CanIfTxPduType;
	CanIf_RxIndicationTypeType CanIfRxPduUserRxIndicationType;
	CanIf_RxIndicationULType  CanIfRxPduUserRxIndicationUL;
	void (*CanIfRxPduUserRxIndicationName )(PduIdType,const PduInfoType*/* uint8 */);
	const CanIf_HrhConfigType *CanIfRxPduHrhIdRef ;
}CanIf_RxPduConfigType;

typedef struct
{
	uint32 CanIfInitNumberOfCanRxPduIds;
	uint32 CanIfInitNumberOfDynamicCanTxPduIds;
	uint32 CanIfInitNumberOfStaticCanTXPduIds;
	CanIf_InitHohConfigType* CanIfInitHohCfg;
	CanIf_RxPduConfigType* CanIfRxPduCfg;
	CanIf_TxPduConfigType* CanIfTxPduCfg;
	CanIf_ControllerConfigType* CanIfCtrlCfg;
}CanIf_InitConfigType;

typedef struct
{
	CanIf_InitConfigType* CanIfInitConfig;
}CanIf_ConfigType;

#ifdef __cplusplus
}}  /* name space */
#endif

#include "CanIf_Cfg.h"

#ifdef __cplusplus
namespace autosar { extern "C" {
#endif
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
FUNC(void,MEM_CanIf_Init) CanIf_Init ( const CanIf_ConfigType* ConfigPtr );
FUNC(Std_ReturnType,MEM_CanIf_SetControllerMode) CanIf_SetControllerMode ( uint8 ControllerId ,
		CanIf_ControllerModeType ControllerMode );
FUNC(void,MEM_CanIf_ControllerModeIndication) CanIf_ControllerModeIndication ( uint8 Controller ,
		CanIf_ControllerModeType ControllerMode );
FUNC(void,MEM_CanIf_TxConfirmation) CanIf_TxConfirmation ( PduIdType canTxPduId );
FUNC(void,MEM_CanIf_RxIndication) CanIf_RxIndication ( uint8 Hrh , Can_IdType CanId , uint8 CanDlc ,
		const uint8 *CanSduPtr );
#ifdef __cplusplus
}}  /* name space */
#endif
#endif /* CANIF_H_ */
