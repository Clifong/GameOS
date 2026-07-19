#ifndef ISRS_H
#define ISRS_H

#include <stdint.h>

struct regs {
    unsigned int gs, fs, es, ds; //Push the segs last
    unsigned int edi, esi, ebp, esp, ebx, edx, ecs, eax; //Pushed by pusha
    unsigned int int_no, err_code; //push byte no. and ecode do this
    unsigned int eip, cs, eflags, useresp, ss; //Pushed by the processor automatically
};

void isrs_install();
void fault_handler(struct regs* r);

#endif