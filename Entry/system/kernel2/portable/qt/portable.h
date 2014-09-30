#ifndef CPU_CONTEX_H_H
#define CPU_CONTEX_H_H

extern void disable_int();
extern void enable_int();

extern void dispatch();

extern void set_ipl(IPL ipl);
extern IPL current_ipl(void);
extern void start_dispatch(void);
extern void exit_and_dispatch(void);
extern void activate_context(TaskType TaskID);

extern void EnterISR2(void);
extern void ExitISR2(void);

#endif
