#include <xc.h>
#include "config.h"
#include "led.h"
#include "lcd.h"
#include "switches.h"

#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled)

void general_setup() {
    DDPCONbits.JTAGEN = 0;
    init_LEDs();
    LCD_Init();
    init_switches();
}