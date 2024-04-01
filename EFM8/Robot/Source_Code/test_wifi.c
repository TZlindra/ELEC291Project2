#include <EFM8LB1.h>
#include <stdio.h>

#define WIFI_SSID "M"
#define WIFI_PASSWORD "MeepMeep"
#define SERVER_IP "128.189.201.143" // Replace with your laptop's IP address
#define SERVER_PORT "12345" // Replace with your server's listening port

#define SYSCLK 72000000
#define BAUDRATE 115200L

#define MAX_16_BIT 65536.0 // 16-Bit Maximum Value
#define MAX_8_BIT 256.0 // 8-Bit Maximum Value

/* Clock Frequency and Baud Rate */
// Baudrate of UART in BPS
#define SARCLK 18000000L // SARCLK Frequency in Hz

/* Define Pins */
#define EFM8_SIGNAL P1_0 // Signal to Measure

#define VSS 5 // The measured value of VSS in volts
#define VDD 3.3035 // The measured value of VDD in volts

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

	return 0;
 }

void TIMER0_Init(void) {
	TMOD &= 0b_1111_0000; // Set the Bits of Timer/Counter 0 to 0
	TMOD |= 0b_0000_0001; // Timer/Counter 0 Used As 16-Bit Timer
	TR0 = 0; // Stop Timer/Counter 0
}

void Timer3us(unsigned char us)
{
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

void UART0_SendChar(char c) {
    while (!TI);  // Wait for previous transmission to complete
    TI = 0;       // Clear transmit interrupt flag
    SBUF0 = c;    // Start transmission
}

void UART0_SendString(char* s) {
    while (*s) {
        UART0_SendChar(*s++);
    }
}

char UART0_GetChar(void) {
    while (!RI);  // Wait for character to be received
    RI = 0;       // Clear receive interrupt flag
    return SBUF0; // Return received character
}


void waitms (unsigned int ms)
{
	unsigned int j;
	unsigned char k;
	for(j=0; j<ms; j++)
		for (k=0; k<4; k++) Timer3us(250);
}

void checkESP8266(void) {
    UART0_SendString("AT\r\n"); // Check if ESP-01S is ready
    waitms(1000); // Wait for a response (adjust based on your testing)
}

void connectToWiFi(void) {
    char cmd[100];
    sprintf(cmd, "AT+CWJAP=\"%s\",\"%s\"\r\n", WIFI_SSID, WIFI_PASSWORD);
    UART0_SendString(cmd);
    waitms(5000); // Wait for connection to establish
}

void connectToServer(void) {
    char cmd[100];
    sprintf(cmd, "AT+CIPSTART=\"TCP\",\"%s\",%s\r\n", SERVER_IP, SERVER_PORT);
    UART0_SendString(cmd);
    waitms(2000); // Wait for connection to establish
}

void sendData(const char* data) {
    char cmd[50];
    sprintf(cmd, "AT+CIPSEND=%d\r\n", strlen(data));
    UART0_SendString(cmd);
    waitms(1000); // Wait for prompt
    UART0_SendString(data);
}

void main(void) {
    UART0_Init();
    checkESP8266(); // Check if the ESP-01S is ready
    connectToWiFi(); // Connect to WiFi
    connectToServer(); // Connect to the TCP server
    sendData("Hello, server!"); // Send a message to the server

    while(1) {
        // Loop indefinitely
        // Additional code can be added here
    }
}
