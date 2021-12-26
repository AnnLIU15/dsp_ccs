#include <std.h>
#include <hst.h>
#include <swi.h>
#include <tsk.h>
#include <log.h>
#include <sts.h>

#ifdef __cplusplus
extern "C" {
#endif

extern far HST_Obj RTA_fromHost;
extern far HST_Obj RTA_toHost;
extern far SWI_Obj KNL_swi;
extern far TSK_Obj TSK_idle;
extern far TSK_Obj task0;
extern far TSK_Obj task1;
extern far TSK_Obj task2;
extern far TSK_Obj task3;
extern far TSK_Obj task4;
extern far LOG_Obj LOG_system;
extern far LOG_Obj trace;
extern far STS_Obj IDL_busyObj;


#ifdef __cplusplus
}
#endif /* extern "C" */
