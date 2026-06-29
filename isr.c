#include <xc.h>
#include "clcd.h"
extern int min,sec;
extern volatile int flag;
extern volatile unsigned char blink;

void __interrupt() isr(void)
{
    static unsigned int count = 0;
    
    if (TMR0IF == 1)
    {
        /* TMR0 Register valur + 6 (offset count to get 250 ticks) + 2 Inst Cycle */
        TMR0 = TMR0 + 6 + 2;
        
        if (++count == 20000)
        {
            count = 0;
            if(flag == 1){
                if(sec == 0){
                    if(min == 0)
                        flag = 0;
                    else{
                        min--;
                        sec = 59;
                    }
                }
                else
                    sec--;
            }
            blink ^= 1;
            
           
        }
        
        TMR0IF = 0;
    }
}