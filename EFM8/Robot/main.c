// C1 = 10nF C2 = 100nF
#include "global.h"
#include "JDY40.h"

#define TIMER_OUT_5 P1_3

idata char hold[20];

volatile int TX5Count = 0;
volatile int RX5Count = 0;

volatile int freq = 300;
volatile int inductance = 0;

/* Function Prototypes */
void Timer3us(unsigned char us);
void waitms(unsigned int ms);

float calculate_period_s(int overflow_count, int TH0, int TL0);
float calculate_freq_Hz(float period_s);
float get_freq(void);

char _c51_external_startup(void) {
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

void TIMER0_Init(void) {
	TMOD &= 0b_1111_0000; // Set the Bits of Timer/Counter 0 to 0
	TMOD |= 0b_0000_0001; // Timer/Counter 0 Used As 16-Bit Timer
	TR0 = 0; // Stop Timer/Counter 0
}

void TIMER5_Init(void) {
	// Initialize timer 5 for periodic interrupts
	SFRPAGE=0x10;
	TMR5CN0=0x00;   // Stop Timer5; Clear TF5; WARNING: lives in SFR page 0x10
	CKCON1|=0b_0000_0100; // Timer 5 uses the system clock
	TMR5RL=(0x10000L-(SYSCLK/(2*TIMER_5_FREQ))); // Initialize reload value
	TMR5=0xffff;   // Set to reload immediately
	EIE2|=0b_0000_1000; // Enable Timer5 interrupts
	TR5=1;         // Start Timer5 (TMR5CN0 is bit addressable)
}


void Timer5_ISR (void) interrupt INTERRUPT_TIMER5
{
	SFRPAGE=0x10;
	TF5H = 0; // Clear Timer5 interrupt flag
	TIMER_OUT_5=!TIMER_OUT_5;
}

void Serial_Init(void) {
	waitms(500); // Give Putty a chance to start.
	printf("\x1b[2J"); // Clear screen using ANSI escape sequence.
}

void UART1_Init(unsigned long baudrate) {
    SFRPAGE = 0x20;
	SMOD1 = 0x0C; // no parity, 8 data bits, 1 stop bit
	SCON1 = 0x10;
	SBCON1 =0x00;   // disable baud rate generator
	SBRL1 = 0x10000L-((SYSCLK/baudrate)/(12L*2L));
	TI1 = 1; // indicate ready for TX
	SBCON1 |= 0x40;   // enable baud rate generator
	SFRPAGE = 0x00;
}

void JDYInit(void) {
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

// Uses Timer3 to delay <us> micro-seconds.
void Timer3us(unsigned char us) {
	unsigned char i;               // usec counter

	// The input for Timer 3 is selected as SYSCLK by setting T3ML (bit 6) of CKCON0:
	CKCON0|=0b_0100_0000;

	TMR3RL = (-(SYSCLK)/1000000L); // Set Timer3 to overflow in 1us.
	TMR3 = TMR3RL;                 // Initialize Timer3 for first overflow

	TMR3CN0 = 0x04;                 // Sart Timer3 and clear overflow flag
	for (i = 0; i < us; i++)       // Count <us> overflows
	{
		while (!(TMR3CN0 & 0x80));  // Wait for overflow
		TMR3CN0 &= ~(0x80);         // Clear overflow indicator
	}
	TMR3CN0 = 0 ;                   // Stop Timer3 and clear overflow flag
}

void waitms(unsigned int ms) {
	unsigned int j;
	unsigned char k;
	for(j=0; j<ms; j++)
		for (k=0; k<4; k++) Timer3us(250);
}

float calculate_period_s(int overflow_count, int TH0, int TL0) {
	return ((overflow_count * MAX_16_BIT)  + (TH0 * MAX_8_BIT) + TL0) * (12.0 / SYSCLK);
}

float calculate_freq_Hz(float period_s) {
	return (1.0 / period_s);
}

float get_freq(void) {
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

void GetMovement(char* s, int com) {
	printf(s);
	if (com == 0){
		return;
	}
}

void main (void) {
	// int com;

	TIMER0_Init();
	Serial_Init();
	UART1_Init(9600);
	JDYInit();
	// TIMER5_Init();

	EA = 1;
	while(1){
		RX5Count++;

		if (RX5Count >= 500) {
			RX5Count = 0;
			RX_Data();
		}

		Update_I(inductance);

		display_buffs();

		inductance += 5;
		waitms(500); // Delay 500 ms
	}
}