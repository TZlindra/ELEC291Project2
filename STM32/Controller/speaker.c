// This program activates the PWM function of timer 2 channel 1 on PA15 (pin 25).
// The PWM is changed every second or so using the ISR for TIM2.

// LQFP32 pinout
//                    ----------
//              VDD -|1      32|- VSS
//             PC14 -|2      31|- BOOT0
//             PC15 -|3      30|- PB7
//             NRST -|4      29|- PB6
//             VDDA -|5      28|- PB5
// LCD_RS      PA0 -|6       27|- PB4
// LCD_E       PA1 -|7       26|- PB3  (TIM2_CH2)
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

#include "../Common/Include/stm32l051xx.h"
#include "speaker.h"

void InitTimer2(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // Turn on clock for timer2
    TIM2->ARR = F_CPU / TICK_FREQ_TIM2 - 1; // Set the auto-reload value

    NVIC_EnableIRQ(TIM2_IRQn); // Enable timer 2 interrupts in the NVIC
    TIM2->CR1 |= TIM_CR1_DIR; // Downcounting
    TIM2->CR1 |= TIM_CR1_ARPE; // ARPE enable
    TIM2->DIER |= TIM_DIER_UIE; // Enable update event (reload event) interrupt
    TIM2->CR1 |= TIM_CR1_CEN; // Enable counting

	__enable_irq();
}

void ToggleSpeaker(void) {
	GPIOA->ODR ^= BIT8;
}

float ChangeSpeakerRatio(float current_ratio) {
    float new_ratio, new_freq;

    if (current_ratio >= 10) new_ratio = 1;
    else new_ratio = current_ratio * 2;

    new_freq = TICK_FREQ_TIM2 / new_ratio;
    printf("Current Frequency: %f\r\n", new_freq);

    return new_ratio;
}

void ConfigSpeaker(float ratio) {
	if (ratio == 0)
		TIM2->CR1 &= !BIT0;
	else
		TIM2->CR1 |= BIT0;
}
