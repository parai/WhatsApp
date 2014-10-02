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
#include "rtetask.h"

RteTask::RteTask(TaskType task_id,void (*task_pc)(void),QObject *parent) :
    QThread(parent)
{
    this->task_id = task_id;
    this->task_pc = task_pc;
}

void RteTask::run()
{
    task_pc();
}


RteTaskPool::RteTaskPool(unsigned long task_num,void (* const pc[])(void))
{
    this->task_num = task_num;
    for(unsigned long i=0;i<task_num;i++)
    {
        task_context.push_back( new RteTask(i,pc[i]) );
    }
}
RteTaskPool::~RteTaskPool()
{
    qDebug() << "~RteTaskPool()";
    while (!task_context.isEmpty())
    {
        delete task_context.at(task_context.size() - 1);
        task_context.removeLast();
    }
}

void RteTaskPool::start(unsigned long task_id)
{
    qDebug() << "start task " << task_id;
    assert(task_id<task_num);
    task_context[task_id]->start(QThread::HighestPriority);
}

void RteTaskPool::stop(unsigned long task_id)
{
    assert(task_id<task_num);
    qDebug() << "stop task " << task_id;
    task_context[task_id]->exit(0);
}

void RteTaskPool::suspend(unsigned long task_id)
{
    assert(task_id<task_num);
    qDebug() << "suspend task " << task_id;
    // TODO: this is NG
    task_context[task_id]->setPriority(QThread::IdlePriority);
}

void RteTaskPool::resume(unsigned long task_id)
{
    assert(task_id<task_num);
    qDebug() << "resume task " << task_id;
    // TODO: this is NG
    task_context[task_id]->setPriority(QThread::HighestPriority);

}

void RteTaskPool::usleep(unsigned long task_id,unsigned long us)
{
    assert(task_id<task_num);
    task_context[task_id]->usleep(us);
}
