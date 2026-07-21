#ifndef KEYBOARD_H
#define KEYBOARD_H

/*
KDBUS = US keyboard layout
*/
extern unsigned char kdbus[128];

void keyboard_install();

#endif