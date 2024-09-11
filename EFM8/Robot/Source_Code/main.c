#include "global.h"
#include "JDY40.h"
#include "movement.h"
#include "inductance.h"
#include "speaker.h"

float x = 0;
float y = 0;
float z = 0;

char _c51_external_startup (void) {
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
	P1MDOUT |= 0b0000_1110;
	P2MDOUT |= 0b0001_1111; // PWM Pins + speaker

	return 0;
}

void UART1_Init(unsigned long baudrate) {
    SFRPAGE = 0x20;
    SMOD1 = 0x0C; // no parity, 8 data bits, 1 stop bit
    SCON1 = 0x10; // Mode 1, 8-bit UART, variable baud rate, receive enabled
    SBCON1 = 0x00; // disable baud rate generator
    SBRL1 = 0x10000L - ((SYSCLK / baudrate) / (12L * 2L));
    TI1 = 1; // indicate ready for TX
    SBCON1 |= 0x40; // enable baud rate generator
    SFRPAGE = 0x00;
}

void test_print(float x, float y) {
	int test_x = x;
	int test_y = y;
    printf("PWM X: %f, PWM Y: %f\r\n", x, y);
}

void main (void) {
	long int freq = 0;

	int inductance = MILLI_MULTIPLIER;
	waitms(500);
	UART1_Init(9600);
	JDY40Init();
	movement_init();

	TIMER2Init();
	TIMER4_Init();
	TIMER5Init();
    EA = 1;

	while(1) {
		Update_TX_Buff(inductance);

		TX_I();
		RX_XY();

		inductance = GetInductance_microH();
		printf("%d\r\n", inductance);

		x = get_x_direction();
		y = get_y_direction();
		z = get_z();

		// printf("X:%.1f, Y:%.1f, Z:%.1f\r\n", x, y, z);

		if (x == 0 && y == 0) LEDA_PIN = 0, LEDB_PIN = 0;
		else LEDA_PIN = 1, LEDB_PIN = 1;

		// printf("Parsed X: %f, Parsed Y: %f\r\n", x, y);
		movement_loop(x, y);
		// test_print(x, y);
		if (z == 1.0)
		{
			waitms(30);
			if (z == 1.0)
			{
				// while (z == 1.0);
				parking();
			}
		}
	}
}
