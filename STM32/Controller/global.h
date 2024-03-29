#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../Common/Include/serial.h"
#include "../Common/Include/stm32l051xx.h"

#define F_CPU 32000000L

#define CHARS_PER_LINE 16

#define MAX_16_BIT 65536.0 // 16-Bit Maximum Value
#define MAX_8_BIT 256.0 // 8-Bit Maximum Value

#define Y_MIDPOINT 2044.0
#define X_MIDPOINT 2136.0
#define MINIMUM_PERCENT_ACTIVE 0.05

#define DEBOUNCE 30

#define BUTTON_A BIT3
#define BUTTON_B BIT5
#define BUTTON_C BIT6
#define BUTTON_D BIT7

void wait_1ms(void);
void waitms (unsigned int ms);

void Delay_us(unsigned char us);
void Delay_ms(unsigned int ms);

void delay(int dly);