#ifndef __IDT_H__
#define __IDT_H__

#include <types.h>

struct idt_entry {
    uint16_t base_low;
    uint16_t sel;
    uint8_t zero;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void idt_set_gate(uint8_t num, unsigned long base, uint16_t sel, uint8_t flags);
void init_idt();

#endif /* __IDT_H__ */
