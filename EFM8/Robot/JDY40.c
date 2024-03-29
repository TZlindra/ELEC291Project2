#include "JDY40.h"

idata char TX_BUFF[20];
idata char RX_BUFF[20];

// Uses Timer3 to delay <us> micro-seconds.
void Timer3_us(unsigned char us) {
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

void putchar1(char c) {
    SFRPAGE = 0x20;
	while (!TI1);
	TI1=0;
	SBUF1 = c;
	SFRPAGE = 0x00;
}

void sendstr1(char* s) {
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
	RI1=0;
	// Clear Overrun and Parity error flags
	SCON1&=0b_0011_1111;
	c = SBUF1;
	SFRPAGE = 0x00;
	return (c);
}

char getchar1_with_timeout(void) {
	char c;
	unsigned int timeout;
    SFRPAGE = 0x20;
    timeout = 0;
	while(!RI1) {
		SFRPAGE = 0x00;
		Timer3_us(20);
		SFRPAGE = 0x20;
		timeout++;
		if (timeout==25000) {
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

void getstr1(char* s) {
	char c;

	while(1) {
		c = getchar1_with_timeout();
		if (c=='\n') {
			*s=0;
			return;
		}
		*s=c;
		s++;
	}
}

// RXU1 returns '1' if there is a byte available in the receive buffer of UART1
bit RXU1(void) {
	bit mybit;
    SFRPAGE = 0x20;
	mybit=RI1;
	SFRPAGE = 0x00;
	return mybit;
}

void waitms_or_RI1(unsigned int ms) {
	unsigned int j;
	unsigned char k;
	for(j=0; j<ms; j++)
	{
		for (k=0; k<4; k++)
		{
			if(RXU1()) return;
			Timer3_us(250);
		}
	}
}

void SendATCommand(char* s) {
	printf("Command: %s", s);
	P2_0=0; // 'set' pin to 0 is 'AT' mode.
	Delay_ms(5);
	sendstr1(s);
	getstr1(TX_BUFF);
	Delay_ms(10);
	P2_0=1; // 'set' pin to 1 is normal operation mode.
	printf("Response: %s\r\n", TX_BUFF);
}

void Update_I(int inductance) {
	sprintf(TX_BUFF, "%d", inductance);
}

void TX_I(void) {
	sendstr1(TX_BUFF);
	waitms_or_RI1(500);
}

void RX_XY(void) {
	int timeout_count = 0;

	while (timeout_count <= 200) {
		if (RXU1()) {
			getstr1(RX_BUFF);
			SBUF1 = 0;
		}

		timeout_count++;
		Delay_ms(1); // Delay For Response
	}
}

void display_buffs(void) {
	printf("TX_BUFF: %s\r\n", TX_BUFF);
	printf("RX_BUFF: %s\r\n", RX_BUFF);
}

int searchI(char* array) {
	char* array_ptr = array;
    while (*array_ptr) {
        if (*array_ptr == 'I') return 1;
        array_ptr++;
    }
    return 0;
}
