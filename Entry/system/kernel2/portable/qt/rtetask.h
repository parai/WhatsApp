#ifndef RTETASK_H
#define RTETASK_H

#include <QRunnable>
#include <QThreadPool>
#include <QThread>
#include <QDebug>
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
    RteTask* task_context[1024];
public:
    explicit RteTaskPool(unsigned long task_num,void (* const pc[])(void));
    void start(unsigned long task_id);
    void stop(unsigned long task_id);

    void suspend(unsigned long task_id);
    void resume(unsigned long task_id);

    void usleep(unsigned long task_id,unsigned long us);
};

#endif // RTETASK_H
