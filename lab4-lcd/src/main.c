/***********************************************************************
 * 
 * Stopwatch by Timer/Counter2 on the Liquid Crystal Display (LCD)

 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2017 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 * Components:
 *   16x2 character LCD with parallel interface
 *     VSS  - GND (Power supply ground)
 *     VDD  - +5V (Positive power supply)
 *     Vo   - (Contrast)
 *     RS   - PB0 (Register Select: High for Data transfer, Low for Instruction transfer)
 *     RW   - GND (Read/Write signal: High for Read mode, Low for Write mode)
 *     E    - PB1 (Read/Write Enable: High for Read, falling edge writes data to LCD)
 *     D3:0 - NC (Data bits 3..0, Not Connected)
 *     D4   - PD4 (Data bit 4)
 *     D5   - PD5 (Data bit 5)
 *     D6   - PD6 (Data bit 3)
 *     D7   - PD7 (Data bit 2)
 *     A+K  - Back-light enabled by PB2
 * 
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <gpio.h>           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <lcd.h>            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for number conversions


/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Update stopwatch value on LCD screen when 8-bit 
 *           Timer/Counter2 overflows.
 * Returns:  none
 **********************************************************************/
int main(void)
{
     // Custom character definition using https://omerk.github.io/lcdchargen/
    uint8_t customChar[48] = {
        // address = 0
        0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000,
        // address = 1
        0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000,
        // address = 2
        0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000,
        // address = 3
        0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100,
        // address = 4
        0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110,
        // address = 5
        0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111
    };

    GPIO_mode_output(&DDRB, PB2);
    GPIO_write_high(&PORTB, PB2);

    // Initialize LCD display
    lcd_init(LCD_DISP_ON);

    // Put string(s) on LCD screen
    lcd_gotoxy(1, 0);
    lcd_puts("00:00.0");
    
    lcd_gotoxy(11, 0);
    lcd_putc('a');

    lcd_gotoxy(1, 1);
    lcd_putc('b');

    lcd_gotoxy(11, 1);
    lcd_putc('c');   

    // Copy the custom characters in memory
    lcd_command(1<<LCD_CGRAM);       // Set addressing to CGRAM (Character Generator RAM)
                                     // ie to individual lines of character patterns
    for (uint8_t i = 0; i < 48; i++)  // Copy new character patterns line by line to CGRAM
        lcd_data(customChar[i]);
    lcd_command(1<<LCD_DDRAM);       // Set addressing back to DDRAM (Display Data RAM)
                                     // ie to character codes

    // Configuration of 8-bit Timer/Counter2 for Stopwatch update
    // Set the overflow prescaler to 16 ms and enable interrupt
    TIM2_overflow_16ms();
    TIM2_overflow_interrupt_enable();

    // Configuration of 8-bit Timer/Couter0 : overflow 16ms
    // Used for the progression bar on position b
    TIM0_overflow_16ms();
    TIM0_overflow_interrupt_enable();

    // Configuration of 8-bit Timer/Counter1 : overflow 262ms
    // Used for the running text on position c
    TIM1_overflow_262ms();
    TIM1_overflow_interrupt_enable();

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines, ISRs */
    }

    // Will never reach this
    return 0;
}


/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
 * Function: Timer/Counter2 overflow interrupt
 * Purpose:  Update the stopwatch on LCD screen every sixth overflow,
 *           ie approximately every 100 ms (6 x 16 ms = 100 ms).
 **********************************************************************/
ISR(TIMER2_OVF_vect)
{
    static uint8_t no_of_overflows = 0;
    static uint8_t tenths = 0;  // Tenths of a second
    static uint8_t seconds = 0;  // Seconds
    static uint8_t minutes = 0;  // Minutes
    char string[2];             // String for converted numbers by itoa()

    no_of_overflows++;
    if (no_of_overflows >= 6)
    {
        // Do this every 6 x 16 ms = 100 ms
        no_of_overflows = 0;

        // Count tenth of seconds 0, 1, ..., 9, 0, 1, ...
        tenths++;

        if(tenths > 9){
            tenths = 0;
            seconds++;

            if(seconds > 59){
                seconds = 0;
                minutes++;

                if(minutes > 59){
                    minutes = 0;
                }

                // If minutes are only on 1 character, we want to display 01, 02, 03... and not 10, 20, 30...
                if(minutes <= 9){
                    itoa(minutes, &string[1], 10);
                    string[0]='0';
                }
                else itoa(minutes, string, 10);
                lcd_gotoxy(1, 0);
                lcd_puts(string);

            }
            
            // If seconds are only on 1 character, we want to display 01, 02, 03... and not 10, 20, 30...
            if(seconds <= 9 ){
                itoa(seconds, &string[1], 10);
                string[0]='0';
            }
            else itoa(seconds, string, 10);
            lcd_gotoxy(4, 0);
            lcd_puts(string);

            // Display the square value of the seconds at position 'a'   
            lcd_gotoxy(11,0);
            itoa(seconds*seconds, string, 10);
            lcd_puts(string);
        }

        // Display tenths
        itoa(tenths, string, 10);  // Convert decimal value to string
        lcd_gotoxy(7, 0);
        lcd_puts(string);        
    }
    // Else do nothing and exit the ISR
}

/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
 * Function: Timer/Counter0 overflow interrupt
 * Purpose:  Display and update the progression bar every 16ms
 **********************************************************************/
ISR(TIMER0_OVF_vect)
{
    static uint8_t position = 0;
    static uint8_t symbol = 0;

    lcd_gotoxy(position+1,1);
    lcd_putc(symbol);
    symbol ++;

    if(symbol > 5){
        symbol = 0;
        position ++;
    
        // Clear the line
        if(position > 9){
            position = 0;
            lcd_gotoxy(1,1);
            for (int i=0; i<=9; i++){
                lcd_gotoxy(i+1, 1);
                lcd_putc(0x00);
            }
        }
    }
}

/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
 * Function: Timer/Counter0 overflow interrupt
 * Purpose:  Display and update the progression bar every 16ms
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{
    char running_text[] = " I like Digital electronics!\n";
    static uint8_t index = 0;
    static uint8_t flag = 0b0;
    
    // Shift the variable to display every 500ms
    if(flag == 0b1){
        index++;
        if(index > 29) index = 0;
    }

    lcd_gotoxy(11,1);
    lcd_puts(running_text+index);

    flag ^= 0b1;
}