#include <mem_node.h>
#include <stddef.h>

void free_and_merge(MemNode* toFree) {
    toFree->_is_free = true;
    if (toFree->_next != NULL) {
        MemNode* neigh = toFree->_next;
        toFree->_next = neigh->_next;
        toFree->_size += neigh->_size;
    }
}

void allocate(MemNode* node, size_t size) {
    MemNode new_neigh = {
        ._size = node->_size - size,
        ._is_free = true,
        ._next = node->_next
    };
    node->_size = size;
    node->_is_free = false;
    node->_next = new_neigh;
}