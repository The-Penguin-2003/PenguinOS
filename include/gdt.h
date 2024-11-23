#ifndef __GDT_H__
#define __GDT_H__

#include <types.h>

struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void gdt_set_gate(int32_t num, unsigned long base, unsigned long limit, uint8_t access, uint8_t gran);
void init_gdt();

#endif /* __GDT_H__ */
