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
#ifndef RTETASK_H
#define RTETASK_H

#include <QRunnable>
#include <QThreadPool>
#include <QThread>
#include <QDebug>
#include <QList>
#include <assert.h>
#include "Os.h"
using namespace autosar;



class RteTask : public QThread
{
    Q_OBJECT
private:
    TaskType task_id;
    void (*task_pc)(void);
public:
    explicit RteTask(TaskType task_id,void (*task_pc)(void),QObject *parent = 0);

    void run();
};

class RteTaskPool
{
private:
    unsigned long task_num;
    QList<RteTask*> task_context;
public:
    explicit RteTaskPool(unsigned long task_num,void (* const pc[])(void));
    ~RteTaskPool();
    void start(unsigned long task_id);
    void stop(unsigned long task_id);

    void suspend(unsigned long task_id);
    void resume(unsigned long task_id);

    void usleep(unsigned long task_id,unsigned long us);
};

#endif // RTETASK_H
