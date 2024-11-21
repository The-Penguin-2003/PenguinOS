#ifndef __MEM_H__
#define __MEM_H__

#include <types.h>

extern uint8_t* memcpy(uint8_t* dst, const uint8_t* src, int32_t cnt);
extern uint8_t* memset(uint8_t* dst, uint8_t val, int32_t cnt);
extern uint16_t* memsetw(uint16_t* dst, uint16_t val, int32_t cnt);

#endif /* __MEM_H__ */
