#include <EFM8LB1.h>
#include "global.h"

#define TIMER_2_FREQ 2048L

#define SPEAKER_OUT P0_6


void TIMER2Init(void);
void ToggleSpeaker(int enable);