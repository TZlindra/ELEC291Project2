#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Common/Include/stm32l051xx.h"
#include "../Common/Include/serial.h"
#include "UART2.h"
#include "JDY40.h"

// LQFP32 pinout
//                    ----------
//              VDD -|1      32|- VSS
//             PC14 -|2      31|- BOOT0
//             PC15 -|3      30|- PB7
//             NRST -|4      29|- PB6
//             VDDA -|5      28|- PB5
// LCD_RS      PA0 -|6       27|- PB4
// LCD_E       PA1 -|7       26|- PB3  (Toggle Pin)
// LCD_D4      PA2 -|8       25|- PA15 (USART2 RX)
// LCD_D5      PA3 -|9       24|- PA14 (USART2 TX)
// LCD_D6      PA4 -|10      23|- PA13
// LCD_D7      PA5 -|11      22|- PA12 (Button)
//             PA6 -|12      21|- PA11
//             PA7 -|13      20|- PA10 (Reserved for RXD)
// (ADC_IN8)   PB0 -|14      19|- PA9  (Reserved for TXD)
// (ADC_IN9)   PB1 -|15      18|- PA8  (Speaker)
//             VSS -|16      17|- VDD
//                    ----------

char TX_BUFF[80];
char RX_BUFF[80];
char *const RX_CMD = " I\r\n";

void InitTimer21(void) {
	RCC->APB2ENR |= RCC_APB2ENR_TIM21EN;  // turn on clock for timer21 (UM: page 188)
	TIM21->ARR = F_CPU / TICK_FREQ_TIM21 - 1; // set the auto-reload value

    NVIC_EnableIRQ(TIM21_IRQn); // Enable Timer 21 Interrupts in NVIC
	TIM21->CR1 |= BIT4;      // Downcounting
	TIM21->CR1 |= BIT0;      // enable counting
	TIM21->DIER |= BIT0;     // enable update event (reload event) interrupt
	__enable_irq();
}

void JDS_Delay_us(unsigned char us) {
	// For SysTick info check the STM32L0xxx Cortex-M0 programming manual page 85.
	SysTick->LOAD = (F_CPU/(1000000L/us)) - 1;  // set reload register, counter rolls over from zero, hence -1
	SysTick->VAL = 0; // load the SysTick counter
	SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk; // Enable SysTick IRQ and SysTick Timer */
	while((SysTick->CTRL & BIT16)==0); // Bit 16 is the COUNTFLAG.  True when counter rolls over from zero.
	SysTick->CTRL = 0x00; // Disable Systick counter
}

void JDY_Delay_ms(unsigned int ms) {
	unsigned int j;
	unsigned char k;
	for(j=0; j<ms; j++)
		for (k=0; k<4; k++) JDS_Delay_us(250);
}

void SendATCommand(char * s) {
	printf("Command: %s", s);
	GPIOA->ODR &= ~(BIT13); // 'set' pin to 0 is 'AT' mode.
	JDY_Delay_ms(10);
	eputs2(s);
	egets2(TX_BUFF, sizeof(TX_BUFF)-1);
	GPIOA->ODR |= BIT13; // 'set' pin to 1 is normal operation mode.
	JDY_Delay_ms(10);
	printf("Response: %s", TX_BUFF);
}

void SendCommand(char * s, int value) {
	sprintf(TX_BUFF, "%s %d\r\n", s, value);
	eputs2(TX_BUFF);
	JDY_Delay_ms(200); // Delay For Response
}

void ReceiveCommand(void) {
	if (ReceivedBytes2() > 0) egets2(RX_BUFF, sizeof(RX_BUFF)-1);
}

int ReceiveInductance(int inductance) {
	int timeout_count = 0;
	int rx = -1;
	eputs2(RX_CMD);

	while (1) {
		timeout_count++;

		if (ReceivedBytes2() > 0) {
			egets2(RX_BUFF, sizeof(RX_BUFF)-1);

			// No Printing in ISRs
			// printf("Length of RX_BUFF: %d\r\n", strlen(RX_BUFF));
			// printf("RX_BUFF: %.*s\r\n", strlen(RX_BUFF)-1, RX_BUFF); // Print String Up to Last Character

			if (strlen(RX_BUFF) == 3) {
				rx = atoi(RX_BUFF);
				// No Printing in ISRs
				// printf("Inductance: %d\r\n", rx);
				break;
			}
		}

		if (timeout_count > 1000) break;
	}

	if (rx != -1) return rx;
	else return inductance;
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

void Update_X_Y(int x_value, int y_value) {
	sprintf(TX_BUFF, " X:%d Y:%d\r\n", x_value, y_value);
	printf("%s", TX_BUFF);
}

void Send_X_Y(void) {
	// No Printing in ISRs
	// printf("TX_BUFF: %s\r\n", TX_BUFF);
	eputs2(TX_BUFF);
}
