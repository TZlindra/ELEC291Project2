#include "global.h"

// #define TICK_FREQ_TIM2 4096L
// #define TICK_FREQ_TIM2 5120L
// #define TICK_FREQ_TIM2 3520L
// #define TICK_FREQ_TIM2 7040L
#define TICK_FREQ_TIM2 14080L

void InitTimer2(void);
void ToggleSpeaker(void);
float SetSpeakerFreq(float inductance_mH, float current_ratio);
void ConfigSpeaker(float ratio);