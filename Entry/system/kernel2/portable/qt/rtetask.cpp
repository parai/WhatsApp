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
    for(int i=0;i<task_num;i++)
    {
        task_context[i] = new RteTask(i,pc[i]);
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
