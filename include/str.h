#ifndef __STR_H__
#define __STR_H__

#include <types.h>

int32_t strlen(const uint8_t* str);
int32_t strcmp(const uint8_t* str1, const uint8_t* str2);
uint8_t* strtok(uint8_t* str, const uint8_t* delimiter);
int32_t atoi(uint8_t* str);
void strcat(uint8_t* dst, const uint8_t* src);
size_t strnlen(const uint8_t* str, size_t max_len);
void strncat(uint8_t* dst, const uint8_t* src, size_t n);

#endif /* __STR_H__ */
