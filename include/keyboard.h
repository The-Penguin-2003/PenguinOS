#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#define KEYBOARD_BUFFER_SIZE 256

#define LEFT_SHIFT_PRESSED 0x2A
#define RIGHT_SHIFT_PRESSED 0x36

#define LEFT_SHIFT_RELEASED 0xAA
#define RIGHT_SHIFT_RELEASED 0xB6

#include <types.h>

void init_keyboard();
int8_t kb_getchar();
int32_t kb_has_input();
int8_t kb_getchar_non_blocking();

#endif /* __KEYBOARD_H__ */
