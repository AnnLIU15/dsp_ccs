/*
 * clock.cpp
 *
 *  Created on: 2021-12-27
 *      Author: Ann
 */

#include "../include/clock.h"

namespace CLK_zy
{
    Clock::Clock(LOG_Obj &newLog)
    {
        ticks = 0;                  /* cnt */
        clockLog = &newLog;         /* ptr_log */
    }

    Clock::~Clock()
    {
    }

    void Clock::tick(int period)
    {
        LOG_printf(clockLog, "CNT TIME: %d(Period=%d)", ticks++, period);
        return;
    }

} /* namespace CLK_zy */
