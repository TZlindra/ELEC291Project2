
#include "passcode.h"
#include <stdio.h>

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

#define DEBOUNCE 30

#define BUTTON_A BIT3
#define BUTTON_B BIT5
#define BUTTON_C BIT6
#define BUTTON_D BIT7

volatile enum State state = sinit;
int correct = 1;

void passcode_wait_1ms(void) {
	// For SysTick info check the STM32L0xxx Cortex-M0 programming manual page 85.
	SysTick->LOAD = (F_CPU/1000L) - 1;  // set reload register, counter rolls over from zero, hence -1
	SysTick->VAL = 0; // load the SysTick counter
	SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk; // Enable SysTick IRQ and SysTick Timer */
	while((SysTick->CTRL & BIT16)==0); // Bit 16 is the COUNTFLAG.  True when counter rolls over from zero.
	SysTick->CTRL = 0x00; // Disable Systick counter
}

void passcode_waitms(unsigned int ms) {
	unsigned int j;
	for(j=0; j<ms; j++) passcode_wait_1ms();
}


int IsButtonPressed(int ButtonPin) {
	return !(GPIOA->IDR & ButtonPin);
}

void passcodeButtons() {
    if (state == sinit) correct &= IsButtonPressed(BUTTON_A);
    else if (state == s1) correct &= IsButtonPressed(BUTTON_B);
    else if (state == s2) correct &= IsButtonPressed(BUTTON_C);
    else if (state == s3) correct &= IsButtonPressed(BUTTON_D);

    if (IsButtonPressed(BUTTON_A) || IsButtonPressed(BUTTON_B) || IsButtonPressed(BUTTON_C) || IsButtonPressed(BUTTON_D))
    {
        passcode_waitms(DEBOUNCE);
        if (IsButtonPressed(BUTTON_A) || IsButtonPressed(BUTTON_B) || IsButtonPressed(BUTTON_C) || IsButtonPressed(BUTTON_D))
        {
            state++;
            printf("%d %d\n", state, correct);

            while (!IsButtonPressed(BUTTON_A) && !IsButtonPressed(BUTTON_B) && !IsButtonPressed(BUTTON_C) && !IsButtonPressed(BUTTON_D));
        }
    }
}

int passcodeMain(void)
{
    printf("Passcode Main\n");
    // while(state != sfinal && correct == 0)
    // {
    //     if (state == sfinal)
    //     {
    //         state = sinit;
    //         if (correct == 0) correct = 1;
    //     }

    //     passcodeButtons();
    // }
    return 0;
}
