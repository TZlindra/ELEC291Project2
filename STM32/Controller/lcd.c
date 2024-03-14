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

#include "../Common/Include/stm32l051xx.h"
#include "lcd.h"

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