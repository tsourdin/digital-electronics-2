/***********************************************************************
 * 
 * Blink a LED in Arduino-style and use function from the delay library.
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2022 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/


/* Defines -----------------------------------------------------------*/
#define LED_GREEN PB5   // PB5 is AVR pin where green on-board LED 
                        // is connected
#define DIT_DELAY           250     // Delay in milliseconds for a DIT (dot)
#define DAH_DELAY           750     // Delay in millisecond for a DAH (comma)
#define INTRA_CHAR_DELAY    250     // Delay between DIT and DAH
#define INTER_CHAR_DELAY    750     // Delay between two chars
#define WORD_SPACE_DELAY    1750    // Delay between two words

#ifndef F_CPU
# define F_CPU 16000000 // CPU frequency in Hz required for delay funcs
#endif

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>     // AVR device-specific IO definitions
#include <util/delay.h> // Functions for busy-wait delay loops


// -----
// This part is needed to use Arduino functions but also physical pin
// names. We are using Arduino-style just to simplify the first lab.
#include "Arduino.h"
#define PB5 13          // In Arduino world, PB5 is called "13"
// -----


/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function:    dit(uint8_t pin)
 * Purpose:     write a dit (dot) to the pin specified as a parameter
 * Returns:     none
 **********************************************************************/
void dit(uint8_t pin){
    digitalWrite(LED_GREEN, HIGH);
    _delay_ms(DIT_DELAY);
    digitalWrite(LED_GREEN, LOW);
}

/**********************************************************************
 * Function:    dah(uint8_t pin)
 * Purpose:     write a dah (comma) to the pin specified as a parameter
 * Returns:     none
 **********************************************************************/
void dah(uint8_t pin){
    digitalWrite(LED_GREEN, HIGH);
    _delay_ms(DAH_DELAY);
    digitalWrite(LED_GREEN, LOW);
}


/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Toggle one LED and use delay library.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    // Set pin where on-board LED is connected as output
    pinMode(LED_GREEN, OUTPUT);

    // Infinite loop
    while (1)
    {
        // PARIS i morse

        // Generate a lettre `P` Morse code : .--.
        dit(LED_GREEN);
        _delay_ms(INTRA_CHAR_DELAY);
        dah(LED_GREEN);
        _delay_ms(INTRA_CHAR_DELAY);
        dah(LED_GREEN);
        _delay_ms(INTRA_CHAR_DELAY);
        dit(LED_GREEN);
        _delay_ms(INTER_CHAR_DELAY);
        
        // Generate a lettre `A` Morse code : .-
        dit(LED_GREEN);
        _delay_ms(INTRA_CHAR_DELAY);
        dah(LED_GREEN);
        _delay_ms(INTER_CHAR_DELAY);

        // Generate a lettre `R` Morse code : .-.
        dit(LED_GREEN);
        _delay_ms(INTRA_CHAR_DELAY);
        dah(LED_GREEN);
        _delay_ms(INTRA_CHAR_DELAY);
        dit(LED_GREEN);
        _delay_ms(INTER_CHAR_DELAY);

        // Generate a lettre `I` Morse code : ..
        dit(LED_GREEN);
        _delay_ms(INTRA_CHAR_DELAY);
        dit(LED_GREEN);
        _delay_ms(INTER_CHAR_DELAY);

        // Generate a lettre `S` Morse code : ...
        dit(LED_GREEN);
        _delay_ms(INTRA_CHAR_DELAY);
        dit(LED_GREEN);
        _delay_ms(INTRA_CHAR_DELAY);
        dit(LED_GREEN);
        _delay_ms(WORD_SPACE_DELAY);
    }

    // Will never reach this
    return 0;
}
