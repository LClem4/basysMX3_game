
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h>
#include <string.h>
#include "config.h"
//#include <stdbool.h>
#include "interrupts.h"
//#include <stdint.h>
#include "led.h"
//#include <proc/p32mz2048efh144.h>
#pragma config FSRSSEL = PRIORITY_7     /* Assign the SRS to level 7 priority handlers */

//#define SYS_FREQ 200000000              // Running at 200MHz
#define SYS_FREQ 200
//void setup_interrupts() {
//    OPTION_REG = 0xD7; // timer 0 internal clock, prescaler 1:256
//    INTCONbits.TMR0IE = 1; // enable interrupts for timer 0
//    ei(); // enable all interrupts
//}
#define TMR_TIME    1.0003 // 300 us for each tick


extern char player_sprite;
extern int score;
void init_timer5()
{
  PR5 = (int)(((float)(TMR_TIME * PB_FRQ) / 256) + 0.5);   //set period register, generates one interrupt every 300 us                     //             set period register, generates one interrupt every 300 us
  TMR5 = 0;                           //    initialize count to 0
  T5CONbits.TCKPS = 3;                //    1:256 prescaler value
  T5CONbits.TGATE = 0;                //    not gated input (the default)
  T5CONbits.TCS = 0;                  //    PCBLK input (the default)
  IPC5bits.T5IP = 2;                  //    INT step 4: priority
  IPC5bits.T5IS = 0;                  //    subpriority
  IFS0bits.T5IF = 0;                  //    clear interrupt flag
  IEC0bits.T5IE = 1;                  //    enable interrupt
  T5CONbits.ON = 1;                   //    turn on Timer5
  
}

void init_timer1()
{
    T1CONbits.TON = 0;
    IEC0bits.T1IE = 1;  // Disable Timer 2 Interrupt
    TMR1 = 0x000;
    T1CONbits.TCS = 0;
    
    T1CONbits.TCKPS = 0b00;
    
    IFS0bits.T1IF = 0;  // Clear interrupt flag for timer 2
    IPC1bits.T1IP = 3;  // Interrupt priority 3
    IPC1bits.T1IS = 1;  // Sub-priority 1
    IEC0bits.T1IE = 1;  // Enable Timer 2 Interrupt

    // Turn on timer 2
    T1CONbits.TON   = 1;
}

void init_timer2(int frequency)
{
    T2CON   = 0x00;      // Disable timer 2 when setting it up
    TMR2    = 0;        // Set timer 2 counter to 0
    IEC0bits.T2IE = 1;  // Disable Timer 2 Interrupt

    // Set up the period. Period = PBCLK3 frequency, which is SYS_FREQ / 2, divided by the frequency we want and then divided by 8 for our chosen pre-scaler.
//    PR2 = SYS_FREQ / 2 / frequency / 8;
    PR2 = (int)(((float)(TMR_TIME * PB_FRQ) / 256) + 0.5);
    // Set up the pre-scaler
    T2CONbits.TCKPS = 0b000; // Pre-scale of 8

    IFS0bits.T2IF = 0;  // Clear interrupt flag for timer 2
    IPC2bits.T2IP = 3;  // Interrupt priority 3
    IPC2bits.T2IS = 1;  // Sub-priority 1
    IEC0bits.T2IE = 1;  // Enable Timer 2 Interrupt

    // Turn on timer 2
    T2CONbits.TON   = 1;
}

void init_timers() {
    macro_enable_interrupts();          //    enable interrupts at CPU
    INTCONSET = _INTCON_MVEC_MASK; 
    INTCONbits.MVEC = 1;
	
    init_timer1();
    init_timer5();
    init_timer2(0xff);
}

void __attribute__((vector(_TIMER_1_VECTOR), interrupt(ipl3soft), nomips16)) timer1_handler()
{
    IFS0bits.T1IF = 0;
    TMR1 = 0x000;
    
    if(PORTBbits.RB1){
       if(player_sprite > 0){
          player_sprite--; 
       }
       else{
          player_sprite = 7;
       } 
    }
    else if(PORTAbits.RA15){
       if(player_sprite < 7){
          player_sprite++; 
       }
       else{
          player_sprite = 0;
       } 
    }
 
}

void __attribute__((vector(_TIMER_5_VECTOR), interrupt(ipl3soft), nomips16)) timer5_handler()
{
    IFS0bits.T5IF = 0;
    TMR5 = 0;
  
}


void __attribute__((vector(_TIMER_2_VECTOR), interrupt(ipl3soft), nomips16)) timer2_handler()
//void  __ISR(_TIMER_2_VECTOR, IPL7SRS) timer2_handler()
{
    IFS0bits.T2IF = 0;  // Clear interrupt flag for timer 2
    TMR2    = 0xffff;
    display_num(score,1);
    
//    RHO = ! RHO;
    //LATGINV = 1 << 0;   // Toggle pin RH0
}


// // only process Timer0-triggered interrupts
//if(INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
// // static variable for permanent storage duration
// static uint8_t portValue;
// // write to port latches
// LATB = (portValue++ >> 4); // RB[0:3] = LED[4:7]
// LATD = portValue++; // RD[0:3] = LED[0:3]
// // clear this interrupt condition
// INTCONbits.TMR0IF = 0;
//}
//}

