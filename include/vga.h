#ifndef __VGA_H__
#define __VGA_H__

#include <types.h>

extern void clear();
extern void putc(uint8_t c);
extern void puts(uint8_t* str);
extern void set_text_color(uint8_t fg, uint8_t bg);
extern void init_vga();

#endif /* __VGA_H__ */
