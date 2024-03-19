#include <stdio.h>
#include <stdlib.h>

#include "../Common/Include/stm32l051xx.h"
#include "../Common/Include/serial.h"
#include "UART2.h"

#define F_CPU 32000000L
#define DEF_F 15000L

#define X_STRING "_X_"
#define Y_STRING "_Y_"

// LQFP32 pinout
//                    ----------
//              VDD -|1      32|- VSS
//             PC14 -|2      31|- BOOT0
//             PC15 -|3      30|- PB7
//             NRST -|4      29|- PB6
//             VDDA -|5      28|- PB5
// LCD_RS      PA0 -|6       27|- PB4
// LCD_E       PA1 -|7       26|- PB3
// LCD_D4      PA2 -|8       25|- PA15
// LCD_D5      PA3 -|9       24|- PA14
// LCD_D6      PA4 -|10      23|- PA13
// LCD_D7      PA5 -|11      22|- PA12
//             PA6 -|12      21|- PA11
//             PA7 -|13      20|- PA10 (Reserved for RXD)
// (ADC_IN8)   PB0 -|14      19|- PA9  (Reserved for TXD)
// (ADC_IN9)   PB1 -|15      18|- PA8  (Speaker)
//             VSS -|16      17|- VDD
//                    ----------

char tx_buff[80];
char rx_buff[80];

void Delay_usJDY(unsigned char us)
{
	// For SysTick info check the STM32L0xxx Cortex-M0 programming manual page 85.
	SysTick->LOAD = (F_CPU/(1000000L/us)) - 1;  // set reload register, counter rolls over from zero, hence -1
	SysTick->VAL = 0; // load the SysTick counter
	SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk; // Enable SysTick IRQ and SysTick Timer */
	while((SysTick->CTRL & BIT16)==0); // Bit 16 is the COUNTFLAG.  True when counter rolls over from zero.
	SysTick->CTRL = 0x00; // Disable Systick counter
}

void waitmsJDY(unsigned int ms)
{
	unsigned int j;
	unsigned char k;
	for(j=0; j<ms; j++)
		for (k=0; k<4; k++) Delay_usJDY(250);
}

void SendATCommand (char * s)
{
	printf("Command: %s", s);
	GPIOA->ODR &= ~(BIT13); // 'set' pin to 0 is 'AT' mode.
	waitmsJDY(10);
	eputs2(s);
	egets2(tx_buff, sizeof(tx_buff)-1);
	GPIOA->ODR |= BIT13; // 'set' pin to 1 is normal operation mode.
	waitmsJDY(10);
	printf("Response: %s", tx_buff);
}

void SendCommand(char * s, int value)
{
	sprintf(tx_buff, "%s %d\r\n", s, value);
	printf("TX: %s", tx_buff);
	eputs2(tx_buff);
	waitmsJDY(200);
}

void ReceiveCommand(void)
{
	if(ReceivedBytes2()>0) // Something has arrived
	{
		printf("RX!\r\n");
		// egets2(rx_buff, sizeof(rx_buff)-1);
		// printf("RX: %s", rx_buff);
	}
}

void ConfigJDY40(void) {
	SendATCommand("AT+DVIDAFAF\r\n"); // Select a unique device ID from 0x0000 to 0xFFFF
	SendATCommand("AT+RFIDFFBB\r\n");

	// Check Configuration
	SendATCommand("AT+VER\r\n");
	SendATCommand("AT+BAUD\r\n");
	SendATCommand("AT+RFID\r\n");
	SendATCommand("AT+DVID\r\n");
	SendATCommand("AT+RFC\r\n");
	SendATCommand("AT+POWE\r\n");
	SendATCommand("AT+CLSS\r\n");
}

void JDY_PWM_Transmission_Y(float y_value)
{
    SendCommand(Y_STRING, y_value);
}