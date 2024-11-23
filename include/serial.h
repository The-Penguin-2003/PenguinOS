#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <types.h>

#define PORT_COM1 0x3F8

int32_t init_serial();
int32_t is_transmit_empty();
void write_serial(const uint8_t c);
void puts_serial(const uint8_t* str);
void log_serial(const uint8_t* str, const int32_t err_level);

#endif /* __SERIAL_H__ */
