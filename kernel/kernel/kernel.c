#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/mem/mem_allocator.h>

void kernel_main(void) {
	terminal_initialize();
	printf("Hello, kernel World!\n");

	//Free when mem allocator has not been initialised yet
    //Expected: FAIL
    kfree(0);

    //Allocate more than limit
    //Expected: FAIL
    kmalloc(MAX_SIZE + 1);

    //Free after a bad malloc
    //Expected: FAIL
    kfree(0);

    //Okay malloc
    //Expected: OK
    void* test_ptr = kmalloc(1);
	printf(test_ptr);

    //Free malloc
    //Expected: OK
    kfree(test_ptr);
	printf(test_ptr);
}
