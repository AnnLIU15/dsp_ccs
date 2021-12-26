#include <std.h>

#include <log.h>
#include <tsk.h>
#include <stdlib.h>
#include <time.h>
#include "tskcfg.h"

#define N 5                     /* ��ѧ����Ŀ */
#define LEFT (idx + N - 1) % N  /* ��ѧ��i������ӱ�� */
#define RIGHT idx % N           /* ��ѧ��i���ҿ��ӱ�� */
#define THINKING 0              /* ��ѧ����˼�� */
#define HUNGRY 1                /* ��ѧ����ͼ������� */
#define EATING 2                /* ��ѧ�ҳԷ� */

typedef int semaphore;          /* �ź��� */
int state[N];                   /* ��¼ÿλ��ѧ��״̬������ */
int times_eat[N];               /* ��¼ÿλ��ѧ�ҳ��˼��� */
semaphore s[N];                 /* ����״̬�� */

Void philosopher(Arg id_arg);   /* Function for tasks created with Config Tool */

Void main()
{
    /* ��ʼ�� */
    int i = 4;
    srand((unsigned)time(NULL));
    for (; i >= 0; --i)
    {
        s[i] = 1;
        times_eat[i] = 0;
        state[i] = THINKING;
    }
    LOG_printf(&trace, "Philosopher Dinner");
    return;
}
/*
 *  ======== task ========
 */
Void philosopher(Arg id_arg)
{
    Int idx = ArgToInt(id_arg); /* ��ȡ����id */
    Int wait_time;              /* �ȴ�ʱ�� */
    LOG_printf(&trace, "Philosopher %d came into the house.", idx);
    for (;;)
    {
        if (state[idx] == THINKING)
        {
            state[idx] = HUNGRY;
            wait_time = rand() % 5 + 1;     /* ��ʼ˼��ʱ�� */
            LOG_printf(&trace, "Philosopher %d Thinking(%ds)", idx, wait_time);
            TSK_sleep(wait_time);
        }
        else if (state[idx] == HUNGRY)
        {
            if (s[LEFT] == 1 && s[RIGHT] == 1 &&
                times_eat[LEFT] >= times_eat[idx] && times_eat[RIGHT] >= times_eat[idx])
            {
                state[idx] = EATING;
                s[LEFT] = 0;
                s[RIGHT] = 0;
                LOG_printf(&trace, "Philosopher %d Eating(%d times)", idx, s[idx]);
                TSK_sleep(5);       /* �Է���Ҫһ��ʱ�� */
            }
            else
            {
                TSK_yield();        /* һֱ�۲���� */
            }
        }
        else if (state[idx] == EATING)
        {
            LOG_printf(&trace, "Philosopher %d release the left chopstick", idx);
            s[LEFT] = 1;
            TSK_sleep(1);       /* �ſ�����Ҫһ��Сʱ�� */
            LOG_printf(&trace, "Philosopher %d release the right chopstick", idx);
            s[RIGHT] = 1;
            state[idx] = THINKING;
            times_eat[idx] += 1;
            //TSK_sleep(30);    /* �ȵ��ֶ��� */
            TSK_exit();         /* �������ǲ�̰�� */
        }
    }
}
