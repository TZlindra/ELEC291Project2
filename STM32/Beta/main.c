#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../Common/Include/stm32l051xx.h"
#include "../Common/Include/serial.h"
#include "UART2.h"
#include "lcd.h"

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
// LCD_D7      PA5 -|11      22|- PA12 (Button)
//             PA6 -|12      21|- PA11
//             PA7 -|13      20|- PA10 (Reserved for RXD)
// (ADC_IN8)   PB0 -|14      19|- PA9  (Reserved for TXD)
// (ADC_IN9)   PB1 -|15      18|- PA8  (Speaker)
//             VSS -|16      17|- VDD
//                    ----------


#define F_CPU 32000000L
#define SYSCLK 32000000L
#define DEF_F 15000L

#define MAX_16_BIT 65536.0 // 16-Bit Maximum Value
#define MAX_8_BIT 256.0 // 8-Bit Maximum Value

/* Define Multipliers */
#define KILO_MULTIPLIER 1000.0 // Kilo Multiplier
#define MEGA_MULTIPLIER 1000000.0 // Mega Multiplier
#define GIGA_MULTIPLIER 1000000000.0 // Giga Multiplier
#define TERA_MULTIPLIER 1000000000000.0 // Tera Multiplier

#define Y_MIDPOINT 2044.0
#define X_MIDPOINT 2136.0

float x = 0, y = 0;
float standardized_x = 0, standardized_y = 0;
int Timer21Count = 0;

#define CHARS_PER_LINE 16

char LCD_BUFF[CHARS_PER_LINE]; // Buffer for LCD Display
char JDY_TX_BUFF[80];
char JDY_RX_BUFF[80];

void Delay_us(unsigned char us);
void Delay_ms(unsigned int ms);
void Delay(int dly);
void ConfigPinsLCD(void);
void ConfigPinsUART2(void);
void ConfigPinButton(void);
void ConfigPinADC(void);
void ConfigPinSpeaker(void);
void ConfigJDY40(void);
void SendATCommand(char * s);
void SendCommand(char * s, int value);
void ReceiveCommand(void);
void display_x_y(float x, float y);
void display_adc(float x, float standardized_x, float y, float standardized_y);
void display_inductance(float inductance);

// Uses SysTick to Delay <us> micro-seconds.
void Delay_us(unsigned char us) {
	// For SysTick info check the STM32L0xxx Cortex-M0 programming manual page 85.
	SysTick->LOAD = (F_CPU/(1000000L/us)) - 1;  // set reload register, counter rolls over from zero, hence -1
	SysTick->VAL = 0; // load the SysTick counter
	SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk; // Enable SysTick IRQ and SysTick Timer */
	while((SysTick->CTRL & BIT16)==0); // Bit 16 is the COUNTFLAG.  True when counter rolls over from zero.
	SysTick->CTRL = 0x00; // Disable Systick counter
}

// Uses SysTick to Delay <ms> milli-seconds.
void Delay_ms(unsigned int ms) {
	unsigned int j;
	unsigned char k;
	for(j=0; j<ms; j++)
		for (k=0; k<4; k++) Delay_us(250);
}

void Delay(int dly) {
	while( dly--);
}

void ConfigPinsLCD(void) {
	RCC->IOPENR |= BIT0; // peripheral clock enable for port A

	// Make pins PA0 to PA5 outputs (page 200 of RM0451, two bits used to configure: bit0=1, bit1=0)
    GPIOA->MODER = (GPIOA->MODER & ~(BIT0|BIT1)) | BIT0; // PA0
	GPIOA->OTYPER &= ~BIT0; // Push-pull

    GPIOA->MODER = (GPIOA->MODER & ~(BIT2|BIT3)) | BIT2; // PA1
	GPIOA->OTYPER &= ~BIT1; // Push-pull

    GPIOA->MODER = (GPIOA->MODER & ~(BIT4|BIT5)) | BIT4; // PA2
	GPIOA->OTYPER &= ~BIT2; // Push-pull

    GPIOA->MODER = (GPIOA->MODER & ~(BIT6|BIT7)) | BIT6; // PA3
	GPIOA->OTYPER &= ~BIT3; // Push-pull

    GPIOA->MODER = (GPIOA->MODER & ~(BIT8|BIT9)) | BIT8; // PA4
	GPIOA->OTYPER &= ~BIT4; // Push-pull

    GPIOA->MODER = (GPIOA->MODER & ~(BIT10|BIT11)) | BIT10; // PA5
	GPIOA->OTYPER &= ~BIT5; // Push-pull
}

