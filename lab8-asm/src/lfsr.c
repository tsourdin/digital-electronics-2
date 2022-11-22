#include <avr/io.h>

uint8_t lfsr4_fibonacci_c(uint8_t value){
    uint8_t temp0;
    uint8_t temp1;
    // First solution
    temp0 = (value & (1 << 3)) >> 3;
    temp1 = (value & (1 << 2)) >> 2;
    value = value << 1;
    if(temp0==temp1) value += 1;
    value &= 0x0F;
    return value;
}