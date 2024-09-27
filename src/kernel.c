/* PenguinOS Kernel */
#include <vga.h>
#include <gdt.h>
#include <kprintf.h>
#include <idt.h>
#include <isrs.h>
#include <irq.h>
#include <syscall.h>
#include <heap.h>
#include <timer.h>
#include <keyboard.h>

int32_t kernel_main()
{
	init_vga();
	set_text_color(14, 0);
	puts("Welcome to PenguinOS!\r\n");
	set_text_color(15, 0);

	for (int32_t i = 0; i < 16; i++)
	{
		set_text_color(i, i);
		putc(' ');
	}
	puts("\r\n");

	set_text_color(10, 0);
	init_gdt();
	init_idt();
	init_isrs();
	init_irq();

	__asm__ __volatile__("sti");

	init_heap();
	
	void* ptr1 = malloc(256);
	void* ptr2 = malloc(512);
	set_text_color(11, 0);
	kprintf("[DEBUG] malloc() test -> ptr1=0x%x, ptr2=0x%x\r\n", (uint32_t)ptr1, (uint32_t)ptr2);
	set_text_color(10, 0);
	free(ptr1);
	free(ptr2);

	init_timer();
	init_keyboard();

	set_text_color(15, 0);

	for (;;);

	return 0;	// Should never get here
}
