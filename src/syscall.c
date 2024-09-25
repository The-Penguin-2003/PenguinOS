/* PenguinOS System Calls */

#include <syscall.h>
#include <kprintf.h>
#include <vga.h>

void handle_syscall(int32_t syscall_num)
{
	switch (syscall_num)
	{
		case 1:
			kprintf("This is SYSCALL 1\r\n");
			break;
		default:
			set_text_color(5, 0);
			kprintf("[ERROR] Invalid Syscall Number %d!\r\n", syscall_num);
			set_text_color(15, 0);
			break;
	}
}

void syscall_handler()
{
	int32_t syscall_num;
	void* arg;

	asm volatile("mov %%eax, %0" : "=r"(syscall_num));
	asm volatile("mov %%ebx, %0" : "=r"(arg));

	kprintf("[SYSCALL] syscall_num=%d, arg=%x\r\n", syscall_num, arg);

	handle_syscall(syscall_num);
}
