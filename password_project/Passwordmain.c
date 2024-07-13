 //kpm_lcd_readnum.c
#include <LPC21xx.h>
 #include <stdlib.h>
#include "lcd.h"
#include "lcd_defines.h"
#include "kpm.h"
#include "delay.h"
u32 num;
u32 KPM_ReadNum(void);
void checkPassword(int num)
{
  int num1=2222,i;
 
 if(num==num1)
   {
	for(i=0;i<=16;i++)
	{
	 CmdLCD(GOTO_LINE1_POS0);
   StrLCD("Correct Password");
   CmdLCD(GOTO_LINE2_POS0+i);
   StrLCD("DOOR UNLOCKED");
   IOSET0=1<<4;
   delay_ms(100);
   
   CmdLCD(CLEAR_LCD);
	}
  IOCLR0=1<<4;
	//while(1);  
   }
 else
 {
	 for(i=0;i<=16;i++)
	{
   CmdLCD(GOTO_LINE1_POS0);
   StrLCD("Invaild Password");
		 CmdLCD(GOTO_LINE2_POS0+i);
   StrLCD("TRY AGAIN!!!");
     IOSET0=1<<5;
   delay_ms(100);
  
   CmdLCD(CLEAR_LCD);
	}
	 IOCLR0=1<<5;
  }
   //return num;
}

int main()
{
        IODIR0|=1<<4|1<<5;// IODIR0|=1<<15;
        InitLCD();
        InitKPM();
	     //IOSET0=1<<15;//delay_s(2);
   
  
        while(1)
        {
					
    CmdLCD(GOTO_LINE1_POS0);
        StrLCD("Enter Password:");

                num=KPM_ReadNum();
                CmdLCD(GOTO_LINE2_POS0);
                StrLCD("   ");
                CmdLCD(GOTO_LINE2_POS0);
        //      U32LCD(checkPassword(num));
                U32LCD(num);
                checkPassword(num);
        }
}
u32 KPM_ReadNum(void)
{
    u32 res = 0;
    u8 keyV;
    int numDigits=0 ; // Track the number of digits entered
     
	 while(numDigits <4)
    {
        keyV = KeyScan();
        while(ColScan() == 0);

        if(keyV != '=' && keyV != '+'&& keyV != '-')
        {
            if(keyV >= '0' && keyV <= '9') // Ensure key is a digit
            {
                res = (res * 10) + (keyV - '0');
                numDigits++; // Increment digit count
                CmdLCD(GOTO_LINE2_POS0);
                U32LCD(res);
            }
        }
        else if (keyV == '+')
        {
            if(numDigits > 0)
            {
                res /= 10;
                numDigits--; // Decrement digit count
                CmdLCD(GOTO_LINE2_POS0);
                StrLCD("          "); // Clear the previous number display
                CmdLCD(GOTO_LINE2_POS0);
                if(res > 0)
                {
                    U32LCD(res);
                }
                else
                {
                    StrLCD(" ");
                }
            }
        }
				 else if (keyV == '-')
				 {
						while(numDigits)
				           if(numDigits > 0)
            {
                res /= 10;
                numDigits--; // Decrement digit count
                CmdLCD(GOTO_LINE2_POS0);
                StrLCD("          "); // Clear the previous number display
                CmdLCD(GOTO_LINE2_POS0);
                if(res > 0)
                {
                    U32LCD(res);
                }
                else
                {
                    StrLCD(" ");
                }
            }
				 }
        else
        {
            break; // '=' key pressed, end input
        }
				
    }
    return res;
}
