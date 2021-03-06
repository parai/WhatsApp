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
#ifndef CANTP_H_
#define CANTP_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Modules.h"
#include "ComStack_Types.h"
#include "CanIf.h"

#ifdef __cplusplus
namespace autosar { extern "C" {
#endif
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* If an RxNsdu or a TxNsdu is configured for mixed addressing format, this
 * parameter contains the transport protocol address extension value
 */
typedef uint8 CanTp_NAeType;
/* If an RxNSdu or a TxNSdu is configured for extended addressing format,
 * this parameter contains the transport protocol source address's value.
 */
typedef uint8 CanTp_NSaType;
/* If an RxNsdu or a TxNsdu is configured for extended addressing format,
 * this parameter contains the transport protocol target address's value
 */
typedef uint8 CanTp_NTaType;
#ifdef __cplusplus
}}  /* name space */
#endif

#include "CanTp_Types.h"
#include "CanTp_Cfg.h"

#ifdef __cplusplus
namespace autosar { extern "C" {
#endif
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
FUNC(void,MEM_CanTp_RxIndication) CanTp_RxIndication(PduIdType CanTpRxPduId, const PduInfoType *CanTpRxPduPtr);
#ifdef __cplusplus
}}  /* name space */
#endif
#endif /* CANTP_H_ */
