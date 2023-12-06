/* 
 * File:   lcd_display.c
 * Author: lclem
 *
 * Created on November 29, 2023, 4:03 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

// Delay function
void delay2(int timeDelay){
    for(int i = 0; i < timeDelay; i++){}   
}

// Sets up all the bits for input/output
void init_display(){
    TRISBbits.TRISB12 = 0; //RB12 set as output
    ANSELBbits.ANSB12 = 0; //RB12 analog functionality disabled
    TRISBbits.TRISB13 = 0; //RB13 set as output
    ANSELBbits.ANSB13 = 0; //RB13 analog functionality disabled
    
    TRISAbits.TRISA9 = 0; //RA9 set as output
    TRISAbits.TRISA10 = 0; //RA10 set as output
    TRISGbits.TRISG12 = 0; //RG12 set as output
    TRISAbits.TRISA14 = 0; //RA14 set as output
    TRISDbits.TRISD6 = 0; //RD6 set as output
    TRISGbits.TRISG13 = 0; //RG13 set as output
    TRISGbits.TRISG15 = 0; //RG15 set as output
    TRISDbits.TRISD7 = 0; //RD7 set as output
    TRISDbits.TRISD13 = 0; //RD13 set as output
    TRISGbits.TRISG14 = 0; //RG14 set as output
    
    TRISFbits.TRISF3 = 1; // RF3 (SW0) configured as input
    TRISFbits.TRISF5 = 1; // RF5 (SW1) configured as input
    TRISFbits.TRISF4 = 1; // RF4 (SW2) configured as input
    TRISDbits.TRISD15 = 1; // RD15 (SW3) configured as input
    TRISDbits.TRISD14 = 1; // RD14 (SW4) configured as input
}

// Sets up the 7 segment display so that only the first position is shown
void set_segment_display(int bits){
   if (bits & 1){ LATBbits.LATB12 = 0; } else { LATBbits.LATB12 = 1; } // digit 1
   if (bits & 2){ LATBbits.LATB13 = 0; } else { LATBbits.LATB13 = 1; } // digit 2
   if (bits & 4){ LATAbits.LATA9 = 0; } else { LATAbits.LATA9 = 1; } // digit 3
   if (bits & 8){ LATAbits.LATA10 = 0; } else { LATAbits.LATA10 = 1; } // digit 4
}

void set_segment_reset(){
   LATBbits.LATB12 = 1; // digit 1
   LATBbits.LATB13 = 1; // digit 2
   LATAbits.LATA9 = 1; // digit 3
   LATAbits.LATA10 = 1; // digit 4
}

// Clears all the pins of the 7 segment display
void reset_pins(){ 
    LATGbits.LATG12 = 1; //RG12 set as output
    LATAbits.LATA14 = 1; //RA14 set as output
    LATDbits.LATD6 = 1; //RD6 set as output
    LATGbits.LATG13 = 1; //RG13 set as output
    LATGbits.LATG15 = 1; //RG15 set as output
    LATDbits.LATD7 = 1; //RD7 set as output
    LATDbits.LATD13 = 1; //RD13 set as output
    LATGbits.LATG14 = 1; //RG14 set as output
}

// Sets the pins that are needed for the 7 segment display
void set_pins(int LED){
    if (LED & 1){ LATGbits.LATG12 = 0; } // top
    if (LED & 2){ LATAbits.LATA14 = 0; } // top right
    if (LED & 4){ LATDbits.LATD6 = 0; } // bottom right
    if (LED & 8){ LATGbits.LATG13 = 0; } // bottom
    if (LED & 16){ LATGbits.LATG15 = 0; } // bottom left
    if (LED & 32){ LATDbits.LATD7 = 0; } // top right
    if (LED & 64){ LATDbits.LATD13 = 0; } // middle
    if (LED & 128){LATGbits.LATG13 = 0; } // dot 
}

// Displays a particular number on the seven segment display
void display_digit(int number){
    int pins = 0x00;
    reset_pins();
    switch(number){
        case 0: pins = 0x3f;
        break;
        case 1: pins = 0x06;
        break;
        case 2: pins = 0x5B;
        break;
        case 3: pins = 0x4f;
        break;
        case 4: pins = 0x66;
        break;
        case 5: pins = 0x6d;
        break;
        case 6: pins = 0x7d;
        break;
        case 7: pins = 0x07;
        break;
        case 8: pins = 0xff;
        break;
        case 9: pins = 0x67;
        break;
    }
    set_pins(pins);
}

// Display up to a 4 digit number
void display_num(int num, int duration){
    for(int i = 0; i < duration; i++){
        int pos = 1;
        int tmpNum = num;
        while(tmpNum != 0 && pos <= 8){
            int digit = tmpNum%10;
            tmpNum = tmpNum/10;
            reset_pins();
            set_segment_display(pos);
            pos = pos << 1;
            display_digit(digit);
        }
        while(pos <= 8){
            pos++;
        }
    }
    reset_pins();
}

