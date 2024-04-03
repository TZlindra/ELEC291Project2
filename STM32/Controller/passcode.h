#include "global.h"

enum State { s_0 = 0, s_1, s_2, s_3, s_check, s_success };

int getPasscodeButton(void);

void resetPasscode(void);
void checkCombination(void);
void getPasscode(void);
