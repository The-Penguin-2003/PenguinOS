#ifndef __TIMER_H__
#define __TIMER_H__

#include <types.h>

void init_timer();
void timer_delay(int32_t ticks);
int32_t uptime();

#endif /* __TIMER_H__ */
