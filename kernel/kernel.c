/* PenguinOS Kernel */
#include <vga.h>
#include <kprintf.h>
#include <serial.h>
#include <gdt.h>

void print_ok_msg(uint8_t* msg) {
    set_text_color(0xF, 0x0);
    kprintf((uint8_t*)"[ ");

    set_text_color(0x2, 0x0);
    kprintf((uint8_t*)"OK");

    set_text_color(0xF, 0x0);
    kprintf((uint8_t*)" ] ");

    kprintf((uint8_t*)"%s", msg);
}

int kernel_main() {
    init_vga();
    print_ok_msg((uint8_t*)"VGA Initialized\r\n");

    init_serial();
    print_ok_msg((uint8_t*)"Serial Port COM1 Initialized\r\n");

    init_gdt();
    print_ok_msg((uint8_t*)"GDT Initialized\r\n");

    kprintf((uint8_t*)"\r\nWelcome to ");
    set_text_color(0xE, 0x0);
    kprintf((uint8_t*)"PenguinOS");
    set_text_color(0xF, 0x0);
    kprintf((uint8_t*)"!\r\n");

    for (;;);
    return 0;
}
