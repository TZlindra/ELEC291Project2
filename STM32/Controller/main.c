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

void wait_1ms(void) {
	// For SysTick info check the STM32L0xxx Cortex-M0 programming manual page 85.
	SysTick->LOAD = (F_CPU/1000L) - 1;  // set reload register, counter rolls over from zero, hence -1
	SysTick->VAL = 0; // load the SysTick counter
	SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk; // Enable SysTick IRQ and SysTick Timer */
	while((SysTick->CTRL & BIT16)==0); // Bit 16 is the COUNTFLAG.  True when counter rolls over from zero.
	SysTick->CTRL = 0x00; // Disable Systick counter
}

void waitms(unsigned int ms) {
	unsigned int j;
	for(j=0; j<ms; j++) wait_1ms();
}

void Delay_us(unsigned char us) {
	// For SysTick info check the STM32L0xxx Cortex-M0 programming manual page 85.
	SysTick->LOAD = (F_CPU/(1000000L/us)) - 1;  // set reload register, counter rolls over from zero, hence -1
	SysTick->VAL = 0; // load the SysTick counter
	SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk; // Enable SysTick IRQ and SysTick Timer */
	while((SysTick->CTRL & BIT16)==0); // Bit 16 is the COUNTFLAG.  True when counter rolls over from zero.
	SysTick->CTRL = 0x00; // Disable Systick counter
}

void initADC(void) {
	RCC->APB2ENR |= BIT9; // peripheral clock enable for ADC (page 175 or RM0451)

	// ADC clock selection procedure (page 746 of RM0451)
	/* (1) Select PCLK by writing 11 in CKMODE */
	ADC1->CFGR2 |= ADC_CFGR2_CKMODE; /* (1) */

	// ADC enable sequence procedure (page 745 of RM0451)
	/* (1) Clear the ADRDY bit */
	/* (2) Enable the ADC */
	/* (3) Wait until ADC ready */
	ADC1->ISR |= ADC_ISR_ADRDY; /* (1) */
	ADC1->CR |= ADC_CR_ADEN; /* (2) */
	if ((ADC1->CFGR1 & ADC_CFGR1_AUTOFF) == 0)
	{
		while ((ADC1->ISR & ADC_ISR_ADRDY) == 0) /* (3) */
		{
			/* For robust implementation, add here time-out management */
		}
	}

	// Calibration code procedure (page 745 of RM0451)
	/* (1) Ensure that ADEN = 0 */
	/* (2) Clear ADEN */
	/* (3) Set ADCAL=1 */
	/* (4) Wait until EOCAL=1 */
	/* (5) Clear EOCAL */
	if ((ADC1->CR & ADC_CR_ADEN) != 0) /* (1) */
	{
		ADC1->CR |= ADC_CR_ADDIS; /* (2) */
	}
	ADC1->CR |= ADC_CR_ADCAL; /* (3) */
	while ((ADC1->ISR & ADC_ISR_EOCAL) == 0) /* (4) */
	{
		/* For robust implementation, add here time-out management */
	}
	ADC1->ISR |= ADC_ISR_EOCAL; /* (5) */
}

