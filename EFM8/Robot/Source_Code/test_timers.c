// #include "movement_integration.h"

#include <EFM8LB1.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SYSCLK 72000000
#define BAUDRATE 115200L

#define MAX_16_BIT 65536.0 // 16-Bit Maximum Value
#define MAX_8_BIT 256.0 // 8-Bit Maximum Value
#define TIMER_4_FREQ 1000L
#define TIMER_5_FREQ 1000L
#define TIMER_3_FREQ 10000L

/* Clock Frequency and Baud Rate */
// Baudrate of UART in BPS
#define SARCLK 18000000L // SARCLK Frequency in Hz

/* Define Pins */
#define EFM8_SIGNAL P1_0 // Signal to Measure

#define VSS 5 // The measured value of VSS in volts
#define VDD 3.3035 // The measured value of VDD in volts

idata char buff[80];

void splitString(const char *str, char *part1, char *part2);
int stringToInt(char *str);

volatile int TXcount=0;
volatile int flag = 0;

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
	P1MDOUT |= 0b0000_1100;
	EA=1;
	return 0;
}

void TIMER4_Init(void)
{
	// Initialize timer 4 for periodic interrupts
	SFRPAGE=0x10;
	TMR4CN0=0x00;   // Stop Timer4; Clear TF4; WARNING: lives in SFR page 0x10
	CKCON1|=0b_0000_0001; // Timer 4 uses the system clock
	TMR4RL=(0x10000L-(SYSCLK/(2*TIMER_4_FREQ))); // Initialize reload value
	TMR4=0xffff;   // Set to reload immediately
	EIE2|=0b_0000_0100;     // Enable Timer4 interrupts
	TR4=1;
}

void Timer4_ISR (void) interrupt INTERRUPT_TIMER4
{

	SFRPAGE=0x10;
	TF4H = 0; // Clear Timer4 interrupt flag
	TXcount++;
	if(TXcount >= 1000){
		TXcount=0;
		// P1_2=!P1_2;
		flag == 0;
	}
	P1_2=!P1_2;
}

void Timer3_ISR (void) interrupt INTERRUPT_TIMER3
{
	SFRPAGE=0x0;
	TMR3CN0&=0b_0011_1111; // Clear Timer3 interrupt flags

    //P1_2 = !P1_2;
    P1_3 = !P1_3;
    //P2_1 = !P2_1;

    // if (count > 100)
    // {
    //     count = 0;
    // }
    // if (PWM_percent_y >= 0)
    // {
    //     LEFT_MOTOR_LHS = (count > left_wheel ) ? 0:1;
    //     RIGHT_MOTOR_LHS = (count > new_right_wheel) ? 0:1;
    // }
    // else
    // {
    //     LEFT_MOTOR_LHS = (count > left_wheel) ? 1:0;
    //     RIGHT_MOTOR_LHS = (count > new_right_wheel) ? 1:0;
    // }


    // count++;


}


// Uses Timer3 to delay <us> micro-seconds.
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

