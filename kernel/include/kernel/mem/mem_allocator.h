#ifndef _KERNEL_MEM_ALLOCATOR_H
#define _KERNEL_MEM_ALLOCATOR_H

#include <stddef.h>

#define MAX_SIZE 100

void* kmalloc(size_t size);
void kfree(void* ptr);
#endif