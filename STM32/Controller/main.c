// LQFP32 pinout
//                    ----------
//              VDD -|1      32|- VSS
//             PC14 -|2      31|- BOOT0
//             PC15 -|3      30|- PB7 (Button D)
//             NRST -|4      29|- PB6 (Button C)
//             VDDA -|5      28|- PB5 (Button B)
// LCD_RS      PA0 -|6       27|- PB4
// LCD_E       PA1 -|7       26|- PB3 (Button A)
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
#include "frequency_calc.h"
#include "passcode.h"

#define CHARS_PER_LINE 16

#define MAX_16_BIT 65536.0 // 16-Bit Maximum Value
#define MAX_8_BIT 256.0 // 8-Bit Maximum Value

#define Y_MIDPOINT 2044.0
#define X_MIDPOINT 2136.0

char LCD_BUFF[CHARS_PER_LINE]; // Buffer for LCD Display

volatile int Timer2Count = 0;
volatile int TX21Count = 0;
volatile int RX21Count = 0;
volatile float SpeakerRatio = 5;

volatile int inductance = 0;
volatile int SpeakerEnabled = 0;

float x = 0, y = 0;
int standardized_x = 0, standardized_y = 0;

void delay(int dly);

void ConfigPinsLCD(void);
void ConfigPinButton(void);
void ConfigPinADC(void);
void ConfigPinsUART2(void);
void ConfigPinSpeaker(void);
void ConfigPasscodeButtonPins(void);

void display_x_y(int x, int y);
void display_adc(float x, int standardized_x, float y, int standardized_y);
void display_inductance(float inductance);

// Interrupt service routines are the same as normal
// subroutines (or C funtions) in Cortex-M microcontrollers.
// The following should happen at a rate of 1kHz.
// The following function is associated with the TIM2 interrupt
// via the interrupt vector table defined in startup.c
void TIM2_Handler(void) {
	TIM2->SR &= ~BIT0; // Clear Update Interrupt Flag
	Timer2Count++;
	if ((Timer2Count >= SpeakerRatio) && (SpeakerEnabled == 1)) {
		TIM2->CCR1 = (TIM2->CCR1+16)&0xFF;
		Timer2Count = 0;
		ToggleSpeaker(); // Toggle Speaker
	}
}

void TIM21_Handler(void) {
	TIM21->SR &= ~BIT0; // Clear Update Interrupt Flag
	TX21Count++;
	if (TX21Count > 500) {
		TX21Count = 0;
		TX_XY();
	}
}

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
	RCC->IOPENR |= RCC_IOPENR_GPIOBEN; // Peripheral Clock Enable for Port B
	GPIOB->MODER |= (BIT0|BIT1);  // Select analog mode for PB0 (pin 14 of LQFP32 package)

	// Configure the pin used for analog input: PB1 (pin 15)
	RCC->IOPENR  |= BIT1;         // peripheral clock enable for port B
	GPIOB->MODER |= (BIT2|BIT3);  // Select analog mode for PB1 (pin 15 of LQFP32 package)
}

void ConfigPinsUART2(void) {
	GPIOA->OSPEEDR = 0xFFFFFFFF; // All pins of port A configured for very high speed! Page 201 of RM0451

	RCC->IOPENR |= RCC_IOPENR_GPIOAEN; // Enable clock for GPIO Port A

    GPIOA->MODER = (GPIOA->MODER & ~(BIT27|BIT26)) | BIT26; // Make pin PA13 output (page 200 of RM0451, two bits used to configure: bit0=1, bit1=0))
	GPIOA->ODR |= BIT13; // 'set' pin to 1 is normal operation mode.

	GPIOA->MODER &= ~(BIT22 | BIT23); // Make PA11 Input

	// Activate Pull-Up Resistor for Pin PA11
	GPIOA->PUPDR |= BIT22;
	GPIOA->PUPDR &= ~(BIT23);
}

void ConfigPinSpeaker(void) {
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN; // Enable clock for GPIO Port A
    GPIOA->MODER = (GPIOA->MODER & ~(BIT17|BIT16)) | BIT16; // PA8
}

void ConfigPasscodeButtonPins(void) {
    RCC->IOPENR |= RCC_IOPENR_GPIOBEN; // Peripheral Clock Enable for Port B
    GPIOB->MODER &= ~(BIT14 | BIT15); // Make Pin PB7 Input
	GPIOB->PUPDR |= BIT14;
	GPIOB->PUPDR &= ~(BIT15);

    GPIOB->MODER &= ~(BIT12 | BIT13); // Make Pin PB6 Input
	GPIOB->PUPDR |= BIT12;
	GPIOB->PUPDR &= ~(BIT13);

    GPIOB->MODER &= ~(BIT10 | BIT11); // Make Pin PB5 Input
	GPIOB->PUPDR |= BIT10;
	GPIOB->PUPDR &= ~(BIT11);

    GPIOB->MODER &= ~(BIT6 | BIT7); // Make Pin PB3 Input
	GPIOB->PUPDR |= BIT6;
	GPIOB->PUPDR &= ~(BIT7);
}

int isTestButtonPressed(void) {
	return !(GPIOA->IDR & BIT12);
}

void display_x_y(int x, int y) {
	sprintf(LCD_BUFF, "MOV(%d, %d)", x, y);
	LCDprint(LCD_BUFF, 2, 1);
}

void display_adc(float x, int standardized_x, float y, int standardized_y) {
	sprintf(LCD_BUFF, "X:%.1f = %d", x, standardized_x);
	printf("%s\r\n", LCD_BUFF);
	LCDprint(LCD_BUFF, 1, 1);

	sprintf(LCD_BUFF, "Y:%.1f = %d", y, standardized_y);
	printf("%s\r\n", LCD_BUFF);
	LCDprint(LCD_BUFF, 2, 1);
}

void display_inductance(float inductance) {
	sprintf(LCD_BUFF, "I: %d", (int) inductance);
	LCDprint(LCD_BUFF, 1, 1);
}

void main(void) {
	ConfigPinsUART2();
	InitUART2(9600);
	ConfigJDY40();

	ConfigPinsLCD();
	LCD_4BIT();
	ConfigPinButton();
	ConfigPinADC();
	ConfigPinSpeaker();
	ConfigPasscodeButtonPins();

	InitTimer2();
	InitTimer21();

	initADC();

	waitms(500); // Wait for putty to start.
	printf("\x1b[2J\x1b[1;1H"); // Clear screen using ANSI escape sequence.

    checkPasscode();

	while (1) {
		x = -1*(readADC(ADC_CHSELR_CHSEL8)-X_MIDPOINT);
		y = -1*(readADC(ADC_CHSELR_CHSEL9)-Y_MIDPOINT);

		standardized_x = standardize_x(x);
		standardized_y = standardize_y(y);
		Update_XY(standardized_x, standardized_y);
		RX_I(); // Receive Inductance Value

		// display_buffs();
		inductance = Update_I(inductance);
		// printf("I: %d\r\n", inductance);

		// if (isTestButtonPressed()) SpeakerRatio = SetSpeakerFreq(SpeakerRatio);

		if (inductance >= 500) {
			SpeakerEnabled = 1;
			SpeakerRatio = SetSpeakerFreq(inductance, SpeakerRatio);
		} else {
			SpeakerEnabled = 0;
		}

		// Display the ADC values on the LCD

		display_inductance(inductance);
		display_x_y(standardized_x, standardized_y);

		fflush(stdout); // GCC printf wants a \n in order to send something.  If \n is not present, we fflush(stdout)
		waitms(200);
	}
}
