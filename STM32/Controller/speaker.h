#define SYSCLK 32000000L
#define TICK_FREQ 2048L

void InitTimer2(void);
void TIM2_Handler(void);
void ToggleSpeaker(void);
void ToggleSpeakerTimer(void);