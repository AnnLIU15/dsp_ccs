#include <std.h>
#include <log.h>
#include <sem.h>
#include <tsk.h>
#include <swi.h>
#include <stdlib.h>
#include <time.h>
#include "../include/tsk6cfg.h"
#include "../include/clock.h"

/* extern "C" */
extern "C"									/* 以c形式声明函数 */
{
	void genChar();							/* 随机生成英文字符，大小写敏感 */
	void displayChar();						/* print出来字符 */
	void clockPrd(CLK_zy::Clock clock);		/* 1s 的计数器 */
}

//#define test_swi							/* 测试软件中断 */
//#define display_gen							/* 测试生成与打印是否相同 */
#ifdef test_swi
CLK_zy::Clock cl0(trace); 					/* periodic clock, period = 1 ms */
#define DEBUG_DELAY 40000
//unsigned char have_printed = 0;
//unsigned char have_generated = 0;
#else
CLK_zy::Clock cl0(prdLog0); /* periodic clock, period = 1 ms */
#endif

char randChar;

int main(void)
{
	srand((unsigned)time(NULL));			/* 理论上为真随机 */
	LOG_printf(&trace, "Task6 started.");
#ifndef test_swi
	prdClock0.period = 1000;				/* 默认为1ms */
#endif
	LOG_printf(&trace, "Cnt Period %dms", prdClock0.period);
	return 0;
}

void genChar()
{
#ifdef test_swi
	long i = 0;
#endif
	for (;;)
	{
		SEM_pendBinary(&sem0, SYS_FOREVER);	/* 永远需要等待sem0信号到来，除非被中断 */
#ifdef test_swi
//		if (have_generated == 0)
//		{
			randChar = rand() % 26 + 65 + ((rand() % 2) << 5);
			LOG_printf(&trace, "Generate: %c.", randChar, have_printed = 0, have_generated = 1);
//		}

		for (i = 0; i < DEBUG_DELAY; i++)
		{
			;
		}
		LOG_printf(&trace, "Go To displayChar");
#else
		randChar = rand() % 26 + 65 + ((rand() % 2) << 5);	/* 按ASCII码生成char */
#ifdef display_gen
		LOG_printf(&trace, "Generate: %c", randChar);
#endif
#endif
		SEM_postBinary(&sem1);				/* 发射sem1信号 */
	}
}

void displayChar()
{
#ifdef test_swi
	long i = 0;
#endif
	for (;;)
	{
		SEM_pendBinary(&sem1, SYS_FOREVER);	/* 永远需要等待sem1信号到来，除非被中断 */
#ifdef test_swi
//		if (have_printed == 0)
//		{
			LOG_printf(&trace, "Print char %c.", randChar, have_printed = 1, have_generated = 0);
//		}
		for (i = 0; i < DEBUG_DELAY; i++)
		{
			;
		}
		LOG_printf(&trace, "Go To genChar");
#else
		LOG_printf(&trace, "Print char %c", randChar);	/* 打印 */
#endif

		SEM_postBinary(&sem0);				/* 发射sem0信号 */
	}
}

void clockPrd(CLK_zy::Clock cnt_clock)
{
	cnt_clock.tick(prdClock0.period);		/* cnt */
	return;
}
