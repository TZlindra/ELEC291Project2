#include "inductance.h"

int C1_nF = 100;
int C2_nF = 10;

// Measure the period of a square signal at PERIOD_PIN
unsigned long GetPeriod (int n) {
	unsigned int overflow_count;
	unsigned char i;

	EA=0; // Disable interrupts
	TR0=0; // Stop Timer/Counter 0
	TMOD&=0b_1111_0000; // Set the bits of Timer/Counter 0 to zero
	TMOD|=0b_0000_0001; // Timer/Counter 0 used as a 16-bit timer

	// Reset the counter
	TR0=0;
	TL0=0; TH0=0; TF0=0; overflow_count=0;
	TR0=1;
	while(PERIOD_PIN!=0) // Wait for the signal to be zero
	{
		if(TF0==1) // Did the 16-bit timer overflow?
		{
			TF0=0;
			overflow_count++;
			if(overflow_count==10) // If it overflows too many times assume no signal is present
			{
				TR0=0;
				return 0; // No signal
			}
		}
	}

	// Reset the counter
	TR0=0;
	TL0=0; TH0=0; TF0=0; overflow_count=0;
	TR0=1;
	while(PERIOD_PIN!=1) // Wait for the signal to be one
	{
		if(TF0==1) // Did the 16-bit timer overflow?
		{
			TF0=0;
			overflow_count++;
			if(overflow_count==10) // If it overflows too many times assume no signal is present
			{
				TR0=0;
				return 0; // No signal
			}
		}
	}

	// Reset the counter
	TR0=0;
	TL0=0; TH0=0; TF0=0; overflow_count=0;
	TR0=1; // Start the timer
	for(i=0; i<n; i++) // Measure the time of 'n' periods
	{
		while(PERIOD_PIN!=0) // Wait for the signal to be zero
		{
			if(TF0==1) // Did the 16-bit timer overflow?
			{
				TF0=0;
				overflow_count++;
			}
		}
		while(PERIOD_PIN!=1) // Wait for the signal to be one
		{
			if(TF0==1) // Did the 16-bit timer overflow?
			{
				TF0=0;
				overflow_count++;
			}
		}
	}
	TR0=0; // Stop timer 0, the 24-bit number [overflow_count-TH0-TL0] has the period in clock cycles!
	EA=1; // Enable interrupts

	return (overflow_count*65536+TH0*256+TL0);
}

unsigned long GetFrequency_Hz(void) {
	long int count = GetPeriod(5);
	long int frequency = (SYSCLK*5.0)/(count*12);

	printf("Frequency: %ld Hz\n", frequency);

	if (count>0) return frequency;
	else return 0;
}

float GetCapacitance_mF(void) {
    return ((C1_nF*C2_nF)/(C1_nF+C2_nF)) / MILLI_MULTIPLIER / MILLI_MULTIPLIER;
}

int GetInductance_microH(void) {
    long int freq = GetFrequency_Hz();
    float CT_mF = GetCapacitance_mF();
	float I_kH = MILLI_MULTIPLIER/(squared(2*PI*freq) * CT_mF);

    return (int)(MILLI_MULTIPLIER * MILLI_MULTIPLIER * I_kH);
}