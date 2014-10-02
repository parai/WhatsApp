#include "osek_kernel.h"
#include "task.h"
#include "rtetask.h"

extern "C" {
STATIC VP tcb_sp[TASK_NUM];
STATIC FP tcb_pc[TASK_NUM];
STATIC RteTaskPool *tcb_manager;
STATIC volatile BOOL stop_task_marker;

#define SYSTEM_STACK_SZ 512
STATIC  UINT8 lc_system_stack[SYSTEM_STACK_SZ];
STATIC	TickType				OsTickCounter;
/* ================== FUNCTIONs DECLARE ========================*/
void activate_r(void);
void pre_idle(void);
void dispatch_task(void);

/* ================== FUNCTIONs  ===============================*/
TASK(OsIdle)
{
    for(;;) tcb_manager->usleep(TASKID_OsIdle,1000);
}

void disable_int(){}
void enable_int(){}

void set_ipl(IPL ipl)
{
    (void)ipl;
    if(ipl > 0)
    {
        enable_int();// disable interrupt
    }
}
IPL current_ipl(void)
{
    return 0;
}
//   activate_r:
//       When a task is scheduled and dispatched for the first time, this function is called
//      Address "activare_r" is set to the PC saving area in TCB by activate_context( ) in portable.h
//           set tinib_exepri[runtsk] to   tcb_curpri[runtsk], where runtsk is the ID of the task to be dispatched
//           enabe interrupt
//           jump to tinib_task[runtsk]
void activate_r(void)
{
    tcb_curpri[runtsk] = tinib_exepri[runtsk];
    enable_int(); // enable interrupt

    tcb_manager->start(runtsk);
}

//     pre_idle:
//        switch the stack from a task stack to the "system_stack"
//        callevel = TCL_ISR2 (type2 interrupt level)
//        fall to idle_loop
void pre_idle(void)
{
    callevel = TCL_ISR2;
    //  idle_loop:
    //     the body of the idle task
    //         enable interrupt
    //         wait  for a while  (wait for an interrupt to arrive)
    //         disable interupt
    //         if (schedtsk == INVALID)  jump back to "idle_loop"
    //         callevel = TCS_TASK
    //         jump to "start_dispatch"
    idle_loop:
    disable_int();
    if (INVALID_TASK == schedtsk)
    {
        enable_int();
        goto  idle_loop;
    }
    callevel = TCL_TASK;
    start_dispatch();
}
//    start_dispatch:
//       this function is called to dispatch schedtsk (the task that the scheduler has just selected)
//          set schedtsk to runtsk
//          if (runtsk == INVALID_TASK) jump to "pre_idle"
//          restore sp from tcxb_sp[runtsk] 
//          if  (PreTaskHook != 0) call_pretaskhook()
//          continue on to dispatch_task
void start_dispatch(void)
{
    runtsk = schedtsk;
    if (INVALID_TASK == runtsk)
    {
        pre_idle();
    }

    PreTaskHook();
    
    dispatch_task();
}

//   dispatch_task:  this is called only from start_dispatch 
//       dispatch to the locatoin saved in tcxb_pc[runtsk]
void dispatch_task(void)
{
    tcb_pc[runtsk]();
}
//    exit_and_dispatch:
//       this is called from TerminateTask() and ChainTask(), when one task relinquishes CPU
//       and another task is scheduled and dispatched
//             if (PostTaskHook != 0) PosTaskHook();
//             continue on to "start_dispatch"
void exit_and_dispatch(void)
/* void dispatcher(void)*/
{
    PostTaskHook();
    if(true == stop_task_marker)
    {
        tcb_manager->stop(runtsk);
    }
    stop_task_marker = true;    // reset it

    start_dispatch();
}

//      dispatcher_r:
//          If a task relinquishes the CPU through "dispatch",  
//          it executes this function to be dispatched when it is scheduled again.
//              restore the non-desctructive registers (PPAGE)
//              restore the value of PC (the address  to return from "dispatch") from stack
void dispatcher_r(void)
{
    tcb_manager->resume(runtsk);
}
void activate_context(TaskType TaskID)
{
    tcb_pc[TaskID] = (FP)activate_r;

    tcb_sp[TaskID] = (VP)( (UINT32)tinib_stk[TaskID] + (UINT32)tinib_stksz[TaskID]);
}
static UINT8 knl_tskind = 0; /* task independent part nested value */
void EnterISR2(void)
{
    if (INVALID_TASK != runtsk)
    {
        callevel = TCL_ISR2;
        knl_tskind++;
    }
}
void ExitISR2(void)
{
    if (INVALID_TASK != runtsk)
    {
        knl_tskind--;
        if(0U == knl_tskind)
        {
            callevel = TCL_TASK;
            if(schedtsk != runtsk)
            {
                dispatch();
            }
        }
    }
}

//   dispatch:
//      this function is called by a task
//            save the non-distructive registers (PPAGE)
//            save sp in the sp saving area in TCB
//            save "dispatcher_r" in the pc saving area in TCB
//            jump to "dispatcher
void dispatch(void)
{
    tcb_manager->suspend(runtsk);
    tcb_pc[runtsk] = (FP)dispatcher_r;

    stop_task_marker = false;
    
    exit_and_dispatch(); // jump to "dispatcher"
}

void OsTick(void)
{
    OsTickCounter ++;
    EnterISR2();
    (void)SignalCounter(0);
    ExitISR2();
}

void sys_initialize(void)
{
    tcb_manager = new RteTaskPool(TASK_NUM,tinib_task);
    stop_task_marker = true;
}
void tool_initialize(void)
{

}
void cpu_initialize(void)
{
    OsTickCounter = 0;
    lc_system_stack[0] = 0;
}
void cpu_terminate(void)
{
}
void sys_exit(void)
{
    for(;;);
}

} // extern "C"
