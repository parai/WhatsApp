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
/* ============================ [ FNCTIONS ] ====================================================== */
/*! \fn StatusType GetResource ( ResourceType ResID )
 *  \brief Get a shared critical resource which will be used by several tasks
 *          As this is a implementation of Non-Preemtable OSEK OS BCC1, so treate the Resource
 *  as mutex. Infact, it is just a mark, if the mark is set, that is to say that the resource
 * is occupied by other task.
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
        if (IsBitopSet(ResourceBit,(uint32)ResID))
        {
            ercd = E_OS_ACCESS;
        }
        else
        {
            BitopSet(ResourceBit,(uint32)ResID);
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
        if (IsBitopSet(ResourceBit,(uint32)ResID))
        {
            BitopClear(ResourceBit,(uint32)ResID);
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
