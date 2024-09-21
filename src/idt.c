/* PenguinOS Interrupt Descriptor Table (IDT) */

#include <idt.h>
#include <string.h>
#include <kprintf.h>

struct idt_entry idt[256];
struct idt_ptr idtp;

extern void idt_load();

void idt_set_gate(uint8_t num, unsigned long base, uint16_t sel, uint8_t flags)
{
	idt[num].base_low = (base & 0xFFFF);
	idt[num].base_high = (base >> 16) & 0xFFFF;

	idt[num].sel = sel;
	idt[num].zero = 0;
	idt[num].flags = flags;
}

void init_idt()
{
	idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
	idtp.base = (uint32_t)&idt;

	memset(&idt, 0, sizeof(struct idt_entry)*256);

	idt_load();
	kprintf("[KERNEL] Loaded IDT -> IDT=0x%x\n", (uint32_t)&idt);
}
