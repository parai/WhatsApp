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
/* ============================ [ INCLUDES ] ====================================================== */
#include "Os.h"

/* ============================ [ MACROS   ] ====================================================== */
/* ============================ [ TYPES    ] ====================================================== */
/* ============================ [ DATAS    ] ====================================================== */
/* ============================ [ DECLARES ] ====================================================== */
/* ============================ [ LOCALS   ] ====================================================== */
/* ============================ [ FNCTIONS ] ====================================================== */

FUNC(void,MEM_BITOP_SET) BitopSet ( uint8* pBuffer, uint32 Position )
{
    uint8   x;
    uint32  y;
    y = Position>>3;
    x = Position&7;

    pBuffer[y] |= 1<<x;
}

FUNC(void,MEM_BITOP_CLEAR) BitopClear ( uint8* pBuffer, uint32 Position )
{
    uint8   x;
    uint32  y;
    y = Position>>3;
    x = Position&7;

    pBuffer[y] &= ~(1<<x);
}

FUNC(bool,MEM_BITOP_ISBITSET) IsBitopSet ( uint8* pBuffer, uint32 Position )
{
    bool isBitSet;
    uint8   x;
    uint32  y;

    isBitSet = FALSE;
    y = Position>>3;
    x = Position&7;

    if( pBuffer[y] & (1<<x) )
    {
        isBitSet = TRUE;
    }
    return isBitSet;
}
