#ifndef OS_CONFIG_H_H
#define OS_CONFIG_H_H
#ifdef __cplusplus
namespace autosar {
extern "C" {
#endif
/* ============================ [ INCLUDES ] ====================================================== */
#include "osek_kernel.h"

/* ============================ [ MACROS   ] ====================================================== */
#define TASKID_OsIdle 						0
#define TASKID_SchM_Startup 				1
#define TASKID_SchM_BswService 				2
#define TASK_NUM               			    3

#define ALARMID_SchM_BswService         0
#define ALARM_NUM						1

#define ID_OS_TICK						0
#define COUNTER_NUM    					1

#define RES_CAN                 (RES_SCHEDULER + 1)
#define RES_NUM                 (RES_SCHEDULER + 2)

//#define BASIC_STATUS

/* ============================ [ TYPES    ] ====================================================== */
/* ============================ [ DATAS    ] ====================================================== */
/* ============================ [ LOCALS   ] ====================================================== */
/* ============================ [ FNCTIONS ] ====================================================== */
extern TASK(OsIdle);
extern TASK(SchM_Startup);
extern TASK(SchM_BswService);

extern ALARMCALLBACK(SchM_BswService);
#ifdef __cplusplus
}}  // name space
#endif
#endif  /* OS_CONFIG_H_H */
