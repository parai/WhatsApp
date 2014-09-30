#include "os_cfg.h"
#include "osek_kernel.h"
/* ============================= TASK =================================================== */
/*
 *  os_cfg.c, static configured information for tasks
 */
const UINT8	tnum_task    = TASK_NUM;
const UINT8	tnum_exttask = TASK_NUM;
	
const Priority	tinib_inipri[] =
{ 
    2, /* SchM_BswService */ 
    1, /* SchM_Startup */ 
    0  /* OsIdle */ 
};
const Priority	tinib_exepri[] = 
{
    2, /* SchM_BswService */ 
    1, /* SchM_Startup */ 
    0  /* OsIdle */ 
};
const UINT8		tinib_maxact[]=
{
    1, /* SchM_BswService */ 
    1, /* SchM_Startup */ 
    1  /* OsIdle */  
};
const AppModeType tinib_autoact[]=
{
    0xFFFFFFFF, 		/* SchM_BswService */ 
    0xFFFFFFFF, 		/* SchM_Startup */ 
    0xFFFFFFFF    		/* OsIdle */ 
};
const FP			tinib_task[]=
{
    TASKNAME(SchM_BswService),
    TASKNAME(SchM_Startup),
    TASKNAME(OsIdle)
};


static UINT8  SchM_BswService_stk[512];
static UINT8  SchM_Startup_stk[512];
static UINT8  OsIdle_stk[512];
const VP			tinib_stk[]=
{
    SchM_BswService_stk,
    SchM_Startup_stk,
    OsIdle_stk
};

const UINT16		tinib_stksz[]=
{
    512,
    512,
    512
};
const IPL		ipl_maxisr2 = 1;
/*
 *  os_cfg.c
 *
 *  used to manage tasks < tasks queue, state, proority, activate count >
 */
TaskType	    tcb_next[TASK_NUM];			/* task linker,indicate the next task in the queue */
UINT8			tcb_tstat[TASK_NUM];		/* task state */
Priority		tcb_curpri[TASK_NUM];		/* task current priority */
UINT8			tcb_actcnt[TASK_NUM];		/* task current activate count */
EventMaskType	tcb_curevt[TASK_NUM];		/* task current event has been set */
EventMaskType	tcb_waievt[TASK_NUM];		/* task wait event */
ResourceType	tcb_lastres[TASK_NUM];		/* task acquired resource recently */

/* ================================= ALARM COUNTER ======================================= */
/*
 *  number of ALARM and Counter
 */
const UINT8		tnum_counter = COUNTER_NUM;		/* Counter number configured */
const UINT8		tnum_alarm = ALARM_NUM;			/* Alarm number configured */

/*
 *  configured information for counter
 */
const TickType	cntinib_maxval[COUNTER_NUM] =
{
    65535
};
const TickType	cntinib_maxval2[COUNTER_NUM] =
{
    65535*2+1
};
const TickType	cntinib_tickbase[COUNTER_NUM] =
{
    1
};
const TickType	cntinib_mincyc[COUNTER_NUM] = 
{
    50
};

/*
 *  counter control block
 */
TickType			cntcb_curval[COUNTER_NUM];		/* counter current value*/
AlarmType		    cntcb_almque[COUNTER_NUM];		/* counter queue */

/*
 *  configured information for alarm
 */
const CounterType alminib_cntid[ALARM_NUM] =
{
    ID_OS_TICK   /* SchM_BswService */ 
};
const FP			 alminib_cback[ALARM_NUM] =
{
    ALARMCALLBACKNAME(SchM_BswService)
    
};	/* alarm call back routine */
const AppModeType alminib_autosta[ALARM_NUM] =
{
    0xFFFFFFFF, /* SchM_BswService */ 
};	/* alarm autostart mode */

const TickType	 alminib_almval[ALARM_NUM] =
{
    10 /* SchM_BswService */ 
};
const TickType	 alminib_cycle[ALARM_NUM] = 
{
    5, /* SchM_BswService */ 
};

/*
 *  alarm control block
 */
AlarmType		almcb_next[ALARM_NUM];		/* next alarm in queue */
AlarmType		almcb_prev[ALARM_NUM];		/* previous alarm in queue */
TickType		almcb_almval[ALARM_NUM];		/* expire time */
TickType		almcb_cycle[ALARM_NUM];		/* alarm cycle time */

/* ======================= RESOURCE =========================================== */
const UINT8		tnum_resource = RES_NUM;

const Priority	resinib_ceilpri[RES_NUM] =
{
    14,
    8
};	

/*
 *  resource control block
 *
 */
Priority			rescb_prevpri[RES_NUM];	/* previous priority of task which has acquired this res */
ResourceType		rescb_prevres[RES_NUM];

/* ============= ISR resource ============= */
const UINT8		tnum_isr2 = 0;


const Priority	isrinib_intpri[] =
{
    0
};

ResourceType		isrcb_lastres[1];


extern void	task_initialize(void);
extern void alarm_initialize(void);
extern void resource_initialize(void);
void object_initialize(void)
{
    task_initialize();
    alarm_initialize();
    resource_initialize();
}