#include "JDY.h"

idata char TX_BUFF[20];
idata char RX_BUFF[20];

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

void getstr1(char* s) {
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
			Timer3us(250);
		}
	}
}

void SendATCommand(char * s) {
	printf("Command: %s", s);
	P2_0=0; // 'set' pin to 0 is 'AT' mode.
	waitms(5);
	sendstr1(s);
	getstr1(TX_BUFF);
	waitms(10);
	P2_0=1; // 'set' pin to 1 is normal operation mode.
	printf("Response: %s\r\n", TX_BUFF);
}

void SendFreq(int freq) {
	sprintf(TX_BUFF,"%d\r\n",freq);
	sendstr1(TX_BUFF);
	waitms_or_RI1(500);
}

void GetData(void){
	if (RXU1()){
		getstr1(RX_BUFF);
		SBUF1 = 0;
	}
}

void TX_I(void) {
	sprintf(TX_BUFF,"%d",inductance);
	sendstr1(TX_BUFF);
	waitms_or_RI1(500);
}

void RX_Data(void) {
	if (RXU1()){
		getstr1(RX_BUFF);
		//printf("%s\r\n",RX_BUFF);
		// if (RX_BUFF[0] == 'I') TX_I();
		// else printf("%s \r\n",RX_BUFF);
	}
}
