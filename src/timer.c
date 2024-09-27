#include <timer.h>
#include <irq.h>
#include <kprintf.h>

volatile unsigned long g_ticks = 0;

void timer_handler()
{
	g_ticks++;
}

void init_timer()
{
	irq_install_handler(0, timer_handler);
	kprintf("[KERNEL] Timer Initialized -> Starting g_ticks...\r\n");
}

void timer_delay(int32_t ticks)
{
	unsigned long e_ticks;
	e_ticks = g_ticks + ticks;

	while (g_ticks < e_ticks);
}

int32_t uptime()
{
	return g_ticks;
}
