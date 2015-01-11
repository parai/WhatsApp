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
#ifndef CANTP_CFG_H_
#define CANTP_CFG_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"

#ifdef __cplusplus
namespace autosar { extern "C" {
#endif
/* ============================ [ MACROS    ] ====================================================== */
enum
{
	CANTP_CHL_P2P,
	CANTP_CHL_P2A,
	CANTP_CHL_NUM
};
enum
{
	CANTP_TX_P2P,
	CANTP_TX_P2A,
	CANTP_TX_NUM
};
enum
{
	CANTP_RX_P2P,
	CANTP_RX_P2A,
	CANTP_RX_NUM
};
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __cplusplus
}}  /* name space */
#endif
#endif /* CANTP_CFG_H_ */
