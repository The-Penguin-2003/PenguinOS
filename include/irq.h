#ifndef __IRQ_H__
#define __IRQ_H__

#include <types.h>
#include <isrs.h>

void init_irq();
void irq_install_handler(int32_t irq, void (*handler)(struct regs* r));
void irq_uninstall_handler(int32_t irq);

#endif /* __IRQ_H__ */
