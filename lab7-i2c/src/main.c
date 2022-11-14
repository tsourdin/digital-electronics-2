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
#include <time.h>

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
    // Set prescaler to 33 ms and enable interrupt
    // For first part : 33ms
    // TIM1_overflow_33ms();
    // For second part (temperature measurement) : 1s
    TIM1_overflow_1s();
    TIM1_overflow_interrupt_enable();

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Put strings to ringbuffer for transmitting via UART
    uart_puts("Scan I2C bus for devices:\r\n");

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}

// Read seconds from RTC DS3231 chip
uint8_t rtc_read_seconds(){
  uint8_t seconds;
  if(twi_start(0x68,TWI_WRITE)==0){
    twi_write(0x00);
    seconds = twi_read_nack();
  }
  return seconds;
}

// Read minutes from RTC DS3231 chip
uint8_t rtc_read_minutes(){
  uint8_t minutes;
  if(twi_start(0x68,TWI_WRITE)==0){
    twi_write(0x00);
    minutes = twi_read_nack();
  }
  return minutes;
}

// Read hours from RTC DS3231 chip
uint8_t rtc_read_hours(){
  uint8_t hours;
  if(twi_start(0x68,TWI_WRITE)==0){
    twi_write(0x00);
    hours = twi_read_nack();
  }
  return hours;
}

// Write seconds to RTC DS3231 chip
void rtc_write_seconds(){
  time_t rawtime;
  struct tm * timeinfo;
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  if(twi_start(0x68,TWI_WRITE)==0){
    twi_write(0x00);
    twi_write(timeinfo->tm_sec); // Not sure at all of this
  }
}

// Write minutes to RTC DS3231 chip
void rtc_write_seconds(){
  time_t rawtime;
  struct tm * timeinfo;
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  if(twi_start(0x68,TWI_WRITE)==0){
    twi_write(0x01);
    twi_write(timeinfo->tm_min); // Not sure at all of this
  }
}

// Write hours to RTC DS3231 chip
void rtc_write_seconds(){
  time_t rawtime;
  struct tm * timeinfo;
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  if(twi_start(0x68,TWI_WRITE)==0){
    twi_write(0x02);
    twi_write(timeinfo->tm_hour); // Not sure at all of this
  }
}

/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:  Test one I2C Slave address from the range 8 to 119.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{   
  /*
  static uint8_t addr = 8;  // I2C Slave address
  uint8_t ack;              // ACK response from Slave
  char string[3];           // String for converting numbers by itoa()

  // Start communication, transmit I2C Slave address, get result,
  // and Stop communication
  if(addr<120)
  {
    ack = twi_start(addr, TWI_WRITE);
    itoa(addr, string, 10);
    uart_puts("Testing address :");
    uart_puts(string);
    
    twi_stop();

    // Test ACK/NACK value obtained from I2C bus and send info to UART
    if(ack==0)
    {
      uart_puts(" OK!");
    }
    uart_puts("\r\n");
    addr++;
  }
  */
  /*
  char string[3];

  if(twi_start(92, TWI_WRITE)==0){
    twi_write(0);
    twi_stop();
    twi_start(92, TWI_READ);
    air.humid_int = twi_read_ack();
    air.humid_dec = twi_read_ack();
    air.temp_int = twi_read_ack();
    air.temp_dec = twi_read_nack();
  }
  else uart_puts("Device not connected !");

  uart_puts("Humidity : ");
  itoa(air.humid_int,string,10);
  uart_puts(string);
  uart_putc('.');
  itoa(air.humid_dec,string,10);
  uart_puts(string);
  uart_puts("\t");

  uart_puts("Air temperature : ");
  itoa(air.temp_int,string,10);
  uart_puts(string);
  uart_putc('.');
  itoa(air.temp_dec,string,10);
  uart_puts(string);
  uart_puts("C \r\n");
  */

  char string[3];
  if(twi_start(0x68,TWI_WRITE)==0){
    twi_write(0x00);
    twi_stop();
    twi_start(0x68, TWI_READ);
    time_struct.seconds = twi_read_ack();
    time_struct.minutes = twi_read_ack();
    time_struct.hours = twi_read_nack();
  }
  
}
