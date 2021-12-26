#include <std.h>

#include <log.h>
#include <tsk.h>
#include <stdlib.h>
#include <time.h>
#include "tskcfg.h"

#define N 5                     /* 哲学家数目 */
#define LEFT (idx + N - 1) % N  /* 哲学家i的左筷子编号 */
#define RIGHT idx % N           /* 哲学家i的右筷子编号 */
#define THINKING 0              /* 哲学家在思考 */
#define HUNGRY 1                /* 哲学家试图拿起筷子 */
#define EATING 2                /* 哲学家吃饭 */

typedef int semaphore;          /* 信号量 */
int state[N];                   /* 记录每位哲学家状态的数组 */
int times_eat[N];               /* 记录每位哲学家吃了几次 */
semaphore s[N];                 /* 筷子状态量 */

Void philosopher(Arg id_arg);   /* Function for tasks created with Config Tool */

Void main()
{
    /* 初始化 */
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
    Int idx = ArgToInt(id_arg); /* 获取任务id */
    Int wait_time;              /* 等待时间 */
    LOG_printf(&trace, "Philosopher %d came into the house.", idx);
    for (;;)
    {
        if (state[idx] == THINKING)
        {
            state[idx] = HUNGRY;
            wait_time = rand() % 5 + 1;     /* 初始思考时间 */
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
                TSK_sleep(5);       /* 吃饭需要一点时间 */
            }
            else
            {
                TSK_yield();        /* 一直观测筷子 */
            }
        }
        else if (state[idx] == EATING)
        {
            LOG_printf(&trace, "Philosopher %d release the left chopstick", idx);
            s[LEFT] = 1;
            TSK_sleep(1);       /* 放筷子需要一点小时间 */
            LOG_printf(&trace, "Philosopher %d release the right chopstick", idx);
            s[RIGHT] = 1;
            state[idx] = THINKING;
            times_eat[idx] += 1;
            //TSK_sleep(30);    /* 等等又饿了 */
            TSK_exit();         /* 假设他们不贪吃 */
        }
    }
}
