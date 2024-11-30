/* PenguinOS Kernel */
#include <vga.h>
#include <kprintf.h>
#include <serial.h>
#include <gdt.h>
#include <idt.h>
#include <isrs.h>
#include <irqs.h>
#include <syscalls.h>
#include <heap.h>
#include <timer.h>
#include <keyboard.h>
#include <shell.h>

void print_ok_msg(uint8_t* msg) {
    set_text_color(0xF, 0x0);
    kprintf((uint8_t*)"[ ");

    set_text_color(0x2, 0x0);
    kprintf((uint8_t*)"OK");

    set_text_color(0xF, 0x0);
    kprintf((uint8_t*)" ] ");

    kprintf((uint8_t*)"%s", msg);
}

void kernel_main() {
    init_vga();
    print_ok_msg((uint8_t*)"VGA Initialized\r\n");

    init_serial();
    print_ok_msg((uint8_t*)"Serial Port COM1 Initialized\r\n");

    init_gdt();
    print_ok_msg((uint8_t*)"GDT Initialized\r\n");

    init_idt();
    print_ok_msg((uint8_t*)"IDT Initialized\r\n");

    init_isrs();
    print_ok_msg((uint8_t*)"ISRS Initialized\r\n");

    init_irqs();
    print_ok_msg((uint8_t*)"IRQS Initialized\r\n");
    print_ok_msg((uint8_t*)"Syscall Infrastructure Initialized\r\n");

    asm volatile("sti");

    init_heap();
    print_ok_msg((uint8_t*)"Heap Memory Initialized\r\n");

    init_timer();
    print_ok_msg((uint8_t*)"Programmable Interval Timer Initialized\r\n");

    init_keyboard();
    print_ok_msg((uint8_t*)"Keyboard Initialized\r\n");

    kprintf((uint8_t*)"\r\nInitializing shell...");

    kprintf((uint8_t*)"\r\nWelcome to ");
    set_text_color(0xE, 0x0);
    kprintf((uint8_t*)"PenguinOS");
    set_text_color(0xF, 0x0);
    kprintf((uint8_t*)"!\r\n");

    init_shell();
}
