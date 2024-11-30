/* PenguinOS Keyboard Driver */
#include <io.h>
#include <vga.h>
#include <irqs.h>
#include <keyboard.h>

uint8_t keyboard_us[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*',
    0,
    ' ',
    0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,
    0,
    0,
    0,
    0,
    '-',
    0,
    0,
    0,
    '+',
    0,
    0,
    0,
    0,
    0,
    0, 0, 0,
    0, 0,
    0
};

uint8_t keyboard_us_shift[128] = {
    0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0,
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
    0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
    '*',
    0,
    ' ',
    0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,
    0,
    0,
    0,
    0,
    '-',
    0,
    0,
    0,
    '+',
    0,
    0,
    0,
    0,
    0,
    0, 0, 0,
    0, 0,
    0
};

volatile uint8_t keyboard_buffer[KEYBOARD_BUFFER_SIZE];
volatile uint32_t keyboard_buffer_start = 0;
volatile uint32_t keyboard_buffer_end = 0;
static int32_t shift_pressed = 0;

void keyboard_handler() {
    uint8_t scancode = inb(0x60);

    if (scancode & 0x80) {
        if (scancode == LEFT_SHIFT_RELEASED || scancode == RIGHT_SHIFT_RELEASED)
            shift_pressed = 0;
    }
    else {
        if (scancode == LEFT_SHIFT_PRESSED || scancode == RIGHT_SHIFT_PRESSED) {
            shift_pressed = 1;
        }
        else {
            uint8_t c;

            if (shift_pressed) {
                c = keyboard_us_shift[scancode];
            }
            else {
                c = keyboard_us[scancode];
            }

            if (c) {
                keyboard_buffer[keyboard_buffer_end] = c;
                keyboard_buffer_end = (keyboard_buffer_end + 1) % KEYBOARD_BUFFER_SIZE;
            }
        }
    }
}

void init_keyboard() {
    irq_install_handler(1, keyboard_handler);
}

uint8_t keyboard_getchar() {
    while (keyboard_buffer_start == keyboard_buffer_end);

    uint8_t c = keyboard_buffer[keyboard_buffer_start];
    keyboard_buffer_start = (keyboard_buffer_start + 1) % KEYBOARD_BUFFER_SIZE;

    return c;
}

int32_t keyboard_has_input() {
    return keyboard_buffer_start != keyboard_buffer_end;
}

uint8_t keyboard_getchar_non_blocking() {
    if (keyboard_has_input()) {
        uint8_t c = keyboard_buffer[keyboard_buffer_start];
        keyboard_buffer_start = (keyboard_buffer_start + 1) % KEYBOARD_BUFFER_SIZE;

        return c;
    }

    return 0;
}

int32_t getch() {
    return keyboard_getchar();
}

void get_input(uint8_t* buffer, int32_t size) {
    int32_t index = 0;
    uint8_t c;

    while (index < size - 1) {
        c = getch();

        if (c == '\n')
            break;
        else if (c == '\b') {
            if (index > 0) {
                index--;
                putc((uint8_t)'\b');
                putc((uint8_t)' ');
                putc((uint8_t)'\b');
            }
        }
        else {
            buffer[index++] = c;
            putc(c);
        }
    }

    buffer[index] = '\0';
}
