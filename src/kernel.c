/* PenguinOS Kernel */
#include <vga.h>

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

	for (;;);

	return 0;	// Should never get here
}
