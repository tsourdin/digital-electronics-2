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