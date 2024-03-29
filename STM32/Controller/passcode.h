#include "../Common/Include/stm32l051xx.h"

enum State { s_0 = 0, s_1, s_2, s_3, s_check, s_success };

#define F_CPU 32000000L

void passcode_waitms(unsigned int ms);

int getPasscodeButton(void);

void resetCombination(void);
void checkCombination(void);
void checkPasscode(void);