void waitms (unsigned int ms)
{
	unsigned int j;
	unsigned char k;
	for(j=0; j<ms; j++)
		for (k=0; k<4; k++) Timer3us(250);
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

void putchar1(char c) {
    SFRPAGE = 0x20;
    while (!TI1);
    TI1 = 0;
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

char getchar1(void) {
    char c;
    SFRPAGE = 0x20;
    while (!RI1);
    RI1 = 0;
    // Clear Overrun and Parity error flags
    SCON1 &= 0b_0011_1111;
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
	getstr1(buff);
	waitms(10);
	P2_0=1; // 'set' pin to 1 is normal operation mode.
	printf("Response: %s\r\n", buff);
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

void clearUART1Buffer(void) {
    // Disable UART1 reception
    REN1 = 0;  // Disable UART1 reception

    // Flush the receive buffer
    while (RI1) {
        volatile dummy = SBUF1; // Read and discard data from receive buffer
    }

    // Re-enable UART1 reception
    REN1 = 1;  // Enable UART1 reception
}


int stringToInt(char *str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    // Check for negative sign
    if (str[0] == '-') {
        sign = -1;
        i++;
    }

    // Iterate through characters of the string
    for (; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            // Convert character to integer and add to result
            result = result * 10 + (str[i] - '0');
        } else {
            // If non-numeric character encountered, return 0
            return 0;
        }
    }

    // Apply sign
    return sign * result;
}

void splitString(const char *str, char *part1, char *part2) {
    // Get the length of the input string
    int length = strlen(str);
    int isNegative1 = 0; // Flag for negative first number
    int isNegative2 = 0; // Flag for negative second number
    const char *ptr = str;

    //printf("str: %s\n", str);
    //printf("part1: %p\n", (void*)part1);
    //printf("part2: %p\n", (void*)part2);

    // Check if the length of the string is less than 6
    // If it is, we cannot split the string as required
    if (length < 6) {
        printf("Error: Input string is too short to split.\n");
        printf("STR: %s \r\n", str);
        return;
    }

    // Loop through the string pointer to check for negative signs
    while (*ptr != '\0') {
        if (*ptr == '-') {
            // Check if the negative sign is for the first or second number
            if (ptr == str) {
                isNegative1 = 1;
            } else {
                isNegative2 = 1;
            }
        }
        ptr++;
    }

    // If the number was negative, prepend '-' to part1 or append it to part2
    if (isNegative1) {
        // Copy the first three characters of the input string to part1
        strncpy(part1+1, str+1, 3);
        part1[4] = '\0'; // Null-terminate the string
        part1[0] = '-'; // Prepend '-'
    } else {
        strncpy(part1, str, 3);
        part1[3] = '\0'; // Null-terminate the string
    }

    if (isNegative2) {
        // Copy the first three characters of the input string to part1
        strncpy(part2+1, str+length-3, 3);
        part2[4] = '\0'; // Null-terminate the string
        part2[0] = '-'; // Prepend '-'
    } else {
        // Copy the first three characters of the input string to part1
        strncpy(part2, str+length-3, 3);
        part2[3] = '\0'; // Null-terminate the string
    }

    //printf("part 1: %s\n", part1);
    //printf("part 2: %s\n", part2);
}

void Trim(char *str, int *xin, int *yin) {
    int i, j;
    char * strStart = str;
    char *x = malloc(5 * sizeof(char));
    char *y = malloc(5 * sizeof(char));

    for (i = 0, j = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i]) || str[i] == '-') {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';  // Null-terminate the resulting string
   // printf("%p \n", x);
    //printf("%s \n", str);
    //printf("%p \n", &x);
    splitString(str, x, y);

    //printf("%p \n", y);
    //printf("%p \n", x);

    *xin = stringToInt(x);
    *yin = stringToInt(y);

    //printf("%d \n", *xin);

   // printf("%d \n", *yin);
}

void JDY40Init(void){

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

void TIMER3Init(void)
{
	// Initialize timer 3 for periodic interrupts
	TMR3CN0=0x00;   // Stop Timer3; Clear TF3;
	CKCON0|=0b_0100_0000; // Timer 3 uses the system clock
	TMR3RL=(0x10000L-(SYSCLK/(2*TIMER_3_FREQ))); // Initialize reload value
	TMR3=0xffff;   // Set to reload immediately
	EIE1|=0b_1000_0000;     // Enable Timer3 interrupts
	TMR3CN0|=0b_0000_0100;  // Start Timer3 (TMR3CN0 is not bit addressable)
    EA = 1;
}

void main (void)
{

	volatile int flag = 0;
	int *xin = malloc(8);
    int *yin = malloc(8);
	unsigned int cnt =0;
	int length;
	int commands[2];
	waitms(500);
	printf("\r\nJDY-40 test\r\n");
	UART1_Init(9600);
	JDY40Init();
    TIMER3Init();
	TIMER4_Init();
	// movement_init();

	// To configure the device (shown here using default values).
	// For some changes to take effect, the JDY-40 needs to be power cycled.
	// Communication can only happen between devices with the
	// same RFID and DVID in the same channel.

	//SendATCommand("AT+BAUD4\r\n");
	//SendATCommand("AT+RFID8899\r\n");
	//SendATCommand("AT+DVID1122\r\n"); // Default device ID.
	//SendATCommand("AT+RFC001\r\n");
	//SendATCommand("AT+POWE9\r\n");
	//SendATCommand("AT+CLSSA0\r\n");

	// We should select an unique device ID.  The device ID can be a hex
	// number from 0x0000 to 0xFFFF.  In this case is set to 0xABBA


	while(1)
	{
		if(flag == 0)
		{
			flag == 1;
			sprintf(buff, " %04d\r\n", cnt++);
			sendstr1(buff);
			printf("%s\r\n",buff);
			clearUART1Buffer();
			waitms_or_RI1(200);
		}
		if(RXU1())
		{

			getstr1(buff);
			clearUART1Buffer();
			length = strlen(buff);
			Trim(buff, &commands[0],&commands[1]);
			if(length >= 11){
				printf("X: %d \r\n", commands[0]);
				printf("Y: %d \r\n", commands[1]);
			}
			else{
				printf("test\r\n");
			}
		}

		// movement_loop(commands[0], commands[1]);

	}
}
