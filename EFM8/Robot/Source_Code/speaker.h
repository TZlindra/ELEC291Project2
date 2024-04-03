#include <EFM8LB1.h>
#include "global.h"

#define TIMER_2_FREQ 4096L

#define SPEAKER_OUT P1_7

void TIMER2Init(void);
void ToggleSpeaker(int enable);