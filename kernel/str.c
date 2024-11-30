/* PenguinOS String Manipulation Kernel Module */
#include <str.h>

int32_t strlen(const uint8_t* str) {
    int32_t i = 0;

    while (str[i] != (int8_t)0)
        ++i;

    return i;
}

int32_t strcmp(const uint8_t* str1, const uint8_t* str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }

    return *(const uint8_t*)str1 - *(const uint8_t*)str2;
}

uint8_t* strchr(const uint8_t* str, int32_t c) {
    while (*str) {
        if (*str == (uint8_t)c)
            return (uint8_t*)str;

        str++;
    }

    if (c == '\0')
        return (uint8_t*)str;

    return NULL;
}

uint8_t* strtok(uint8_t* str, const uint8_t* delimiter) {
    static uint8_t* last;

    if (str)
        last = str;
    else
        str = last;

    if (!str || *str == '\0')
        return NULL;

    uint8_t* token_start = str;

    while (*str && !strchr(delimiter, *str))
        str++;

    if (*str) {
        *str = '\0';
        last = str + 1;
    }
    else
        last = NULL;

    return token_start;
}

int32_t atoi(uint8_t* str) {
    int32_t res = 0;

    for (int32_t i = 0; str[i] != '\0'; i++)
        res = res * 10 + str[i] - '0';

    return res;
}

void strcat(uint8_t* dst, const uint8_t* src) {
    while (*dst)
        dst++;

    while (*src) {
        *dst = *src;
        dst++;
        src++;
    }

    *dst = '\0';
}

size_t strnlen(const uint8_t* str, size_t max_len) {
    size_t len = 0;

    while (*str && len < max_len) {
        len++;
        str++;
    }

    return len;
}

void strncat(uint8_t* dst, const uint8_t* src, size_t n) {
    while (*dst)
        dst++;

    while (*src && n > 0) {
        *dst = *src;
        dst++;
        src++;
        n--;
    }

    *dst = '\0';
}
