/* PenguinOS Memory Manipulation Kernel Module */
#include <mem.h>

uint8_t* memcpy(uint8_t* dst, const uint8_t* src, int32_t cnt) {
    int32_t i = 0;

    for (; i < cnt; ++i)
        dst[i] = src[i];

    return dst;
}

uint8_t* memset(uint8_t* dst, uint8_t val, int32_t cnt) {
    int32_t i = 0;

    for (; i < cnt; ++i)
        dst[i] = val;

    return dst;
}

uint16_t* memsetw(uint16_t* dst, uint16_t val, int32_t cnt) {
    int32_t i = 0;

    for (; i < cnt; ++i)
        dst[i] = val;

    return dst;
}
