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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../Common/Include/serial.h"
#include "../Common/Include/stm32l051xx.h"

#include "lcd.h"
#include "speaker.h"
#include "adc.h"
#include "UART2.h"
#include "JDY40.h"
#include "movement.h"

#define F_CPU 32000000L

#define CHARS_PER_LINE 16

char LCD_BUFF[CHARS_PER_LINE]; // Buffer for LCD Display
char TX_BUFF[CHARS_PER_LINE+1];
char RX_BUFF[CHARS_PER_LINE+1];

#define MAX_16_BIT 65536.0 // 16-Bit Maximum Value
#define MAX_8_BIT 256.0 // 8-Bit Maximum Value

/* Define Multipliers */
#define KILO_MULTIPLIER 1000.0 // Kilo Multiplier
#define MEGA_MULTIPLIER 1000000.0 // Mega Multiplier
#define GIGA_MULTIPLIER 1000000000.0 // Giga Multiplier
#define TERA_MULTIPLIER 1000000000000.0 // Tera Multiplier

void ConfigPinsLCD(void);
void ConfigPinADC(void);

void display_rx(void);
void display_x_y(float x, float y);

void delay(int dly) {
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

void ConfigPinsUART2(void) {
	GPIOA->OSPEEDR=0xffffffff; // All pins of port A configured for very high speed! Page 201 of RM0451

	RCC->IOPENR |= BIT0; // peripheral clock enable for port A

    GPIOA->MODER = (GPIOA->MODER & ~(BIT27|BIT26)) | BIT26; // Make pin PA13 output (page 200 of RM0451, two bits used to configure: bit0=1, bit1=0))
	GPIOA->ODR |= BIT13; // 'set' pin to 1 is normal operation mode.

	GPIOA->MODER &= ~(BIT22 | BIT23); // Make PA11 Input
	// Activate pull up for pin PA11;
	GPIOA->PUPDR |= BIT22;
	GPIOA->PUPDR &= ~(BIT23);
}

void ConfigSpeakerPin(void)
{
	RCC->IOPENR |= BIT0; // peripheral clock enable for port A
    GPIOA->MODER = (GPIOA->MODER & ~(BIT17|BIT16)) | BIT16; // PA8
}

void display_rx() {
	printf("Send to LCD (16 Char Mac): ");
	fflush(stdout); // GCC peculiarities: need to flush stdout to get string out without a '\n'
	egets_echo(RX_BUFF, sizeof(RX_BUFF));

	printf("\r\n");
	for (int i=0; i<sizeof(RX_BUFF); i++) {
		if (RX_BUFF[i]=='\n') RX_BUFF[i]=0;
		if (RX_BUFF[i]=='\r') RX_BUFF[i]=0;
	}

	sprintf(LCD_BUFF, "%s", RX_BUFF);

	LCDprint(LCD_BUFF, 2, 1);
}

void display_x_y(float x, float y) {
	sprintf(LCD_BUFF, "ADC[8]=%d", (int)x);
	LCDprint(LCD_BUFF, 1, 1);

	sprintf(LCD_BUFF, "ADC[9]=%d", (int)y);
	LCDprint(LCD_BUFF, 2, 1);
}

void display_inductance(float inductance)
{
	sprintf(LCD_BUFF, "Inductance: %d", (int) inductance);
	LCDprint(LCD_BUFF, 1, 1);
}

void main(void) {
	float x, y;

	ConfigPinsUART2();
	InitUART2(9600);
	ConfigJDY40();

	ConfigPinsLCD();
	LCD_4BIT();
	ConfigPinButton();
	ConfigPinADC();
	ConfigSpeakerPin();
	InitTimer2();

	initADC();

	waitms(500); // Wait for putty to start.
	printf("\x1b[2J\x1b[1;1H"); // Clear screen using ANSI escape sequence.

	while (1) {
		x = readADC(ADC_CHSELR_CHSEL8);
		y = readADC(ADC_CHSELR_CHSEL9);

		standardized_joystick_values(&x, &y);
		while (!(GPIOA->IDR & BIT12))
		{
			//printf("Hi");
			TIM2->CR1 &= !BIT0; // enable counter enable
		}
		TIM2->CR1 |= BIT0;

		while (!(GPIOA->IDR & BIT11))
		{
			JDY_PWM_Transmission_Y(y);
		}
		ReceiveCommand();

		// Display the ADC values on the LCD
		display_x_y(x, y);

		// printf("ADC[8]=0x%04x\r\n", (int)x);
		// printf("ADC[9]=0x%04x\r\n", (int)y);

		fflush(stdout); // GCC printf wants a \n in order to send something.  If \n is not present, we fflush(stdout)
		waitms(200);
	}
}
