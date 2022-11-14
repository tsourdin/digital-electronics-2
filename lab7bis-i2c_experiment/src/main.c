/***********************************************************************
 * 
 * The I2C (TWI) bus scanner tests all addresses and detects chips and
 * modules that are connected to the SDA and SCL signals.
 * 
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2017 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/


/* Defines -----------------------------------------------------------*/
#ifndef F_CPU
# define F_CPU 16000000  // CPU frequency in Hz required for UART_BAUD_SELECT
#endif


/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <twi.h>            // I2C/TWI library for AVR-GCC
#include <uart.h>           // Peter Fleury's UART library
#include <stdlib.h>         // C library. Needed for number conversions

/* Global variables --------------------------------------------------*/
// Declaration of "air" variable with structure "Air_parameters_structure"
struct Air_parameters_structure {
    uint8_t humid_int;
    uint8_t humid_dec;
    uint8_t temp_int;
    uint8_t temp_dec;
    uint8_t checksum;
} air;

struct Time_structure {
  uint8_t hours;
  uint8_t minutes;
  uint8_t seconds;

}time_struct;

uint8_t values[8] = {
  0b11111110,
  0b11111101,
  0b11111011,
  0b11110111,
  0b11101111,
  0b11011111,
  0b10111111,
  0b01111111
};

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Use Timer/Counter1, send one I2C (TWI) address every 33 ms,
 *           and test all combinations. Send information about scanning
 *           process to UART.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    // Initialize I2C (TWI)
    twi_init();

    // Initialize USART to asynchronous, 8N1, 9600
    uart_init(UART_BAUD_SELECT(9600, F_CPU));

    // Configure 16-bit Timer/Counter1 to test one I2C address
    // Set prescaler to 262ms and enable interrupt
    TIM1_overflow_262ms();
    TIM1_overflow_interrupt_enable();

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Write random values to the first two ram modules 
    uint8_t random;
    twi_start(0x57, TWI_WRITE);
    twi_write(0);
    for(uint8_t i=0; i<10; i++){
      random = rand();
      twi_write(random);
    }
    twi_stop();

    twi_start(0x57, TWI_WRITE);
    twi_write(1);
    for(uint8_t i=0; i<10; i++){
      random = rand();
      twi_write(random);
    }
    twi_stop();

    uint8_t tab[5];
    twi_start(0x57, TWI_READ);
    twi_write(2);
    for(uint8_t i=0; i<5; i++){
      tab[i] = twi_read_ack();
    }
    twi_stop();

    twi_start(0x57, TWI_WRITE);
    for(uint8_t i=0; i<5; i++){
      twi_write(tab[i]);
    }
    twi_stop();

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:  Test one I2C Slave address from the range 8 to 119.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{ 
  char string[9];
  static int8_t index = 0;
  static uint8_t direction = 0; // 0 means index is increasing ; 1 means index is decreasing
  twi_start(0x20, TWI_WRITE);
  twi_write(values[index]);
  twi_stop();
  itoa(values[index], string, 2);
  uart_puts(string);
  uart_putc(' ');
  itoa(values[index], string, 16);
  uart_puts(string);
  uart_puts("\r\n");

  if(direction == 0){
    index++;
    if(index > 7){
      direction = 1;
      index = 6;
    }
  }else{ // if direction = 1
    index--;
    if(index < 0){
      direction = 0;
      index = 1;
    }
  }
}