void ConfigPinsUART2(void) {
	GPIOA->OSPEEDR=0xffffffff; // All pins of port A configured for very high speed! Page 201 of RM0451

	RCC->IOPENR |= BIT0; // peripheral clock enable for port A

    GPIOA->MODER = (GPIOA->MODER & ~(BIT27|BIT26)) | BIT26; // Make pin PA13 output (page 200 of RM0451, two bits used to configure: bit0=1, bit1=0))
	GPIOA->ODR |= BIT13; // 'set' pin to 1 is normal operation mode.

	GPIOA->MODER &= ~(BIT22 | BIT23); // Make PA11 Input

	// Activate Pull-Up Resistor for Pin PA11
	GPIOA->PUPDR |= BIT22;
	GPIOA->PUPDR &= ~(BIT23);
}

void ConfigPinButton() {
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN; // Peripheral Clock Enable for Port A

	GPIOA->MODER &= ~(BIT24 | BIT25); // Make Pin PA12 Input

	// Activate Pull-Up Resistor for Pin PA12
	GPIOA->PUPDR |= BIT24;
	GPIOA->PUPDR &= ~(BIT25);
}

void ConfigPinADC(void) {
	// Configure the pin used for analog input: PB0 (pin 14)
	RCC->IOPENR  |= BIT1;         // peripheral clock enable for port B
	GPIOB->MODER |= (BIT0|BIT1);  // Select analog mode for PB0 (pin 14 of LQFP32 package)

	// Configure the pin used for analog input: PB1 (pin 15)
	RCC->IOPENR  |= BIT1;         // peripheral clock enable for port B
	GPIOB->MODER |= (BIT2|BIT3);  // Select analog mode for PB1 (pin 15 of LQFP32 package)
}

void ConfigPinSpeaker(void) {
	RCC->IOPENR |= BIT0; // peripheral clock enable for port A
    GPIOA->MODER = (GPIOA->MODER & ~(BIT17|BIT16)) | BIT16; // PA8
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

void SendATCommand(char * s) {
	printf("Command: %s", s);
	GPIOA->ODR &= ~(BIT13); // 'set' pin to 0 is 'AT' mode.
	Delay_ms(10);
	eputs2(s);
	egets2(JDY_TX_BUFF, sizeof(JDY_TX_BUFF)-1);
	GPIOA->ODR |= BIT13; // 'set' pin to 1 is normal operation mode.
	Delay_ms(10);
	printf("Response: %s", JDY_TX_BUFF);
}

void SendCommand(char * s, int value) {
	int count = 0;
	sprintf(JDY_TX_BUFF, "%s %d\r\n", s, value);
	printf("%s", JDY_TX_BUFF); // Print to Terminal
	eputs2(JDY_TX_BUFF);
	Delay_ms(200);
}

void ReceiveCommand(void) {
	if(ReceivedBytes2()>0) // Something has arrived
	{
		egets2(JDY_RX_BUFF, sizeof(JDY_RX_BUFF)-1);
		printf("RX: %s", JDY_RX_BUFF);
	}
}

void display_x_y(float x, float y) {
	sprintf(LCD_BUFF, "X DIR: %.2f", x);
	LCDprint(LCD_BUFF, 1, 1);

	sprintf(LCD_BUFF, "Y DIR: %.2f", y);
	LCDprint(LCD_BUFF, 2, 1);
}

void display_adc(float x, float standardized_x, float y, float standardized_y) {
	sprintf(LCD_BUFF, "X:%.1f = %.1f", x, standardized_x);
	printf("%s\r\n", LCD_BUFF);
	LCDprint(LCD_BUFF, 1, 1);

	sprintf(LCD_BUFF, "Y:%.1f = %.1f", y, standardized_y);
	printf("%s\r\n", LCD_BUFF);
	LCDprint(LCD_BUFF, 2, 1);
}

void display_inductance(float inductance) {
	sprintf(LCD_BUFF, "Inductance: %d", (int) inductance);
	LCDprint(LCD_BUFF, 1, 1);
}

int main(void) {
    int cnt = 0;

	ConfigPinsUART2();
	initUART2(9600);
	ConfigJDY40();

	ConfigPinsLCD();
	LCD_4BIT();

	Delay_ms(1000); // Give putty some time to start.

	cnt = 0;
	while (1) {
		if ((GPIOA->IDR&BIT11)==0) {
			SendCommand("CURR:", cnt);
			display_inductance(cnt);
			cnt++;
		}
		ReceiveCommand();
	}
}
