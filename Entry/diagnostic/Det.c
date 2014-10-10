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
#include "Det.h"
#ifdef __cplusplus
namespace autosar {
#endif

/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
STATIC boolean detStarted;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
FUNC(void,MEM_Det_Init) Det_Init ( void )
{
	detStarted = FALSE;
}
FUNC(Std_ReturnType,MEM_Det_ReportError) Det_ReportError ( uint16 ModuleId , uint8 InstanceId , uint8 ApiId ,
		uint8 ErrorId )
{
	if ( detStarted )
	{
		fprintf(stderr,"ModuleId=%3d,InstanceId=%2d,ApiId=0x%0-2x,ErrorId=%2d\n",ModuleId,InstanceId,ApiId,ErrorId);
		fflush(stderr);
	}
	else
	{

	}
	return E_OK;
}
FUNC(void,MEM_Det_Start) Det_Start ( void )
{
	detStarted = TRUE;
}

#ifdef __cplusplus
} /* namespace autosar */
#endif
