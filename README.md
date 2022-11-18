# digital-electronics-2
Repository for the course labs

# Lab 1

## H2 header

### H3 header

#### Unordered list
- *italics*
- **bold**

#### Ordered list
1. *italics*
2. **bold**

#### Link to github
[github](github.com) 

#### Table 

| Column1 | Column2 | Column3 |
----------|---------|----------
| Does    | This    | Work ?  |
| It      | Seems   | To      |
| Does    | This    | Work ?  |
| It      | Seems   | To      |

#### Listing of C source code (with syntax highlighting)

```c
#include <stdio.h>

int main(int argc, char[] *argv){
  printf("Hello World\n");
}
```
# Lab2
## Pre-Lab preparation

1. Fill in the following table and enter the number of bits and numeric range for the selected data types defined by C.

   | **Data type** | **Number of bits** | **Range** | **Description** |
   | :-: | :-: | :-: | :-- |
   | `uint8_t`  | 8 | 0, 1, ..., 255 | Unsigned 8-bit integer |
   | `int8_t`   | 8 | -128, ..., 127 | Signed 8-bit integer |
   | `uint16_t` | 16 | 0, 1, ..., 65 535 | Unsigned 16-bit integer |
   | `int16_t`  | 16 | -32768, ..., 32 767 | Signed 16-bit integer |
   | `float`    | 32 | -3.4e+38, ..., 3.4e+38 | Single-precision floating-point |
   | `void`     | undefined | ... | No type |

# Lab3
## Pre-Lab preparation

Calculate the overflow times for three Timer/Counter modules that contain ATmega328P if CPU clock frequency is 16&nbsp;MHz. Complete the following table for given prescaler values. Note that, Timer/Counter2 is able to set 7 prescaler values, including 32 and 128 and other timers have only 5 prescaler values.

   | **Module** | **Number of bits** | **1** | **8** | **32** | **64** | **128** | **256** | **1024** |
   | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
   | Timer/Counter0 | 8  | 16u    | 128u    | --   | 1024u    | --    | 4096u    | 16384u    |
   | Timer/Counter1 | 16 | 4096u  | 32768u  | --   | 262144u  | --    | 1.048576 | 4.194304  |
   | Timer/Counter2 | 8  | 16u    | 128u    | 512u | 1024u    | 2048u | 4096u    | 16384u    |

## Datasheet

   | **Module** | **Operation** | **I/O register(s)** | **Bit(s)** |
   | :-: | :-- | :-: | :-- |
   | Timer/Counter0 | Prescaler<br><br>8-bit data value<br>Overflow interrupt enable | TCCR0B<br><br>TCNT0<br>TIMSK0 | CS02, CS01, CS00<br>(000: stopped, 001: 1, 010: 8, 011: 64, 100: 256, 101: 1024, 110-111: external clock source)<br>TCNT0[7:0]<br>TOIE0 (1: enable, 0: disable) |
   | Timer/Counter1 | Prescaler<br><br>16-bit data value<br>Overflow interrupt enable | TCCR1B<br><br>TCNT1H, TCNT1L<br>TIMSK1 | CS12, CS11, CS10<br>(000: stopped, 001: 1, 010: 8, 011: 64, 100: 256, 101: 1024, 110-111: external clock source)<br>TCNT1[15:0]<br>TOIE1 (1: enable, 0: disable) |
   | Timer/Counter2 | Prescaler<br><br>8-bit data value<br>Overflow interrupt enable | TCCR2B<br><br>TCNT2<br>TIMSK2 | CS22, CS21, CS20<br>(000: stopped, 001: 1, 010: 8, 011: 32, 100: 64, 101: 128, 110: 256, 111: 1024)<br>TCNT0[7:0]<br>TOIE0 (1: enable, 0: disable) |

# Lab4

