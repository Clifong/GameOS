#include <stdint.h>
#include <stddef.h>

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
}__attribute((packed));

//3 entries: null segment, code segment, data segment
//null being the first entry is the DEFAULT for most OS
struct gdt_entry gdt[3];
struct gdt_ptr gp;

// By default, GRUB loads a local GDT for us. But if we overwrite
// GRUB, we trash the GDT. So we need to load our own GDT, hence
// this function
extern void gdt_flush();