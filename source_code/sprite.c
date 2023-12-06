/* 
 * File:   sprite.c
 * Author: lclem
 *
 * Created on November 27, 2023, 9:46 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"
#include "config.h"
#include "interrupts.h"

/*
 * 
 */
void spike_pair(int top, int bot){
     
    if(top == 0){
        char top_large_spike[] = {0x1f,0x1f,0x1f,0x0e,0x0e,0x0e,0x04,0x04};
        LCD_WriteBytesAtPosCgram(top_large_spike, 8, posCgramChar5);
    }
    else if(top == 1){
        char top_spike[] = {0x1f,0x1f,0x0e,0x0e,0x04,0x04,0x00,0x00};
        LCD_WriteBytesAtPosCgram(top_spike, 8, posCgramChar5);
    }
    else if(top == 2){
        char top_small_spike[] = {0x1f,0x0e,0x04,0x04,0x00,0x00,0x00,0x00};
        LCD_WriteBytesAtPosCgram(top_small_spike, 8, posCgramChar5);
    }
    else if(top == 3){
        char top_tiny_spike[] = {0x0e,0x04,0x00,0x00,0x00,0x00,0x00,0x00};
        LCD_WriteBytesAtPosCgram(top_tiny_spike, 8, posCgramChar5);
    }
    else if(top == 4){
        char block[] = {0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f};
        LCD_WriteBytesAtPosCgram(block, 8, posCgramChar5);
    }
    
    if(bot == 0){
        char bot_large_spike[] = {0x04,0x04,0x0e,0x0e,0x0e,0x1f,0x1f,0x1f};
        LCD_WriteBytesAtPosCgram(bot_large_spike, 8, posCgramChar6);
    }
    else if(bot == 1){
        char bot_spike[] = {0x00,0x00,0x04,0x04,0x0e,0x0e,0x1f,0x1f};
        LCD_WriteBytesAtPosCgram(bot_spike, 8, posCgramChar6);
    }
    else if(bot == 2){
        char bot_small_spike[] = {0x00,0x00,0x00,0x00,0x04,0x0e,0x0e,0x1f};
        LCD_WriteBytesAtPosCgram(bot_small_spike, 8, posCgramChar6);
    }
    else if(bot == 3){
        char bot_tiny_spike[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x0e};
        LCD_WriteBytesAtPosCgram(bot_tiny_spike, 8, posCgramChar6);
    }
    
}

void init_sprite_player(){
     char player_top[] = {0x0c,0x0c,0x00,0x00,0x00,0x00,0x00,0x00};
     LCD_WriteBytesAtPosCgram(player_top,8, posCgramChar1);
     
     char player_midTop[] = {0x00,0x00,0x0c,0x0c,0x00,0x00,0x00,0x00};
     LCD_WriteBytesAtPosCgram(player_midTop, 8, posCgramChar2);
     
     char player_midBot[] = {0x00,0x00,0x00,0x00,0x0c,0x0c,0x00,0x00};
     LCD_WriteBytesAtPosCgram(player_midBot, 8, posCgramChar3);
     
     char player_bot[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x0c,0x0c};
     LCD_WriteBytesAtPosCgram(player_bot, 8, posCgramChar4);
}

