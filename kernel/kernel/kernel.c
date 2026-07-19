#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/mem/mem_allocator.h>
#include <kernel/gdt/gdt.h>
#include <kernel/idt/idt.h>
#include <kernel/isrs/isrs.h>

void kernel_main(void) {

    // gdt_install();
    // idt_install();
    isrs_install();
	terminal_initialize();
	// printf("Hello, kernel World!\n");

	// //Free when mem allocator has not been initialised yet
    // //Expected: FAIL
    // printf("Should fail\n");
    // kfree(0);

    // //Allocate more than limit
    // //Expected: FAIL
    // printf("Should fail\n");
    // kmalloc(MAX_SIZE + 1);

    // //Free after a bad malloc
    // //Expected: FAIL
    // printf("Should fail\n");
    // kfree(0);

    // //Okay malloc
    // //Expected: OK
    // printf("Should not fail\n");
    // void* test_ptr = kmalloc(1);
	// printf(test_ptr);

    // //Free malloc
    // //Expected: OK
    // printf("Should not fail\n");
    // kfree(test_ptr);
    // printf("Should fail\n");
	// printf(test_ptr);
}
