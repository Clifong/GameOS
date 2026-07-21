#include <kernel/regs.h>
#include <stdio.h>
#include <kernel/irq/irq.h>

//Track how many ticks elapsed
int timer_ticks = 0;

void timer_handler(struct regs* r) {
    timer_ticks++;

    /*
    Based on PIT model 8253 which fires
    18.2222 times per second
    */
    if (timer_ticks % 18 == 0) {
        puts("One second has passed");
    }
}

//Installs into IRQ0 since IRQ0 is in channel 0 of PIT
void timer_install() {
    irq_install_handler(0, timer_handler);
}