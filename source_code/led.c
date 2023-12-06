
#include <xc.h>
#include "config.h"
#include "led.h"

int LED_VALUE = 0x00;



void _refresh() {
    PORTA = LED_VALUE;
}

void init_LEDs() {
    TRISA = 0x00;
    _refresh(0);
}

void set_LEDs(int x) {
    LED_VALUE = x & 0xff;
    _refresh();
}

void set_LED(int choice, int x) {
    if (x) {
        LED_VALUE |= 0x01 << choice;
    } else {
        LED_VALUE &= 0xff ^ (0x01 << choice);
    }
    _refresh();
}

void toggle_LEDs(int x) {
    LED_VALUE = (LED_VALUE ^ x) & 0xff;
    _refresh();
}

void toggle_all_LEDs() {
    toggle_LEDs(0xff);
}

void toggle_LED(int choice) {
    toggle_LEDs(0x01 << choice);
}