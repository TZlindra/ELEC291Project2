/* Include Headers */
#include <EFM8LB1.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_16_BIT 65536.0 // 16-Bit Maximum Value
#define MAX_8_BIT 256.0 // 8-Bit Maximum Value

/* Clock Frequency and Baud Rate */
#define SYSCLK    72000000L // SYSCLK Frequency in Hz
#define BAUDRATE    115200L // Baudrate of UART in BPS
#define SARCLK 18000000L // SARCLK Frequency in Hz

/* Function Prototypes */
void Timer3us(unsigned char us);
void waitms(unsigned int ms);
