#ifndef _KERNEL_MEM_NODE_H
#define _KERNEL_MEM_NODE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct MemNode MemNode;

struct MemNode {
    size_t _size;
    bool _is_free;
    MemNode* _next;
};

void free_and_merge(MemNode* toFree);
void allocate(MemNode* node, size_t size);
#endif