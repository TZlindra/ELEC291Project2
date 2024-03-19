// Inductance = 1.001 mH

/*
 * main.c : Robot Period Measurement At Pin P0.1 using Timer 0
 * and Displaying the Frequency and Colpitts Oscillator on LCD.
 */

/* Include Headers */
#include <EFM8LB1.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_16_BIT 65536.0 // 16-Bit Maximum Value
#define MAX_8_BIT 256.0 // 8-Bit Maximum Value

/* Clock Frequency and Baud Rate */
#define SYSCLK    72000000L // SYSCLK Frequency in Hz
#define BAUDRATE    115200L // Baudrate of UART in BPS
#define SARCLK 18000000L // SARCLK Frequency in Hz

/* Define Pins */
#define EFM8_SIGNAL P1_0 // Signal to Measure

#define VSS 5 // The measured value of VSS in volts
#define VDD 3.3035 // The measured value of VDD in volts

idata char buffs[80];
idata char buffr[80];
/*
 * External Startup Function
 */
char _c51_external_startup (void)
{
	// Disable Watchdog with key sequence
	SFRPAGE = 0x00;
	WDTCN = 0xDE; //First key
	WDTCN = 0xAD; //Second key

	VDM0CN=0x80;       // enable VDD monitor
	RSTSRC=0x02|0x04;  // Enable reset on missing clock detector and VDD

	#if (SYSCLK == 48000000L)
		SFRPAGE = 0x10;
		PFE0CN  = 0x10; // SYSCLK < 50 MHz.
		SFRPAGE = 0x00;
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
		// Before setting clock to 48 MHz, must transition to 24.5 MHz first
		CLKSEL = 0x00;
		CLKSEL = 0x00;
		while ((CLKSEL & 0x80) == 0);
		CLKSEL = 0x07;
		CLKSEL = 0x07;
		while ((CLKSEL & 0x80) == 0);
	#elif (SYSCLK == 72000000L)
		// Before setting clock to 72 MHz, must transition to 24.5 MHz first
		CLKSEL = 0x00;
		CLKSEL = 0x00;
		while ((CLKSEL & 0x80) == 0);
		CLKSEL = 0x03;
		CLKSEL = 0x03;
		while ((CLKSEL & 0x80) == 0);
	#else
		#error SYSCLK must be either 12250000L, 24500000L, 48000000L, or 72000000L
	#endif

	P0MDOUT |= 0x11; // Enable UART0 TX (P0.4) and UART1 TX (P0.0) as push-pull outputs
	P2MDOUT |= 0x01; // P2.0 in push-pull mode
	XBR0     = 0x01; // Enable UART0 on P0.4(TX) and P0.5(RX)
	XBR1     = 0X00;
	XBR2     = 0x41; // Enable crossbar and uart 1

	// Configure Uart 0
	#if (((SYSCLK/BAUDRATE)/(2L*12L))>0xFFL)
		#error Timer 0 reload value is incorrect because (SYSCLK/BAUDRATE)/(2L*12L) > 0xFF
	#endif
	SCON0 = 0x10;
	TH1 = 0x100-((SYSCLK/BAUDRATE)/(2L*12L));
	TL1 = TH1;      // Init Timer1
	TMOD &= ~0xf0;  // TMOD: timer 1 in 8-bit auto-reload
	TMOD |=  0x20;
	TR1 = 1; // START Timer1
	TI = 1;  // Indicate TX0 ready

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

void UART1_Init (unsigned long baudrate)
{
    SFRPAGE = 0x20;
	SMOD1 = 0x0C; // no parity, 8 data bits, 1 stop bit
	SCON1 = 0x10;
	SBCON1 =0x00;   // disable baud rate generator
	SBRL1 = 0x10000L-((SYSCLK/baudrate)/(12L*2L));
	TI1 = 1; // indicate ready for TX
	SBCON1 |= 0x40;   // enable baud rate generator
	SFRPAGE = 0x00;
}

void putchar1 (char c)
{
    SFRPAGE = 0x20;
	while (!TI1);
	TI1=0;
	SBUF1 = c;
	SFRPAGE = 0x00;
}

void sendstr1 (char * s)
{
	while(*s)
	{
		putchar1(*s);
		s++;
	}
}

char getchar1 (void)
{
	char c;
    SFRPAGE = 0x20;
	while (!RI1);
	RI1=0;
	// Clear Overrun and Parity error flags
	SCON1&=0b_0011_1111;
	c = SBUF1;
	SFRPAGE = 0x00;
	return (c);
}

char getchar1_with_timeout (void)
{
	char c;
	unsigned int timeout;
    SFRPAGE = 0x20;
    timeout=0;
	while (!RI1)
	{
		SFRPAGE = 0x00;
		Timer3us(20);
		SFRPAGE = 0x20;
		timeout++;
		if(timeout==25000)
		{
			SFRPAGE = 0x00;
			return ('\n'); // Timeout after half second
		}
	}
	RI1=0;
	// Clear Overrun and Parity error flags
	SCON1&=0b_0011_1111;
	c = SBUF1;
	SFRPAGE = 0x00;
	return (c);
}

void getstr1 (char * s)
{
	char c;

	while(1)
	{
		c=getchar1_with_timeout();
		if(c=='\n')
		{
			*s=0;
			return;
		}
		*s=c;
		s++;
	}
}

// RXU1 returns '1' if there is a byte available in the receive buffer of UART1
bit RXU1 (void)
{
	bit mybit;
    SFRPAGE = 0x20;
	mybit=RI1;
	SFRPAGE = 0x00;
	return mybit;
}

void waitms_or_RI1 (unsigned int ms)
{
	unsigned int j;
	unsigned char k;
	for(j=0; j<ms; j++)
	{
		for (k=0; k<4; k++)
		{
			if(RXU1()) return;
			Timer3us(250);
		}
	}
}

void SendATCommand (char * s)
{
	printf("Command: %s", s);
	P2_0=0; // 'set' pin to 0 is 'AT' mode.
	waitms(5);
	sendstr1(s);
	getstr1(buffs);
	waitms(10);
	P2_0=1; // 'set' pin to 1 is normal operation mode.
	printf("Response: %s\r\n", buffs);
}

float calculate_period_s(int overflow_count, int TH0, int TL0) {
	return ((overflow_count * MAX_16_BIT)  + (TH0 * MAX_8_BIT) + TL0) * (12.0 / SYSCLK);
}

float calculate_freq_Hz(float period_s) {
	return (1.0 / period_s);
}


// This function initalizes the JDY40 by setting the RFID and DVID, note that the EFM8 and STM32
// Must have the same RFID AND DVID in order to be able to communicate with eachother
// After setting the DVID and RFID it checks the configuration at the start of the program

void InitJDY(void) {
	SendATCommand("AT+DVIDAFAF\r\n");
	SendATCommand("AT+RFIDFFBB\r\n");
	// To check configuration
	SendATCommand("AT+VER\r\n");
	SendATCommand("AT+BAUD\r\n");
	SendATCommand("AT+RFID\r\n");
	SendATCommand("AT+DVID\r\n");
	SendATCommand("AT+RFC\r\n");
	SendATCommand("AT+POWE\r\n");
	SendATCommand("AT+CLSS\r\n");
}

// This function Uses timer 0 to calculate the period of a square wave
// on P1_0, It can be easily changed to read another pin by changing
// EFM8_SIGNAL to another pin

float GetFreq(void){
		float period_s, freq_Hz;
		int overflow_count = 0;
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
		return freq_Hz;
}

// This function sends the frequency on P1_0 to the JDY40 for transmission to the STM32
// Should more data need to be sent it will either be put here or in its own function
// We should consider adding logic so frequency is only sent if it is a certain range
// that we will determine once we have constructed the circuit for metal detection
void SendFreq(float freq){
	sprintf(buffs,"%.3f\r\n",freq);
	sendstr1(buffs);
	waitms_or_RI1(500);
}


	// This function will be receiving the ADC values from the joy stick both X and Y
	// More logic will be needed in order to store these ADC values to then control the motors
void CheckCommand(void){

	if(RXU1())
		{
			getstr1(buffr);
			printf("%s\r\n", buffr);
		}
}

void main(void) {
	float freq;
	TIMER0_Init(); // Initialize Timer 0
    Serial_Init(); // Initialize Serial Port
	UART1_Init(9600);
	InitJDY();
    while(1){
    //	freq = GetFreq();
    //	SendFreq(freq);
		CheckCommand();
    }
}