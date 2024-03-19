/*
 * Uses Timer 3 to delay <us> micro-seconds.
 */
void Timer3us(unsigned char us) {
	unsigned char i; // Microsecond Counter

	// Input for Timer 3 is Selected as SYSCLK by Setting T3ML (Bit 6) of CKCON0
	CKCON0 |= 0b_0100_0000;

	TMR3RL = (-(SYSCLK)/1000000L); // Set Timer3 to Overflow in 1us
	TMR3 = TMR3RL;                 // Initialize Timer3 for First Overflow

	TMR3CN0 = 0x04;                 // Start Timer3 and Clear Overflow Flag
	for (i = 0; i < us; i++) {      // Count Overflows (#Microseconds)
		while (!(TMR3CN0 & 0x80));  // Wait for Overflow
		TMR3CN0 &= ~(0x80);         // Clear Overflow Indicator
	}
	TMR3CN0 = 0 ;                   // Stop Timer3 and Clear Overflow Flag
}

void waitms(unsigned int ms) {
	unsigned int j;
	unsigned char k;
	for (j=0; j<ms; j++)
		for (k=0; k<4; k++) Timer3us(250);
}
