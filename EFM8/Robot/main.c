/*
 * main.c : Robot Period Measurement At Pin P0.1 using Timer 0
 * and Displaying the Frequency and Colpitts Oscillator on LCD.
 */

/* Include Headers */
#include <EFM8LB1.h>
#include <stdio.h>

#define MAX_16_BIT 65536.0 // 16-Bit Maximum Value
#define MAX_8_BIT 256.0 // 8-Bit Maximum Value

/* Clock Frequency and Baud Rate */
#define SYSCLK    72000000L // SYSCLK Frequency in Hz
#define BAUDRATE    115200L // Baudrate of UART in BPS
#define SARCLK 18000000L // SARCLK Frequency in Hz

/* Define Pins */
#define EFM8_SIGNAL P0_1 // Signal to Measure

#define VSS 5 // The measured value of VSS in volts
#define VDD 3.3035 // The measured value of VDD in volts

int overflow_count = 0; // Timer 0 Overflow Counter

/*
 * External Startup Function
 */
char _c51_external_startup(void) {
	// Disable Watchdog With Key Sequence
	SFRPAGE = 0x00;
	WDTCN = 0xDE; // First Key
	WDTCN = 0xAD; // Second Key

	VDM0CN |= 0x80;
	RSTSRC=0x02|0x04;  // Enable Reset on Missing Clock Detector and VDD

	#if (SYSCLK == 48000000L)
		SFRPAGE = 0x10;
		PFE0CN  = 0x10; // SYSCLK < 50 MHz.
		SFRPAGE = 0x00;
    /* Effective SYSCLK */
	#elif (SYSCLK == 72000000L)
		SFRPAGE = 0x10;
		PFE0CN  = 0x20; // SYSCLK < 75 MHz.
		SFRPAGE = 0x00;
	#endif

	#if (SYSCLK == 12250000L)
		CLKSEL = 0x10;
		CLKSEL = 0x10;
		while ((CLKSEL & 0x80) == 0);
	#elif (SYSCLK == 24500000L)
		CLKSEL = 0x00;
		CLKSEL = 0x00;
		while ((CLKSEL & 0x80) == 0);
	#elif (SYSCLK == 48000000L)
		// Before Setting Clock to 48 MHz, Must Transition to 24.5 MHz First
		CLKSEL = 0x00;
		CLKSEL = 0x00;
		while ((CLKSEL & 0x80) == 0);
		CLKSEL = 0x07;
		CLKSEL = 0x07;
		while ((CLKSEL & 0x80) == 0);
    /* Effective SYSCLK */
	#elif (SYSCLK == 72000000L)
		// Before Setting Clock to 72 MHz, Must Transition to 24.5 MHz First
		CLKSEL = 0x00;
		CLKSEL = 0x00;
		while ((CLKSEL & 0x80) == 0);
		CLKSEL = 0x03;
		CLKSEL = 0x03;
		while ((CLKSEL & 0x80) == 0);
	#else
		#error SYSCLK must be either 12250000L, 24500000L, 48000000L, or 72000000L
	#endif

	P0MDOUT |= 0x10; // Enable UART0 TX As Push-Pull Output
	XBR0     = 0x01; // Enable UART0 on P0.4 (TX) and P0.5 (RX)
	XBR1     = 0X00; // Enable T0 on P0.0
	XBR2     = 0x40; // Enable Crossbar and Weak Pull-Ups

	#if (((SYSCLK/BAUDRATE)/(2L*12L))>0xFFL)
		#error Timer 0 reload value is incorrect because (SYSCLK/BAUDRATE)/(2L*12L) > 0xFF
	#endif

	// Configure UART 0
	SCON0 = 0x10;
	CKCON0 |= 0b_0000_0000 ; // Timer 1 Uses SYSCLK / 12
	TH1 = 0x100-((SYSCLK/BAUDRATE)/(2L*12L)); // Set Timer1 Reload Value, Initial Value
	TL1 = TH1; 	// Init Timer1
	TMOD &= ~0xf0;  // TMOD: Timer 1 in 8-bit auto-reload
	TMOD |=  0x20;
	TR1 = 1; // Start Timer1
	TI = 1;  // Indicate TX0 Ready

	return 0;
}

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

void Serial_Init(void) {
	waitms(500); // Give Putty a chance to start.
	printf("\x1b[2J"); // Clear screen using ANSI escape sequence.
}

void TIMER0_Init(void) {
	TMOD &= 0b_1111_0000; // Set the Bits of Timer/Counter 0 to 0
	TMOD |= 0b_0000_0001; // Timer/Counter 0 Used As 16-Bit Timer
	TR0 = 0; // Stop Timer/Counter 0
}

float calculate_period_s(int overflow_count, int TH0, int TL0) {
	return ((overflow_count * MAX_16_BIT)  + (TH0 * MAX_8_BIT) + TL0) * (12.0 / SYSCLK);
}

float calculate_freq_Hz(float period_s) {
	return (1.0 / period_s);
}

void main(void) {
	float period_s, freq_Hz, capacitance_nF;

	TIMER0_Init(); // Initialize Timer 0
    Serial_Init(); // Initialize Serial Port

    while(1) {
        // Reset Counter
		TL0 = 0;
		TH0 = 0;
		TF0 = 0;
		overflow_count = 0;

		while (EFM8_SIGNAL != 0); // Wait for Signal == 0
		while (EFM8_SIGNAL != 1); // Wait for Signal == 1

        TR0 = 1; // Start Timer

		while (EFM8_SIGNAL != 0) { // Wait for Signal == 0
			if (TF0 == 1) { // Did 16-Bit Timer Overflow?
				TF0 = 0;
				overflow_count++;
			}
        }
        while (EFM8_SIGNAL != 1) { // Wait for Signal == 1
			if (TF0 == 1) { // Did 16-Bit Timer Overflow?
				TF0 = 0;
				overflow_count++;
			}
        }

		TR0 = 0; // Stop Timer 0. The 24-bit number [overflow_count-TH0-TL0] has the period!
		period_s = calculate_period_s(overflow_count, TH0, TL0);
		freq_Hz = calculate_freq_Hz(period_s);

		/*
		 * Print Frequency & Capacitance to Serial Port. Display on LCD.
		 */
	}
}