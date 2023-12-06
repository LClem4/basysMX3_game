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
#include "config.h"
#include "interrupts.h"

char player_sprite;
int score = 0;
void init_buttons();

int delay(int how_long) {
    int delay_length_tuned = 1500;
    for (int i = 0; i < how_long; i++) {
        for (int j = 0; j < delay_length_tuned; j++) {
            1+1;
        }
    }
    return 1;
}

int short_delay(int how_long) {
    for (int i = 0; i < how_long; i++) {
        1+1;
    }
    return 1;
}

void game_loop() {
    init_sprite_player();
    init_display();
    
    score = 0;
    int s = 0;
    int wall = 15;
    int topSpike = 1;
    int botSpike = 1;
    player_sprite = 1;
    spike_pair(topSpike,botSpike);
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
        short_delay(1000 * ((score < 18) ? (10 - (score / 2)) : 1) );
        LCD_DisplayClear();
        int upper_collision = (player_sprite <= 3) && ((3 - (player_sprite%4)) >= topSpike);
        int lower_collision = !(player_sprite <= 3) && ((player_sprite%4) >= botSpike);
        if (wall == 0 && (upper_collision || lower_collision)) {
            break;
        
        }
        if(wall < 0){
            
//            topSpike++;
//            botSpike++;
            topSpike = rand() % 4;
            botSpike = rand() % 4;
            
            if(topSpike > 3){
                topSpike = 0;
            }
            if (botSpike > 3) {
                botSpike = 0;
            }
            if (topSpike + botSpike < 2) {
                topSpike++;
                botSpike++;
            }
            
            wall = 15;
            score++;
            spike_pair(topSpike,botSpike);
        }
              
    }
    init_sprite_explosion();
    for (int i = 1; i <= 3; i++) {
        char a[] = {i, '\0'};
        if(player_sprite <= 3){
            LCD_WriteStringAtPos(a,0,1);
        } else {
            LCD_WriteStringAtPos(a,1,1);
        }
        delay(7);
    }
        
    
    LCD_WriteStringAtPos("Game over!", 0, 0);
}

int main(int argc, char** argv) {
    
    general_setup();
    LCD_WriteStringAtPos("Loading...",0,0);
    init_timers();
    init_buttons();
    while (1) {
        game_loop();
        delay(50);
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


