#include <stdbool.h>

typedef struct {
    size_t _size;
    bool _is_free;
    MemNode* _next;
} MemNode;

void free_and_merge(MemNode* toFree);
void allocate(MemNode* node, size_t size);