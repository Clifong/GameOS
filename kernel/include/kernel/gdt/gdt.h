#ifndef GDT_H
#define GDT_H

#include <stdint.h>
#include <stddef.h>

extern void gdt_flush();
void gdt_install();

#endif 