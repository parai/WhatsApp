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
#ifndef DET_H_
#define DET_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
#include "Modules.h"

#ifdef __cplusplus
namespace autosar { extern "C" {
#endif
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
FUNC(void,MEM_Det_Init)  Det_Init ( void );
FUNC(Std_ReturnType,MEM_Det_ReportError) Det_ReportError ( uint16 ModuleId , uint8 InstanceId , uint8 ApiId , uint8 ErrorId );
FUNC(void,MEM_Det_Start) Det_Start ( void );
#ifdef __cplusplus
}}  /* name space */
#endif
#endif /* DET_H_ */
