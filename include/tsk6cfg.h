/*
 * tsk6cfg.h
 *
 *  Created on: 2021-12-27
 *      Author: Ann
 */

#ifndef TSK6CFG_H_
#define TSK6CFG_H_

#include <std.h>
#include <prd.h>
#include <hst.h>
#include <swi.h>
#include <tsk.h>
#include <log.h>
#include <sem.h>
#include <sts.h>

#ifdef __cplusplus
extern "C"
{
#endif

    extern far PRD_Obj prdClock0;
    extern far HST_Obj RTA_fromHost;
    extern far HST_Obj RTA_toHost;
    extern far SWI_Obj PRD_swi;
    extern far SWI_Obj KNL_swi;
    extern far TSK_Obj TSK0;
    extern far TSK_Obj TSK1;
    extern far LOG_Obj LOG_system;
    extern far LOG_Obj trace;
    extern far LOG_Obj prdLog0;
    extern far SEM_Obj sem0;
    extern far SEM_Obj sem1;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* TSK6CFG_H_ */
