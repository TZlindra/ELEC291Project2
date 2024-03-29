#include "../Common/Include/stm32l051xx.h"

enum State { sinit = 0, s1, s2, s3, sfinal };

#define F_CPU 32000000L

void passcode_waitms(unsigned int ms);
void passcodeButtons();
int passcodeMain();
