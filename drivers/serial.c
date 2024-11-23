/* PenguinOS Serial I/O Driver */

#include <io.h>
#include <kprintf.h>
#include <serial.h>

int32_t init_serial() {
    outb(PORT_COM1 + 1, 0x00);
    outb(PORT_COM1 + 3, 0x80);
    outb(PORT_COM1 + 0, 0x03);
    outb(PORT_COM1 + 1, 0x00);

    outb(PORT_COM1 + 3, 0x03);
    outb(PORT_COM1 + 2, 0xC7);
    outb(PORT_COM1 + 4, 0x0B);
    outb(PORT_COM1 + 4, 0x1E);
    outb(PORT_COM1 + 0, 0xAE);

    if (inb(PORT_COM1 + 0) != 0xAE)
        return 1;

    outb(PORT_COM1 + 4, 0x0F);
    return 0;
}

int32_t is_transmit_empty() {
    return inb(PORT_COM1 + 5) & 0x20;
}

void write_serial(const uint8_t c) {
    while (is_transmit_empty() == 0);
    outb(PORT_COM1, c);
}

void puts_serial(const uint8_t* str) {
    uint32_t i = 0;
    write_serial(str[0]);

    while (*str++)
        write_serial(str[i]);
}

void log_serial(const uint8_t* str, const int32_t err_level) {
    switch (err_level) {
        case 0:
            puts_serial((uint8_t*)"[ERROR] ");
            break;
        case 1:
            puts_serial((uint8_t*)"[WARNING] ");
            break;
        case 2:
            puts_serial((uint8_t*)"[INFO] ");
            break;
        case 3:
            puts_serial((uint8_t*)"[DEBUG] ");
            break;
    }

    puts_serial(str);
}