int readADC(unsigned int channel) {
	// Single conversion sequence code example - Software trigger (page 746 of RM0451)
	/* (1) Select HSI16 by writing 00 in CKMODE (reset value) */
	/* (2) Select the auto off mode */
	/* (3) Select channel */
	/* (4) Select a sampling mode of 111 i.e. 239.5 ADC clk to be greater than17.1us */
	/* (5) Wake-up the VREFINT (only for VRefInt) */
	//ADC1->CFGR2 &= ~ADC_CFGR2_CKMODE; /* (1) */
	ADC1->CFGR1 |= ADC_CFGR1_AUTOFF; /* (2) */
	ADC1->CHSELR = channel; /* (3) */
	ADC1->SMPR |= ADC_SMPR_SMP_0 | ADC_SMPR_SMP_1 | ADC_SMPR_SMP_2; /* (4) */
	if(channel==ADC_CHSELR_CHSEL17)
	{
		ADC->CCR |= ADC_CCR_VREFEN; /* (5) */
	}

	/* Performs the AD conversion */
	ADC1->CR |= ADC_CR_ADSTART; /* start the ADC conversion */
	while ((ADC1->ISR & ADC_ISR_EOC) == 0) /* wait end of conversion */
	{
		/* For robust implementation, add here time-out management */
	}

	return ADC1->DR; // ADC_DR has the 12 bits out of the ADC
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

void LCD_pulse(void) {
	LCD_E_1;
	Delay_us(40);
	LCD_E_0;
}

void LCD_byte(unsigned char x) {
	//Send high nible
	if(x&0x80) LCD_D7_1; else LCD_D7_0;
	if(x&0x40) LCD_D6_1; else LCD_D6_0;
	if(x&0x20) LCD_D5_1; else LCD_D5_0;
	if(x&0x10) LCD_D4_1; else LCD_D4_0;
	LCD_pulse();
	Delay_us(40);
	//Send low nible
	if(x&0x08) LCD_D7_1; else LCD_D7_0;
	if(x&0x04) LCD_D6_1; else LCD_D6_0;
	if(x&0x02) LCD_D5_1; else LCD_D5_0;
	if(x&0x01) LCD_D4_1; else LCD_D4_0;
	LCD_pulse();
}

void WriteData (unsigned char x) {
	LCD_RS_1;
	LCD_byte(x);
	waitms(2);
}

void WriteCommand (unsigned char x) {
	LCD_RS_0;
	LCD_byte(x);
	waitms(5);
}

void LCD_4BIT(void) {
	LCD_E_0; // Resting state of LCD's enable is zero
	//LCD_RW=0; // We are only writing to the LCD in this program
	waitms(20);
	// First make sure the LCD is in 8-bit mode and then change to 4-bit mode
	WriteCommand(0x33);
	WriteCommand(0x33);
	WriteCommand(0x32); // Change to 4-bit mode

	// Configure the LCD
	WriteCommand(0x28);
	WriteCommand(0x0c);
	WriteCommand(0x01); // Clear screen command (takes some time)
	waitms(20); // Wait for clear screen command to finsih.
}

void LCDprint(char * string, unsigned char line, unsigned char clear) {
	int j;

	WriteCommand(line==2?0xc0:0x80);
	waitms(5);
	for(j=0; string[j]!=0; j++)	WriteData(string[j]);// Write the message
	if(clear) for(; j<CHARS_PER_LINE; j++) WriteData(' '); // Clear the rest of the line
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
	sprintf(LCD_BUFF, "ADC[8]=0x%04x V=%fV", (int)x, (x*3.3)/0x1000);
	LCDprint(LCD_BUFF, 1, 1);

	sprintf(LCD_BUFF, "ADC[9]=0x%04x V=%fV", (int)y, (y*3.3)/0x1000);
	LCDprint(LCD_BUFF, 2, 1);
}

void main(void) {
	float x, y;

	ConfigPinsLCD();
	LCD_4BIT();
	ConfigPinButton();
	ConfigPinADC();

	initADC();

	waitms(500); // Wait for putty to start.
	printf("\x1b[2J\x1b[1;1H"); // Clear screen using ANSI escape sequence.

	while (1) {

		x = readADC(ADC_CHSELR_CHSEL8);
		y = readADC(ADC_CHSELR_CHSEL9);

		// Display the ADC values on the LCD
		display_x_y(x, y);

		printf("ADC[8]=0x%04x V=%fV\r", (int)x, (x*3.3)/0x1000);
		printf("ADC[9]=0x%04x V=%fV\r", (int)y, (y*3.3)/0x1000);

		fflush(stdout); // GCC printf wants a \n in order to send something.  If \n is not present, we fflush(stdout)
		waitms(200);
	}
}
