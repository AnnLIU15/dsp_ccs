/*
 * clock.h
 *
 *  Created on: 2021-12-27
 *      Author: Ann
 */

#ifndef CLOCK_H_
#define CLOCK_H_
#include "tsk6cfg.h"

namespace CLK_zy
{

	class Clock
	{
	public:
		Clock(LOG_Obj &newLog); // Constructor
		virtual ~Clock();
		void tick(int period);	// cnt per period

	private:
		int ticks;
		LOG_Obj *clockLog;
	};

} /* namespace CLK_zy */
#endif /* CLOCK_H_ */
