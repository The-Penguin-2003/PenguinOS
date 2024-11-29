#ifndef __TIMER_H__
#define __TIMER_H__

#include <types.h>

extern volatile unsigned long g_ticks;

void init_timer();
void delay(int32_t ticks);
int32_t uptime();

#endif /* __TIMER_H__ */
