#ifndef REGS_H
#define REGS_H

struct regs {
    unsigned int gs, fs, es, ds; //Push the segs last
    unsigned int edi, esi, ebp, esp, ebx, edx, ecs, eax; //Pushed by pusha
    unsigned int int_no, err_code; //push byte no. and ecode do this
    unsigned int eip, cs, eflags, useresp, ss; //Pushed by the processor automatically
};

#endif