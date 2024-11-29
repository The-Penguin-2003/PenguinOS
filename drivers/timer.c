/* PenguinOS Programmable Interval Timer Driver */
#include <irqs.h>
#include <timer.h>

volatile unsigned long g_ticks = 0;

void timer_handler() {
    g_ticks++;
}

void init_timer() {
    irq_install_handler(0, timer_handler);
}

void delay(int32_t ticks) {
    unsigned long eticks;
    eticks = g_ticks + ticks;

    while (g_ticks < eticks);
}

int32_t uptime() {
    return g_ticks;
}
