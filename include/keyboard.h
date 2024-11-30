#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <types.h>

#define KEYBOARD_BUFFER_SIZE 256

#define LEFT_SHIFT_PRESSED 0x2A
#define RIGHT_SHIFT_PRESSED 0x36
#define LEFT_SHIFT_RELEASED 0xAA
#define RIGHT_SHIFT_RELEASED 0xB6

uint8_t keyboard_getchar();
int32_t keyboard_has_input();
uint8_t keyboard_getchar_non_blocking();
void init_keyboard();
int32_t getch();
void get_input(uint8_t* buffer, int32_t size);

#endif /* __KEYBOARD_H__ */
