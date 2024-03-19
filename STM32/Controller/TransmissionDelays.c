#include "../Common/Include/stm32l051xx.h"
#include "JDY40.h"

volatile int Count = 0;

#define SYSCLK 32000000L
#define TICK_FREQ 1000L

// Once every 0.001 seconds
void TIM21_Handler(void)
{
	TIM21->SR &= ~BIT0; // clear update interrupt flag
	Count++;
	if (Count > 1000)
	{
		Count = 0;
		ReceiveCommand(); // toggle the state of the LED every half second
	}
}

// LQFP32 pinout
//             ----------
//       VDD -|1       32|- VSS
//      PC14 -|2       31|- BOOT0
//      PC15 -|3       30|- PB7
//      NRST -|4       29|- PB6
//      VDDA -|5       28|- PB5
//       PA0 -|6       27|- PB4
//       PA1 -|7       26|- PB3
//       PA2 -|8       25|- PA15
//       PA3 -|9       24|- PA14
//       PA4 -|10      23|- PA13
//       PA5 -|11      22|- PA12
//       PA6 -|12      21|- PA11
//       PA7 -|13      20|- PA10 (Reserved for RXD)
//       PB0 -|14      19|- PA9  (Reserved for TXD)
//       PB1 -|15      18|- PA8
//       VSS -|16      17|- VDD
//             ----------

void Timer21Init(void)
{
	// Set up timer
	RCC->APB2ENR |= BIT2;  // turn on clock for timer21 (UM: page 188)
	TIM21->ARR = SYSCLK/(TICK_FREQ*2);
	NVIC->ISER[0] |= BIT20; // enable timer 21 interrupts in the NVIC
	TIM21->CR1 |= BIT4;      // Downcounting
	TIM21->CR1 |= BIT0;      // enable counting
	TIM21->DIER |= BIT0;     // enable update event (reload event) interrupt
	__enable_irq();
}
