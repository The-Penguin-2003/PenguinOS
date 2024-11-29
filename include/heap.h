#ifndef __HEAP_H__
#define __HEAP_H__

#include <types.h>

typedef struct {
    size_t size;
    struct block* next;
} block_t;

#define HEAP_SIZE 1024*1024

void init_heap();
void* malloc(size_t size);
void free(void* ptr);
void* calloc(size_t num, size_t size);

#endif /* __HEAP_H__ */
