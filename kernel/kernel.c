/* PenguinOS Kernel */
#include <vga.h>

int kernel_main() {
    init_vga();
    set_text_color(0xE, 0x0);
    puts((uint8_t*)"PenguinOS\r\n");
    set_text_color(0xF, 0x0);
    puts((uint8_t*)">");

    for (;;);
    return 0;
}
