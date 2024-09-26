#ifndef __HEAP_H__
#define __HEAP_H__

#define HEAP_SIZE 1024*1024

#include <types.h>

typedef struct block
{
	size_t size;
	struct block* next;
} block_t;

void init_heap();
void* malloc(size_t size);
void free(void* ptr);

#endif /* __HEAP_H__ */
