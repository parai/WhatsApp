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
STATIC uint8 ResourceBit[(RES_NUMBER+7)/8];
/* ============================ [ DECLARES ] ====================================================== */
/* ============================ [ LOCALS   ] ====================================================== */

STATIC FUNC(void,MEM_RES_SETBIT) SetBit ( ResourceType ResID )
{
    uint8 x;
    uint8 y;
    y = ResID>>3;
    x = ResID&7;

    ResourceBit[y] |= 1<<x;
}

STATIC FUNC(void,MEM_RES_CLEARBIT) ClearBit ( ResourceType ResID )
{
    uint8 x;
    uint8 y;
    y = ResID>>3;
    x = ResID&7;

    ResourceBit[y] &= ~(1<<x);
}

STATIC FUNC(bool,MEM_RES_ISBITSET) IsBitSet ( ResourceType ResID)
{
    bool isBitSet = FALSE;
    uint8 y = ResID>>3;
    uint8 x = ResID&7;

    if( ResourceBit[y] & (1<<x) )
    {
        isBitSet = TRUE;
    }
    return isBitSet;
}

/* ============================ [ FNCTIONS ] ====================================================== */
/*! \fn StatusType GetResource ( ResourceType ResID )
 *  \brief Get a shared critical resource which will be used by several tasks
 *          As this is a implementation of Non-Preemtable OSEK OS BCC1, so treate the Resource
 *  as mutex.
 *  \param ResID Identifier to the critical resource
 *  \return the status of GetResource:
 *              E_OK: get ResID successfully
 *              E_OS_ACCESS: get ResID failed
 */
FUNC(StatusType,MEM_GetResource) GetResource ( ResourceType ResID )
{
    StatusType ercd = E_OK;

    if (ResID < RES_NUMBER)
    {
        if (IsBitSet(ResID))
        {
            ercd = E_OS_ACCESS;
        }
        else
        {
            SetBit(ResID);
        }
    }
    else
    {
        ercd = E_OS_ID;
    }

    return ercd;
}

FUNC(StatusType,MEM_ReleaseResource) ReleaseResource ( ResourceType ResID )
{
    StatusType ercd = E_OK;
    if (ResID < RES_NUMBER)
    {
        if (IsBitSet(ResID))
        {
            ClearBit(ResID);
        }
        else
        {
            ercd = E_OS_ACCESS;
        }
    }
    else
    {
        ercd = E_OS_ID;
    }
    return ercd;
}

FUNC(void,MEM_OsResourceInit) OsResourceInit ( void )
{
    memset(ResourceBit,0,sizeof(ResourceBit));
}
