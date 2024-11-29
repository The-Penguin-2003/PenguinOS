#ifndef __TYPES_H__
#define __TYPES_H__

typedef char int8_t;
typedef unsigned char uint8_t;

typedef short int16_t;
typedef unsigned short uint16_t;

typedef int int32_t;
typedef unsigned int uint32_t;

typedef long long int64_t;
typedef unsigned long long uint64_t;

typedef int8_t bool;

typedef int32_t size_t;

#define NULL ((void*)0)

#define TRUE 1
#define FALSE 0

#define INT32_MAX 0x7FFFFFFFL
#define INT32_MIN (-INT32_MAX - 1L)

#endif /* __TYPES_H__ */
