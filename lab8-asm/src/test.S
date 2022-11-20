;* Includes ------------------------------------------------------------
; Set offset for control register addresses (NEEDED FOR I/O REGISTERS)
#define __SFR_OFFSET    0
#include <avr/io.h>

.global asm_test
asm_test:
    add r24, r0
    com r26
    eor r26, r27
    mul r22, r20
    ret
