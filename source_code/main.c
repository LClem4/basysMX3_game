/* 
 * File:   main.c
 * Author: ph4671
 *
 * Created on October 2, 2023, 8:47 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h>
#include "lcd.h"
#include "led.h"
#include "config.h"
#include "interrupts.h"
#include "lcd_display.c"

char player_sprite;
int delay(int how_long) {
    int delay_length_tuned = 1500;
    for (int i = 0; i < how_long; i++) {
        for (int j = 0; j < delay_length_tuned; j++) {
            1+1;
        }
    }
    return 1;
}

int main(int argc, char** argv) {
    
    general_setup();
    init_timers();
    init_buttons();
    init_sprite_player();
    spike_pair(3,3);
    
    int s = 0;
    int wall = 15;
    int topSpike = 0;
    int botSpike = 0;
    player_sprite = 0;
    
    while (1) {
   
        char top[] = {5,'\0'};
        char bot[] = {6,'\0'};
        char bot2[] = {6,'\0'};
        char player[] = {(player_sprite%4)+1,'\0'};

        LCD_WriteStringAtPos(top,0,wall);
        LCD_WriteStringAtPos(bot,1,wall);
    
        if(player_sprite <= 3){
            LCD_WriteStringAtPos(player,0,1);
        }
        else{
            LCD_WriteStringAtPos(player,1,1);
        }
        wall--;
        delay(2);
        LCD_DisplayClear();
        if(wall < 0){
            spike_pair(topSpike,botSpike);
            topSpike++;
            botSpike++;
            if(topSpike > 3){
                topSpike = 0;
                botSpike = 0;
            }
            wall = 15;
        }   
        display_num(100);
    }
    
}

void init_buttons(){
    TRISBbits.TRISB1 = 1; // RB1 (BTNU) configured as input
    ANSELBbits.ANSB1 = 0; // RB1 (BTNU) disabled analog

    TRISBbits.TRISB0 = 1; // RB1 (BTNL) configured as input
    ANSELBbits.ANSB0 = 0; // RB1 (BTNL) disabled analog

    TRISFbits.TRISF4 = 1; // RF0 (BTNC) configured as input 

    TRISBbits.TRISB8 = 1; // RB8 (BTNR) configured as input
    ANSELBbits.ANSB8 = 0;	// RB8 (BTNR) disabled analog

    TRISAbits.TRISA15 = 1;	// RA15 (BTND) configured as input
}


