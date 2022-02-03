# Mini_Project_Blood_Pressure
Blood pressure by using PIC16F887 in protes and MPLAB

##Update 04/02/2022

////////////////Schematic Diagram////////////////

![test](https://user-images.githubusercontent.com/81744011/152381045-45b970a7-662f-4cf3-99d5-a8bdbf8952ff.jpg)

 
 In this project assume that button represent as pressure sensor
 
////////////////Port that use in this project////////////////

RA0 as temperature sensor (LM35)

RA3 as increase button

RA3 as decrease button

RA4 as mode selection button

RB1 as buzzer output

RC0,RC1,RD0,RD1,RD2,RD3 as LCD display 

RE3 as master clear button

////////////////How This Project Works////////////////
1. When the circuit are power on the LCD will display normal blodd presure (assume 4mmHG as normal) in this scenario.
2. As the button increase are push the value will increase, when the value are more 10 the buzzer will sound as alert and the LCD will show "HIGH".
3. As the button decrease are push the value will decrease, when the value are less than 4 the LCD will display "Low".
4. As mode selection button press it will change to temperature monitor mode.
