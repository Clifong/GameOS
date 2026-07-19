#ifndef ISRS_H
#define ISRS_H

#include <stdint.h>
#include <kernel/regs.h>

void isrs_install();
void fault_handler(struct regs* r);

#endif