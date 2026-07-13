#include <stdint.h>
#include <stddef.h>
#include <kernel/gdt/gdt.h>

// We follow the standard 64 but system segment descriptor
// Refer to readme for more info
struct gdt_entry { 
    unsigned char base_high; 
    unsigned char access; 
    unsigned char granularity; 
    unsigned char base_middle;
    unsigned short limit_low; 
    unsigned short base_low; 
}__attribute__((packed));

// The LGDT register needs to store a pointer
// that points to our GDT table
struct gdt_ptr {
    unsigned short limit;
    unsigned int base;
}__attribute__((packed));

//3 entries: null segment, code segment, data segment
//null being the first entry is the DEFAULT for most OS
struct gdt_entry gdt[3];
struct gdt_ptr gp;

// By default, GRUB loads a local GDT for us. But if we overwrite
// GRUB, we trash the GDT. So we need to load our own GDT, hence
// this function
extern void gdt_flush();

//Set descriptor in the table
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char granularity) {
    
    //Set the descriptor base address
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    //Set the descriptor limits
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    //Set granularity and access flags
    gdt[num].granularity |= (granularity & 0xF0);
    gdt[num].access = access;
}

/*
Does:
1. gdt pointer
2. the 3 gdt entries
3. Calls gdt_flush() in .ass file to update the gdt pointer
*/
void gdt_install() {

    //Set up gdt pointer and limit
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base = (unsigned int)&gdt;

    //Set up NULL descriptor (1st entry)
    gdt_set_gate(0, 0, 0, 0, 0);

    /*
    Set up code segment (2nd entry). 
    Base address: 0
    Limit: 4GB
    Granularity: 4KB blocks
    Opcode: 32-bit
    */
   gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

   /*
   Set up data segment (3rd entry). Identical to
   code segment
   */
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    //Flush out and install new gdt
    gdt_flush();
}