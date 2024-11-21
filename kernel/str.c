/* PenguinOS String Manipulation Kernel Module */
#include <str.h>

int32_t strlen(const uint8_t* str) {
    int32_t i = 0;

    while (str[i] != (int8_t)0)
        ++i;

    return i;
}
