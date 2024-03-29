
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

static enum State state;
static int correct_combination;

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

int isButtonPressed(int ButtonPin) {
	return !(GPIOA->IDR & ButtonPin);
}

void resetCombination(void) {
    printf("\x1b[2J\x1b[1;1H"); // Clear screen using ANSI escape sequence.
    printf("Enter Combination...\r\n");
    state = s_0;
    correct_combination = 1;
}

int getPasscodeButton(void) {
    if (isButtonPressed(BIT12) || isButtonPressed(BIT12) || isButtonPressed(BIT12) || isButtonPressed(BIT12)) {
        passcode_waitms(DEBOUNCE); // Debounce

        if (isButtonPressed(BIT12)) return s_0; // Button A
        else if (isButtonPressed(BIT12)) return s_1; // Button B
        else if (isButtonPressed(BIT12)) return s_2; // Button C
        else if (isButtonPressed(BIT12)) return s_3; // Button D
        else return -1;
    } else {
        return -1;
    }
}

void checkCombination(void) {
    int button = getPasscodeButton();
    if (button != -1) {
        if (state != button) correct_combination = 0;
        state++;
        printf("State:%d Button:%d Correct:%d\r\n", state, button, correct_combination);
    }
}

void checkPasscode(void) {
    resetCombination();

    while (state != s_success) {
        // printf("Button A: %d\r\n", isButtonPressed(BIT12));
        // printf("Button B: %d\r\n", isButtonPressed(BIT12));
        // printf("Button C: %d\r\n", isButtonPressed(BIT12));
        // printf("Button D: %d\r\n", isButtonPressed(BIT12));

        passcode_waitms(500); // Wait 500ms

        if (state != s_check) checkCombination();
        else if (correct_combination == 1) {
            state = s_success;
            printf("Ready to Operate!\r\n");
        } else {
            printf("Combination Fail...Reset...\r\n");
            passcode_waitms(500); // Wait 1s
            resetCombination();
        }
    }
    return;
}
