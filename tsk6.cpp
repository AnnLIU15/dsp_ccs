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
extern "C"									/* ��c��ʽ�������� */
{
	void genChar();							/* �������Ӣ���ַ�����Сд���� */
	void displayChar();						/* print�����ַ� */
	void clockPrd(CLK_zy::Clock clock);		/* 1s �ļ����� */
}

//#define test_swi							/* ��������ж� */
//#define display_gen							/* �����������ӡ�Ƿ���ͬ */
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
	srand((unsigned)time(NULL));			/* ������Ϊ����� */
	LOG_printf(&trace, "Task6 started.");
#ifndef test_swi
	prdClock0.period = 1000;				/* Ĭ��Ϊ1ms */
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
		SEM_pendBinary(&sem0, SYS_FOREVER);	/* ��Զ��Ҫ�ȴ�sem0�źŵ��������Ǳ��ж� */
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
		randChar = rand() % 26 + 65 + ((rand() % 2) << 5);	/* ��ASCII������char */
#ifdef display_gen
		LOG_printf(&trace, "Generate: %c", randChar);
#endif
#endif
		SEM_postBinary(&sem1);				/* ����sem1�ź� */
	}
}

void displayChar()
{
#ifdef test_swi
	long i = 0;
#endif
	for (;;)
	{
		SEM_pendBinary(&sem1, SYS_FOREVER);	/* ��Զ��Ҫ�ȴ�sem1�źŵ��������Ǳ��ж� */
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
		LOG_printf(&trace, "Print char %c", randChar);	/* ��ӡ */
#endif

		SEM_postBinary(&sem0);				/* ����sem0�ź� */
	}
}

void clockPrd(CLK_zy::Clock cnt_clock)
{
	cnt_clock.tick(prdClock0.period);		/* cnt */
	return;
}
