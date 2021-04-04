/*
 * File:   LCDscreen
 * Author: Jose Borrayo @Harding University
 * Created on January 29, 2021, 10:50 PM
 * About: the LCD screen for this project is a 16x1 LCD screen. It can work for 16x2 or even 40x4 LCD screens.
 * In the case of a 40x4 LCD screen, an extra E2 enable is needed and you have to initialize the LCD screen two times:
 * for the first two rows (ENABLE 1) and for the second two rows (ENABLE 2).
 */


#include "xc.h"
#define FCY 8000000UL //Internal oscillator frequency.
#include <libpic30.h> 
#include <p24FJ128GC006.h>

#define E1 PORTEbits.RE0
#define RS PORTEbits.RE1
#define LED PORTFbits.RF4

/*
                         Main application
 */
void blinkLED(){
    int i;
    for(i = 0;i<3;i++){
        LED = 1;
        __delay_ms(200);
        LED = 0;
        __delay_ms(200);
    }
}
             //Function for sending values to the write register of LCD
void lcd_data(unsigned char data)  
{
    PORTD = data;
    RS = 1;
    __delay_ms(2); //Small delay to turn on RS.
    E1 = 1;             		
    __delay_ms(50);
    E1 = 0;
}
             //Function for sending values to the command register of LCD
void lcd_command(unsigned char cmd)  
{
    PORTD = cmd;
    RS = 0;
    __delay_ms(2);
    E1 = 1;
    __delay_ms(50);
    E1 = 0;
}

void lcd_string(const unsigned char *str,unsigned char num){
    unsigned char i;
    for(i=0;i<num;i++){
        lcd_data(str[i]);
    }
}

void lcd_initialize(){
    __delay_ms(1500); //Wait for the LCD screen to warm up.
    
    lcd_command(0x38); //2 lines and 5x7 matrix (8 bit mode).
    __delay_ms(50);
    
    lcd_command(0x06); //Increment cursor 
    __delay_ms(20);
    
    lcd_command(0x0E); //Display on, cursor blinking.
    __delay_ms(20);
    
     lcd_command(0x01); //Clear display screen.
    __delay_ms(20);
    
    lcd_command(0x0F); //Display on, cursor blinking
    __delay_ms(20);
}

void main()
{
    TRISD = 0x00; //Set Port D pins as outputs.
    TRISE = 0x00; //Set Port E pins as outputs.
    TRISF = 0X00; //Set Port F pins as outputs.
    
    blinkLED();
    lcd_initialize();
    lcd_command(0x80);
    lcd_string("Hello World",11);
}  
