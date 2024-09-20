#ifndef __STRING_H__
#define __STRING_H__

#include <types.h>

int32_t strlen(int8_t* str);

extern uint8_t* memcpy(uint8_t* dst, const uint8_t* src, int32_t cnt);
extern uint8_t* memset(uint8_t* dst, uint8_t val, int32_t cnt);
extern uint16_t* memsetw(uint16_t* dst, uint16_t val, int32_t cnt);

#endif /* __STRING_H__ */
