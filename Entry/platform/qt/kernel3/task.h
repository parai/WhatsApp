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
#ifndef TASK_H_
#define TASK_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include <QThread>
#include <QDebug>
#include <assert.h>
#include "Os.h"

#ifdef __cplusplus
namespace autosar {
#endif
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ CLASS     ] ====================================================== */
class arTask : public QThread
{
    Q_OBJECT
private:
    TaskType task_id;
    const task_declare_t* declare;
    uint8  activation;
    EventMaskType setEvent;
public:
    explicit arTask(TaskType task_id,const task_declare_t* declare,QObject *parent = 0);

    bool Activate   (void);
    bool WaitEvent  (EventMaskType eventMask);
    bool ClearEvent (void);
    bool SetEvent   (EventMaskType eventMask);
    EventMaskType GetEvent(void) { return setEvent;}

    void run();
};
/* ============================ [ DATAS     ] ====================================================== */
extern "C" QList<arTask*> task_context;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifdef __cplusplus
}  /* name space */
#endif
#endif /* TASK_H_ */
