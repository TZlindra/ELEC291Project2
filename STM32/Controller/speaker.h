#define F_CPU 32000000L
// #define TICK_FREQ_TIM2 1024L
// #define TICK_FREQ_TIM2 2048L
#define TICK_FREQ_TIM2 4096L

void InitTimer2(void);
void ToggleSpeaker(void);
float ChangeSpeakerRatio(float current_ratio);
void ConfigSpeaker(float ratio);