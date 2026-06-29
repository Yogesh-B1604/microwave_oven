/*
 * File:   main_menu.c
 * Author: yogeshkumar
 *
 * Created on June 26, 2026, 12:43 PM
 */


#include <xc.h>
#include "clcd.h"
#include "matrix_keypad.h"
int min,flag2 = 0;
int min = 0,sec = 0;
volatile int flag = 0,field_flag=0;
volatile unsigned char blink = 0;

void main_menu(unsigned char key){
    
    while(1){
    clcd_print(" 1.MICRO        ",LINE1(0));
    clcd_print(" 2.GRILL        ",LINE2(0));
    clcd_print(" 3.CONVECTION   ",LINE3(0));
    clcd_print(" 4.START        ",LINE4(0));
    key = read_matrix_keypad(LEVEL);
    switch (key)  
        {
            case 1 : clcd_print("                ",LINE1(0));
                     clcd_print("  POWER = 900W  ",LINE2(0));
                     clcd_print("                ",LINE3(0));
                     clcd_print("                ",LINE4(0));
                     __delay_ms(500);
                     set_time(key);
                     break;
                
            case 2 : set_time(key);
                     break;
                
            case 3 : set_temp(key);
                     break;
                
            case 4 : sec = 30;
                     run_mode(key);
                     break;
                     
            default: break;
                
        }
    }
}
void set_time(unsigned char key){
    int first_time = 1,digit=0;
    field_flag = 1;
    while(1){
        clcd_print("SET TIME <MM:SS>",LINE1(0));
        clcd_print("TIME: ",LINE2(0));
        clcd_print("                ",LINE3(0));
        clcd_print("*:CLEAR  #:ENTER",LINE4(0));
        key = read_matrix_keypad(LEVEL);
        clcd_putch(':',LINE2(8));
        clcd_print("     ",LINE2(11));
        if(field_flag == 1)
        {
            if(blink)
                {
                    clcd_print("  ", LINE2(6));
                }
            else
            {
                clcd_putch((min/10)+'0',LINE2(6));
                clcd_putch((min%10)+'0',LINE2(7));
            }
                clcd_putch((sec/10)+'0',LINE2(9));
                clcd_putch((sec%10)+'0',LINE2(10));
        }
        else if(field_flag == 2)
        {
                clcd_putch((min/10)+'0',LINE2(6));
                clcd_putch((min%10)+'0',LINE2(7));
                if(blink)
                {
                    clcd_print("  ", LINE2(9));
                }
                else
                {
                    clcd_putch((sec/10)+'0',LINE2(9));
                    clcd_putch((sec%10)+'0',LINE2(10));
                }
        }
        
        if(key >= 0 && key <= 9){
            if(digit==0){
                if(first_time){
                    first_time = 0;
                    min = key%10;
                }
                else{
                    first_time = 1;
                    min = (min*10)+ key;
                    digit = 1;
                    field_flag = 2;
                }
            }
            else{
                if(first_time){
                    first_time = 0;
                    sec = key%10; 
                }
                else{
                    first_time = 1;
                    sec = (sec*10)+ key;
                    digit = 0;
                    field_flag = 1;
                }
            }      
        }
        else if(key == '#'){
//            if(sec==0 && min == 0){
//                return;
//            }
            run_mode(key);
            return ;
        }
        else if(key == '*'){
            sec = 0;
            min = 0;
            first_time = 0;
            
        }
    }
}
void run_mode(unsigned char key){
    flag = 1;
    FAN = 1;
    while(1){
        clcd_print("  TIME = ",LINE1(0));
        clcd_print("4.START(add 30s)",LINE2(0));
        clcd_print("5.PAUSE/RESUME  ",LINE3(0));
        clcd_print("6.STOP          ",LINE4(0));
        key = read_matrix_keypad(LEVEL);
        if(key == 4){
            sec = sec + 30;
            if(sec > 60){
                sec = sec - 60;
                min++;
            }
        }
        else if(key == 5){
            if(flag){
                FAN = 0;
                flag = 0;
            }
            else{
                flag = 1;
                FAN = 1;
            }
        }
        else if(key == 6 ){
            FAN = 0;
            sec = 0;
            min = 0;
            flag = 0;
            return;
        }
            clcd_putch((min/10)+'0',LINE1(9));
            clcd_putch((min%10)+'0',LINE1(10));
            clcd_putch(':',LINE1(11));
            clcd_putch((sec/10)+'0',LINE1(12));
            clcd_putch((sec%10)+'0',LINE1(13));
            clcd_print("  ",LINE1(14));
            if(sec == 0 && min == 0){
                clcd_print("                ",LINE1(0));
                clcd_print("     TIME UP    ",LINE2(0));
                clcd_print("Enjoy your Meal!",LINE3(0));
                clcd_print("                ",LINE4(0));
                flag = 0;
                FAN = 0;
                BUZZ = 1;
                __delay_ms(1000);
                BUZZ = 0;
                return;   
            }
    }
    
}
void set_temp(unsigned char key){
    int temp=0;
    char digit=0;
    while(1){
        clcd_print("SET TEMP <",LINE1(0));
        clcd_putch(0xDF, LINE1(10));
        clcd_print("c>    ",LINE1(11));
        clcd_print("TEMP: ",LINE2(0));
        clcd_print("                ",LINE3(0));
        clcd_print("*:CLEAR  #:ENTER",LINE4(0));
        clcd_putch((temp/100)+'0', LINE2(6));
        clcd_putch(((temp/10)%10)+'0', LINE2(7));
        clcd_putch((temp%10)+'0', LINE2(8));
        clcd_putch(0xDF, LINE2(9));
        clcd_print("c     ",LINE2(10));
        key = read_matrix_keypad(LEVEL);
        if(key >= 0 && key <= 9)
        {
            if(digit == 0)
            {
                temp = key;
                digit = 1;
            }
            else if(digit == 1)
            {
                temp = (temp * 10) + key;
                digit = 2;
            }
            else if(digit == 2)
            {
                temp = temp * 10 + key;

                if(temp > 180)
                    temp = 180;

                digit = 0;        
            }
        }
        if(key == '*'){
            temp = 0;
            digit = 0;
        }
        else if(key == '#'){
            sec = 60;
            flag = 1;
            FAN = 1;
            while(1){
                clcd_print("                ",LINE1(0));
                clcd_print("  Pre-Heating   ",LINE2(0));
                clcd_print("TIME LEFT : ",LINE3(0));
                clcd_print("                ",LINE4(0));
                clcd_putch((sec/10)+'0',LINE3(12));
                clcd_putch((sec%10)+'0',LINE3(13));
                clcd_print("s ",LINE3(14));
                if(sec == 0){
                    FAN = 0;
                    flag = 0;
                    set_time(key);
                    return ; 
                }
            }
        }
        
    }
    
}
