#include <xc.h>
#include "switches.h"

void init_switches() {
    TRISFbits.TRISF3 = 1; // RF3 (SW0) configured as input
    TRISFbits.TRISF5 = 1; // RF5 (SW1) configured as input
    TRISFbits.TRISF4 = 1; // RF4 (SW2) configured as input 
    TRISDbits.TRISD15 = 1; // RD15 (SW3) configured as input
    TRISDbits.TRISD14 = 1; // RD14 (SW4) configured as input
    TRISBbits.TRISB11 = 1; // RB11 (SW5) configured as input
    ANSELBbits.ANSB11 = 0; // RB11 (SW5) disabled analog
    TRISBbits.TRISB10 = 1; // RB10 (SW6) configured as input
    ANSELBbits.ANSB10 = 0; // RB10 (SW6) disabled analog
    TRISBbits.TRISB9 = 1; // RB9 (SW7) configured as input
    ANSELBbits.ANSB9 = 0;
}

int read_switches() {
    int val = PORTFbits.RF3; // read SW0
    val += PORTFbits.RF5 << 1; // read SW1
    val += PORTFbits.RF4 << 2; // read SW2
    val += PORTDbits.RD15 << 3 ; // read SW3
    val += PORTDbits.RD14 << 4; // read SW4
    val += PORTBbits.RB11 << 5; // read SW5
    val += PORTBbits.RB10 << 6; // read SW6
    val += PORTBbits.RB9 << 7; // read SW7
    return val;
}

int read_switch(int choice) {
    return read_switches() & (0x01 << choice);
}


