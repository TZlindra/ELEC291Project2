#define F_CPU 32000000L
#define TICK_FREQ_TIM2 2048L

void InitTimer2(void);
void ToggleSpeaker(void);
float ChangeSpeakerRatio(float inductance);
void ConfigSpeaker(float ratio);