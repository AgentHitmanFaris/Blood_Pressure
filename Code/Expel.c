/*
 * Author: Sayang
 *
 * Created with love
 */
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#define _XTAL_FREQ 8000000
#define RS PORTCbits.RC0
#define EN PORTCbits.RC1

#define D4 PORTDbits.RD0
#define D5 PORTDbits.RD1
#define D6 PORTDbits.RD2
#define D7 PORTDbits.RD3


#include <stdlib.h>
#include <stdio.h> //header file for sprintf
#include <xc.h>
#include "lcd.h"

/*PWM_Initialize()
{
    PR2 = (_XTAL_FREQ/(PWM_freq*4TMR2PRESCALE)) - 1; //Makes the PWM work in 5 KHZ
    CCP1M3 = 1;
    CCP1M2 = 1; //Configure the CCP 1 module
    T2CKPS0 = 1;
    T2CKPS1 = 0;
    TMR2ON = 1; //Configure the Timer module
    TRISC2 = 0; // make port pin on C as output
}

PWM_Duty(unsigned int duty)
{
    if(duty<1023)
    {
        duty = ((float)duty/1023)*(_XTAL_FREQ/(PWM_freq*TMR2PRESCALE));
        CCP1X = duty & 1; //Store the 1st bit
        CCP1Y = duty & 2; //Store the 0th bit
        CCPR1L = duty>>2;// Store the remaining 8 bit
    }
}*/


void main() {
    int inc = 4;
    char str1[5];
    TRISA = 0xFF; 
    ANSEL = 0x00;  
    TRISC = 0x00;
    TRISB = 0x00;
    TRISD = 0x00; 
    OSCCON = 0x75;   
    Lcd_Init();
    Lcd_Clear();
    PORTBbits.RB1 = 1;
while(1)
{ 
     if(PORTAbits.RA0 == 0)
   {
       __delay_ms(200);
       if(PORTAbits.RA0 == 0)
       {           
        if(inc>=300)
         {
            inc=0;
            Lcd_Clear();
         }
          else
          {
             inc++;
          }
       }
   }

    if (PORTAbits.RA1 == 0) 
    {
    __delay_ms(100); //to eliminate bouncing effect 
    if (PORTAbits.RA1 == 0) 
    { 
        if (inc <=0)
        {
            inc = 0;
            Lcd_Clear();
        }
        else
        {
            inc--;
        } 
    }
    }


    sprintf(str1, "%d", inc); //to convert from number to string
    Lcd_Set_Cursor(1,1); 
    Lcd_Write_String("Pressure:");
    Lcd_Write_String(str1);
    Lcd_Write_String("mmHg");
    Lcd_Write_String("       ");
    
    //check value to blood pressure in high
    if(inc>10)
    {
        PORTBbits.RB1=0;
        Lcd_Set_Cursor(2,1); 
        Lcd_Write_String("High");
        Lcd_Write_String("       ");
    }
    //check value to blood pressure  in normal
    if(inc<10 && inc > 3)
    {
        PORTBbits.RB1=1;
        Lcd_Set_Cursor(2,1); 
        Lcd_Write_String("Normal");
        Lcd_Write_String("       ");
    }
    //check value to blood pressure  in low
    if (inc<3)
    {
        PORTBbits.RB1=1;
        Lcd_Set_Cursor(2,1); 
        Lcd_Write_String("Low");
        Lcd_Write_String("       ");
    
    }
} 
} // end main