1. Use schematic of the [LCD keypad shield](https://oshwlab.com/tomas.fryza/arduino-shields) and find out the connection of LCD display. What data and control signals are used? What is the meaning of these signals?

   | **LCD signal(s)** | **AVR pin(s)** | **Description** |
   | :-: | :-: | :-- |
   | RS | PB0 | Register selection signal. Selection between Instruction register (RS=0) and Data register (RS=1) |
   | R/W | Ground | R/W always at 0 : only write mode |
   | E | PB1 | Enable Signal. Trigger the write on falling edge |
   | D[3:0] | Not connected | because of 4 bit communication |
   | D[7:4] | PD7 to PD4 | Data or command to write |
   | K | Connected to a transistor controlled by PB2 | Backlight cathode ; transistor = switch (PB0 output 0 => switch off) |

2. What is the ASCII table? What are the codes/values for uppercase letters `A` to `Z`, lowercase letters `a` to `z`, and numbers `0` to `9` in this table?

   | **Char** | **Decimal** | **Hexadecimal** |
   | :-: | :-: | :-: |
   | `A` | 65 | 0x41 |
   | `B` | 66 | 0x42 |
   | `...` | | |
   | `Z` | 90 | 0x5A |
   | ... |  |  |
   | `a` | 97 | 0x61 |
   | `b` | 98 | 0x62 |
   | ... |  |  |
   | `z` | 122 | 0x7A |
   | ... |  |  |
   | `0` | 48 | 0x30 |
   | `1` | 49 | 0x31 |
   | ... |  |  |
   | `9` | 57 | 0x39 |

1. Use the online manual of LCD library (generated by [Doxygen tool](https://www.doxygen.nl/manual/docblocks.html#specialblock)) and add the input parameters and description of the following functions.

   | **Function name** | **Function parameters** | **Description** | **Example** |
   | :-- | :-- | :-- | :-- |
   | `lcd_init` | `LCD_DISP_OFF`<br>`LCD_DISP_ON`<br>`LCD_DISP_ON_CURSOR`<br>`LCD_DISP_ON_CURSOR_BLINK` | Display off&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br> display on, cursor off <br> display on, cursor on <br> display on, cursor on flashing | `lcd_init(LCD_DISP_OFF);`<br> `lcd_init(LCD_DISP_ON);` <br> `lcd_init(LCD_DISP_ON_CURSOR);` <br>`lcd_init(LCD_DISP_ON_CURSOR_BLINK);` |
   | `lcd_clrscr` | none | Clear display and set cursor to home position.  | `lcd_clrscr();` |
   | `lcd_gotoxy` | `uint8_t x` <br> `uint8_t y` | horizontal position (0 : left most postition) <br> vertical position (0: first line)| `lcd_gotoxy(5,0);` |
   | `lcd_putc` | `char c` | 	character to be displayed  | `lcd_putc('a');` |
   | `lcd_puts` | `const char * s` | string to be displayed | `lcd_puts("Hello World");`|
   | `lcd_command` | `uint8_t cmd` | instruction to send to LCD controller | `lcd_command(0);` |
   | `lcd_data` | `uint8_t data` | data byte to send t LCD controller | `lcd_data(65);` |

   # Lab5

   Use online manual of UART library and add the input parameters and description of the following functions.

   | **Function name** | **Function parameter(s)** | **Description** | **Example** |
   | :-- | :-- | :-- | :-- |
   | `uart_init` | `UART_BAUD_SELECT(9600, F_CPU)` | Initialize UART to 8N1 and set baudrate to 9600&nbsp;Bd | `uart_init(UART_BAUD_SELECT(9600, F_CPU));` |
   | `uart_getc` | none | Get received byte | `uart_getc();`
   | `uart_putc` | char data | Put data to send to ringbuffer | `uart_putc(data);`
   | `uart_puts` | char * s | Put string to the ringbuffer | `uart_puts(s);`

   # Lab 7

   | **Function name** | **Function parameters** | **Description** | **Example** |
   | :-- | :-- | :-- | :-- |
   | `twi_init` | None | Initialize TWI unit, enable internal pull-up resistors, and set SCL frequency | `twi_init();` |
   | `twi_start` | uint8_t address, uint8_t mode | Start communication on I2C/TWI bus and send address byte | `twi_start(addr, TWI_READ);` |
   | `twi_write` | uint8_t data | Send one data byte to I2C/TWI Slave device | `twi_write(data)` |
   | `twi_read_ack` | None | Read one byte from the I2C/TWI Slave device and acknowledge it with ACK, i.e. communication will continue. | `twi_read_ack()` |
   | `twi_read_nack` | None | Read one byte from the I2C/TWI Slave device and acknowledge it with NACK, i.e. communication will not continue. | `twi_read_nack()` |
   | `twi_stop` | None | Generates stop condition on I2C/TWI bus. | `twi_stop();` |

   # Lab 8

   1. Use **AVR® Instruction Set Manual** from Microchip [Online Technical Documentation](https://onlinedocs.microchip.com/), find the description of selected instructions, and complete the table.

   | **Instruction** | **Operation** | **Description** | **Cycles** |
   | :-- | :-: | :-- | :-: |
   | `add Rd, Rr` | Rd = Rd + Rr | Add two registers and store the result in Rd | 1 |
   | `andi Rd, K` | Rd = Rd and K | Logical AND between register Rd and 8-bit constant K | 1 |
   | `bld Rd, b` | Rd(b) = T | Copies the T bit in the SREG (Status Register) to bit b in register Rd | 1 |
   | `bst Rd, b` | T = Rd(b) | Stores bit b from Rd to the T bit in SREG | 1 |
   | `com Rd` | Rd = 0xFF - Rd | This instruction performs a One’s Complement of register Rd | 1 |
   | `eor Rd, Rr` | Rd = Rd XOR Rr | Performs the logical EOR between the contents of register Rd and register Rr and places the result in the destination register Rd. | 1 |
   | `mul Rd, Rr` | R1:R0 = Rd * Rr |  8-bit × 8-bit → 16-bit unsigned multiplication | 2 |
   | `pop Rd` | Rd = STACK | loads register Rd with a byte from the STACK | 2 |
   | `push Rr` | STACK = Rr |  stores the contents of register Rr on the STACK | 2 |
   | `ret` | PC(15:0) = STACK | Returns from the subroutine | 4 |
   | `rol Rd` | ... | Shifts all bits in Rd one place to the left. The C flag is shifted into bit 0 of Rd. Bit 7 is shifted into the C flag.  | 1 |
   | `ror Rd` | ... | Shifts all bits in Rd one place to the right. The C flag is shifted into bit 7 of Rd. Bit 0 is shifted into the C flag.  | 1 |