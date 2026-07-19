#include <kernel/regs.h>
#include <kernel/idt/idt.h>
#include <stdio.h>

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

/*
Array of function pointers. Handle custom IRQ handler for a given IRQ
*/
void* irq_routines[16] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

//Installs custom IRQ handler for a given IRQ
void irq_install_handler(int irq, void (*handler)(struct regs* r)) {
    irq_routines[irq] = handler;
}

//Clears the handler for a given IRQ
void irq_uninstall_handler(int irq) {
    irq_routines[irq] = 0;
}

/*
We need to tell the PIC that we are mapping IEQ0 - IRQ15 to IDT entries 32 = 47
because they're usually mapped to entries 8 - 15
*/
void irq_remap(void) {
    outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0x00);
    outportb(0xA1, 0x00);
}

/*
Remap, then install the right ISRs to correct entries of IDT
*/
void irq_install() {
    irq_remap();
    idt_set_gate(32, (unsigned)irq0, 0x08, 0x8E);
    idt_set_gate(33, (unsigned)irq1, 0x08, 0x8E);
    idt_set_gate(34, (unsigned)irq2, 0x08, 0x8E);
    idt_set_gate(35, (unsigned)irq3, 0x08, 0x8E);
    idt_set_gate(36, (unsigned)irq4, 0x08, 0x8E);
    idt_set_gate(37, (unsigned)irq5, 0x08, 0x8E);
    idt_set_gate(38, (unsigned)irq6, 0x08, 0x8E);
    idt_set_gate(39, (unsigned)irq7, 0x08, 0x8E);
    idt_set_gate(40, (unsigned)irq8, 0x08, 0x8E);
    idt_set_gate(41, (unsigned)irq9, 0x08, 0x8E);
    idt_set_gate(42, (unsigned)irq10, 0x08, 0x8E);
    idt_set_gate(43, (unsigned)irq11, 0x08, 0x8E);
    idt_set_gate(44, (unsigned)irq12, 0x08, 0x8E);
    idt_set_gate(45, (unsigned)irq13, 0x08, 0x8E);
    idt_set_gate(46, (unsigned)irq14, 0x08, 0x8E);
    idt_set_gate(47, (unsigned)irq15, 0x08, 0x8E);
}

/*
IRQ ISRs runs this instead of fault exception handlers
0x20 is sent to tell the IRQ controller we are done handling
an interrupt

There are 2 PIC chips:
- 0x20 (Master controller): Handles IRQ0 - IRQ7
- 0xA0 (Slave controller): Handles IRQ8 - IRQ15

If the slave controller receives an interrupt, both controller MUST ACK.
Otherwise, the slave controller will nvr be able to receive any further interrupt
because it is "stuck" waiting for the original interrupt
*/
void irq_handler(struct regs* r) {
    //Blank function pointer
    void (*handler)(struct regs* r);

    //Do we have a custom handler for this? Run if so
    handler = irq_routines[r->int_no - 32];
    if (handler) {
        handler(r);
    }

    //If the IDT entry invoked >= 40, send an EOI to the slave
    if (r->int_no >= 40) {
        outportb(0xA0, 0x20);
    }
    //Master controller EOI!
    outportb(0x20, 0x20);
}