#ifndef __IRQS_H__
#define __IRQS_H__

#include <types.h>
#include <isrs.h>

void init_irqs();
void irq_install_handler(int32_t irq, void (*handler)(struct regs* r));
void irq_uninstall_handler(int32_t irq);

#endif /* __IRQS_H__ */
