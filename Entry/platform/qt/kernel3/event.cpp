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
#include "task.h"
namespace autosar {
extern "C" {
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ CLASS     ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
StatusType SetEvent(TaskType TaskID, EventMaskType mask)
{
	StatusType ercd = E_OK;
	if(TaskID < TASK_NUM)
	{
		task_context[TaskID]->SetEvent(mask);
	}
	else
	{
		ercd = E_OS_ID;
	}
	return ercd;
}
StatusType GetEvent(TaskType TaskID, EventMaskRefType p_mask)
{
	StatusType ercd = E_OK;
	if(TaskID < TASK_NUM)
	{
		*p_mask = task_context[TaskID]->GetEvent();
	}
	else
	{
		ercd = E_OS_ID;
	}
	return ercd;
}
StatusType ClearEvent(TaskType TaskID,EventMaskType mask)
{
	StatusType ercd = E_OK;
	if(TaskID < TASK_NUM)
	{
		task_context[TaskID]->ClearEvent();
	}
	else
	{
		ercd = E_OS_ID;
	}
	return ercd;
}
StatusType WaitEvent (TaskType TaskID,EventMaskType mask)
{
	StatusType ercd = E_OK;
	if(TaskID < TASK_NUM)
	{
		task_context[TaskID]->WaitEvent(mask);
	}
	else
	{
		ercd = E_OS_ID;
	}
	return ercd;
}
}} /* namespace autosar */
