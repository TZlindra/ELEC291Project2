#include <EFM8LB1.h>
#include "speaker.h"

int store;

void TIMER2Init(void)
{
// Initialize timer 2 for periodic interrupts
	TMR2CN0=0x00;   // Stop Timer2; Clear TF2;
	CKCON0|=0b_0001_0000; // Timer 2 uses the system clock
	TMR2RL=(0x10000L-(SYSCLK/(2*TIMER_2_FREQ))); // Initialize reload value
	TMR2=0xffff;   // Set to reload immediately
	ET2=1;         // Enable Timer2 interrupts
	TR2=1;         // Start Timer2 (TMR2CN is bit addressable)
}

void Timer2_ISR (void) interrupt INTERRUPT_TIMER2
{
	EA = 0;
	store = TR0;
	TR0 = 0;
	SFRPAGE=0x0;
	TF2H = 0; // Clear Timer2 interrupt flag
	TF2L = 0;
	SPEAKER_OUT=!SPEAKER_OUT;
	if(store == 1) TR0 = 1;
	EA = 1;
}

void ToggleSpeaker(int enable)
{
    if (enable) TR2 = 1;
    else{
		TR2 = 0;
		SPEAKER_OUT = 0;
	}
}