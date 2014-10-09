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

#ifndef COMSTACK_TYPES_H_
#define COMSTACK_TYPES_H_


/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
#ifdef __cplusplus
namespace autosar { extern "C" {
#endif
/* ============================ [ MACROS    ] ====================================================== */
/* version 00.01#00 */
#define COMSTACKTYPE_MAJOR_VERSION		0
#define COMSTACKTYPE_MINOR_VERSION		1
#define COMSTACKTYPE_PATCH_VERSION		0

#define BUSTRCV_NO_ERROR	0x00
#define BUSBUSTRCV_E_ERROR	0x01

/* ============================ [ TYPES     ] ====================================================== */
/* Zero-based integer number
 * The size of this global type depends on the maximum
 * number of PDUs used within one software module.
 * Example :
 * If  no software module deals with more PDUs that
 * 256, this type can be set to uint8.
 * If at least one software module handles more than
 * 256 PDUs, this type must globally be set to uint16.
 * In order to be able to perform table-indexing within a software
 * module, variables of this type shall be zero-based and consecutive.
 * There might be several ranges of PduIds in a module, one for each type of
 * operation performed within that module (e.g. sending and receiving).
*/

typedef uint16 PduIdType;
typedef uint16 PduLengthType;
typedef struct {
    uint8 *SduDataPtr;
    PduLengthType SduLength;
} PduInfoType;

typedef enum {
    TP_DATACONF,
    TP_DATARETRY,
    TP_CONFPENDING,
    TP_NORETRY,
} TpDataStateType;

typedef struct {
    TpDataStateType TpDataState;
    PduLengthType TxTpDataCnt;
} RetryInfoType;

typedef enum {
    BUFREQ_OK=0,
    BUFREQ_NOT_OK,
    BUFREQ_BUSY,
    BUFREQ_OVFL
} BufReq_ReturnType;

typedef uint8 BusTrcvErrorType;

typedef uint8 NetworkHandleType;
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */


#ifdef __cplusplus
}}
#endif
#endif /*COMSTACK_TYPES_H_*/
