#include "passcode.h"

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

#define BUTTON0 1 << 6
#define BUTTON1 1 << 5
#define BUTTON2 1 << 4
#define BUTTON3 1 << 3

#define DEBOUNCE 30


enum State state = init;

enum State
{
    init,
    x1,
    x2,
    x3,
    c1,
    c2,
    c3
};

void passcodeButtonsInit()
{
    RCC->IOPENR |= RCC_IOPENR_GPIOBEN; // Peripheral Clock Enable for Port A
	GPIOA->MODER &= ~(BUTTON0 | BUTTON0 << 1); // Make Pin PA12 Input

	GPIOA->PUPDR |= BUTTON0;
	GPIOA->PUPDR &= ~(BUTTON0 << 1);
}

void passcodeButtons()
{

}

int main(void)
{
    switch(state) {
        case init:
            printf("Current state is 1\n");
            break;
        case STATE_2:
            printf("Current state is 2\n");
            break;
        case STATE_3:
            printf("Current state is 3\n");
            break;
        case STATE_4:
            printf("Current state is 4\n");
            break;
        default:
            printf("Invalid state\n");
            break;
    }
    return 0;
}
