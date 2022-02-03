/*
 * Author: Agent_Hitman_Faris
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

void main() {
    unsigned int myADC;
    float mypos,myneg,myresult;
    int inc = 4, mode = 1;
    char str1[5],str2[10];
    TRISA = 0xFF;
    ANSEL = 0x01;  
    TRISC = 0x00;
    TRISB = 0x00;
    TRISD = 0x00; 
    OSCCON = 0x75;  
    ADCON0 = 0b11000001;
    ADCON1 = 0b10000000;
    Lcd_Init();
    Lcd_Clear();
    PORTBbits.RB1 = 1;
while(1)
{
    //temp
    ADCON0 = 0b11000001; //AN0 selected
    __delay_ms (100);
    ADCON0bits.GO_nDONE = 1;
    while(ADCON0bits.GO_nDONE);
    {
        myADC =(ADRESH<<8)+ADRESL;
        mypos = ((float)myADC *5)/10.24;
    }
    ADCON0 = 0b11000101; //AN1 selected
    __delay_ms (100);
    ADCON0bits.GO_nDONE = 1;
    while(ADCON0bits.GO_nDONE);
    {
        myADC = (ADRESH<<8)+ADRESL;
        myneg = ((float)myADC *5)/10.24;
    }
    myresult = mypos-myneg ;
    sprintf(str2, "%.1f", myresult );
    
    //button counting up
    if(PORTAbits.RA2 == 0)
    {
        __delay_ms(200);
        if(PORTAbits.RA2 == 0)
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
    //button counting down
    if (PORTAbits.RA3 == 0) 
    {
        __delay_ms(100); //to eliminate bouncing effect 
        if (PORTAbits.RA3 == 0 ) 
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
    //mode button counting up
    if (PORTAbits.RA4 == 0) 
    {
        __delay_ms(100); //to eliminate bouncing effect 
        if (PORTAbits.RA4 == 0) 
        { 
            if (mode > 2)
            {
                mode = 1;
                Lcd_Clear();
            }
            else
            {
                mode++;
            } 
        }
    }
    
    sprintf(str1,"%d",inc);
    
    //check value to blood pressure in high
    if(inc>10 && mode == 1)
    {
        Lcd_Set_Cursor(1,1); 
        Lcd_Write_String("Pressure:");
        Lcd_Write_String(str1);
        Lcd_Write_String("mmHg");
        Lcd_Write_String("       ");
        PORTBbits.RB1=0;
        Lcd_Set_Cursor(2,1); 
        Lcd_Write_String("High");
        Lcd_Write_String("       ");

    }
    //check value to blood pressure in normal
    if(inc<10 && inc > 3 && mode == 1)
    {
        Lcd_Set_Cursor(1,1); 
        Lcd_Write_String("Pressure:");
        Lcd_Write_String(str1);
        Lcd_Write_String("mmHg");
        Lcd_Write_String("       ");
        PORTBbits.RB1=1;
        Lcd_Set_Cursor(2,1); 
        Lcd_Write_String("Normal");
        Lcd_Write_String("       ");
    }
    //check value to blood pressure in low
    if (inc<3 && mode == 1)
    {
        Lcd_Set_Cursor(1,1); 
        Lcd_Write_String("Pressure:");
        Lcd_Write_String(str1);
        Lcd_Write_String("mmHg");
        PORTBbits.RB1=1;
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String("Low");
        Lcd_Write_String("       ");
    }
    
    //for temperature mode
    if(mode >= 2)
    {
        PORTBbits.RB1=1;
        inc = 4;
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("Temp: ");
        Lcd_Write_String(str2);
        Lcd_Write_Char (233);
        Lcd_Write_Char('C');        
    }

} //end while
} // end main



