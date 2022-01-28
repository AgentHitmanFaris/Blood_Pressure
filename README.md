# Mini_Project_Blood_Pressure
Blood pressure by using PIC16F887 in protes and MPLAB

////////////////Schematic Diagram////////////////

![image](https://user-images.githubusercontent.com/81744011/151529298-081c088f-4b05-4f0c-b8dc-2b10a1b2e188.png)
 
 In this project assume that button represent as pressure sensor
 
////////////////Port that use in this project////////////////

RA0 as increase button
RA1 as decrease button
RB1 as buzzer output
RC0,RC1,RD0,RD1,RD2,RD3 as LCD display 
RE3 as master clearbutton

////////////////How This Project Works////////////////
1. When the circuit are power on the LCD will display normal blodd presure (assume 4mmHG as normal) in this scenario.
2. As the button increase are push the value will increase, when the value are more 10 the buzzer will sound as alert and the LCD will show "HIGH"
3. As the button decrease are push the value will decrease, when the value are less than 4 the LCD will display "Low"
