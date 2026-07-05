#include <stdint.h>
#include <mem_node.h>
#include <mem_allocator.h>

MemNode* head = NULL;

//Find a free node that has the size closest to required size
static MemNode* find_best_fit(size_t size) {
    MemNode* temp = &head;
    MemNode* best_candidate = NULL;
    while (temp->_next != NULL) {
        if (temp->_is_free && temp->_size < size) {
            if (best_candidate == NULL) {
                best_candidate = temp;
            } else if (temp->_size < best_candidate->_size) {
                best_candidate = temp;
            }
        } 
        temp = temp->_next;
    }
    return best_candidate;
}

static void* malloc(size_t size) {
    if (size > MAX_SIZE) {
        //TODO: Error handling
    } else {
        if (head == NULL) {
            MemNode temp = {
                ._size = MAX_SIZE,
                ._is_free = true,
                ._next = NULL
            };
            allocate(&temp, size);
            return &temp;
        }
        MemNode* freeNode = find_best_fit(size);
        allocate(&freeNode, size);
        return freeNode;
    }
}

static void free(void* ptr) {
    if (head == NULL) return;
    MemNode* cast_ptr = (MemNode*) ptr;
    free_and_merge(cast_ptr);
}