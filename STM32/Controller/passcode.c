
#include "passcode.h"
#include "lcd.h"

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

#define BUTTON_S0 BIT7
#define BUTTON_S1 BIT6
#define BUTTON_S2 BIT5
#define BUTTON_S3 BIT3

static enum State state;
static int correct_combination;

char PASSCODE_BUFF[CHARS_PER_LINE]; // Buffer for Passcode

int isButtonPressed(int ButtonPin) {
	return !(GPIOB->IDR & ButtonPin);
}

void resetPasscode(void) {
    state = s_0;
    correct_combination = 1;

    printf("\x1b[2J\x1b[1;1H"); // Clear screen using ANSI escape sequence.
    printf("Enter Passcode...\r\n");
    LCDprint("ENTER PASSCODE:", 1, 1);
    for (int i = 0; i < 4; i++) PASSCODE_BUFF[i] = ' ';
    PASSCODE_BUFF[4] = '\0';
    LCDprint(PASSCODE_BUFF, 2, 1);
}

int getPasscodeButton(void) {
    int pressed = -1;
    if (isButtonPressed(BUTTON_S0) || isButtonPressed(BUTTON_S1) || isButtonPressed(BUTTON_S2) || isButtonPressed(BUTTON_S3)) {
        waitms(DEBOUNCE); // Debounce

        if (isButtonPressed(BUTTON_S0)) pressed = s_0; // Button A
        else if (isButtonPressed(BUTTON_S1)) pressed = s_1; // Button B
        else if (isButtonPressed(BUTTON_S2)) pressed = s_2; // Button C
        else if (isButtonPressed(BUTTON_S3)) pressed = s_3; // Button D
        else pressed = -1;

        while (isButtonPressed(BUTTON_S0) || isButtonPressed(BUTTON_S1) || isButtonPressed(BUTTON_S2) || isButtonPressed(BUTTON_S3)); // Wait for button release
        return pressed;
    } else {
        return -1;
    }
}

void checkCombination(void) {
    int button = getPasscodeButton();
    if (button != -1) {
        if (state != button) correct_combination = 0;
        PASSCODE_BUFF[state] = '*';
        LCDprint(PASSCODE_BUFF, 2, 1);
        state++;
        printf("State:%d Button:%d Correct:%d\r\n", state, button, correct_combination);
    }
}

void getPasscode(void) {
    resetPasscode();

    while (state != s_success) {
        // printf("Button S_0: %d\r\n", isButtonPressed(BUTTON_S0));
        // printf("Button S_1: %d\r\n", isButtonPressed(BUTTON_S1));
        // printf("Button S_2: %d\r\n", isButtonPressed(BUTTON_S2));
        // printf("Button S_3: %d\r\n", isButtonPressed(BUTTON_S3));

        // waitms(250); // Wait 500ms

        if (state != s_check) checkCombination();
        else if (correct_combination == 1) {
            state = s_success;
            printf("Rdy to Operate!\r\n");
            LCDprint("RDY TO OPERATE!", 1, 1);
        } else {
            printf("Passcode Fail...\r\n");
            LCDprint("PASSCODE FAIL...", 1, 1);
            waitms(1000); // Wait 1s
            resetPasscode();
        }
    }
    return;
}
