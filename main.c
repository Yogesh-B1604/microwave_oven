/*
 * File:   main.c
 */

#include <xc.h>
#include "clcd.h"
#include "matrix_keypad.h"


#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

static void init_config(void) {
    init_clcd();
    init_matrix_keypad();
//    ADCON1 = 0x06;
    TRISC1 = 0;
    TRISC2 = 0;
    FAN = 0;
    BUZZ = 0;
    init_timer0();
    GIE = 1;
    
}

void main(void) {
    unsigned char key;
    
    init_config();
    
    while (1) {
        clcd_print("  POWERING ON   ",LINE2(0));
        clcd_print(" MICROWAVE OVEN ",LINE3(0));
        for(int i=0;i<16;i++){
            clcd_putch(0xFF,LINE1(i));
            clcd_putch(0xFF,LINE4(i));
            __delay_ms(80);
        }
        clcd_print("                ",LINE1(0));
        clcd_print("                ",LINE2(0));
        clcd_print("                ",LINE3(0));
        clcd_print("                ",LINE4(0));
        main_menu(key);
    }
    return;
}
