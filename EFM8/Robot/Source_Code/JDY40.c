#include "JDY40.h"

#define TIMER_4_FREQ 1000L

xdata char RXbuff[80];
xdata char TXbuff[80];

volatile int TXcount=0;
volatile int flag = 0;
volatile int commands[2];

int length;

void JDY40Init(void) {
	// int *xin = malloc(8);
	// int *yin = malloc(8);

	// To configure the device (shown here using default values).
	// For some changes to take effect, the JDY-40 needs to be power cycled.
	// Communication can only happen between devices with the
	// same RFID and DVID in the same channel.

	// We should select an unique device ID.  The device ID can be a hex
	// number from 0x0000 to 0xFFFF.  In this case is set to 0xABBA
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

void TIMER4_Init(void) {
	// Initialize timer 4 for periodic interrupts
	SFRPAGE=0x10;
	TMR4CN0=0x00;   // Stop Timer4; Clear TF4; WARNING: lives in SFR page 0x10
	CKCON1|=0b_0000_0001; // Timer 4 uses the system clock
	TMR4RL=(0x10000L-(SYSCLK/(2*TIMER_4_FREQ))); // Initialize reload value
	TMR4=0xffff;   // Set to reload immediately
	EIE2|=0b_0000_0100;     // Enable Timer4 interrupts
	TR4=1;
}

void Timer4_ISR (void) interrupt INTERRUPT_TIMER4 {
	SFRPAGE=0x10;
	TF4H = 0; // Clear Timer4 interrupt flag
	TXcount++;
	// if(TXcount >= 1000){
	if(TXcount >= 2500){
		TXcount=0;
		P1_2=!P1_2;
		flag == 0;
	}
}

void putchar1(char c) {
    SFRPAGE = 0x20;
    while (!TI1);
    TI1 = 0;
    SBUF1 = c;
    SFRPAGE = 0x00;
}

void sendstr1(char * s) {
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

char getchar1_with_timeout (void) {
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

void getstr1 (char * s) {
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

void SendATCommand(char * s) {
	printf("Command: %s", s);
	P2_0=0; // 'set' pin to 0 is 'AT' mode.
	waitms(5);
	sendstr1(s);
	getstr1(RXbuff);
	waitms(10);
	P2_0=1; // 'set' pin to 1 is normal operation mode.
	printf("Response: %s\r\n", RXbuff);
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

    free(x);
    free(y);

    //printf("%d \n", *xin);

   // printf("%d \n", *yin);
}

void Update_TX_Buff(long inductance) {
	sprintf(TXbuff, "%08d\r\n", inductance);
}

void TX_I(void) {
    if(flag == 0)
		{
			flag == 1;
			sendstr1(TXbuff);
			// printf("%s\r\n",TXbuff);
			clearUART1Buffer();
			waitms_or_RI1(200);

		}
}

void RX_XY() {
    if(RXU1())
		{

			getstr1(RXbuff);
			clearUART1Buffer();
			length = strlen(RXbuff);
            // printf("Buff: %s\r\n", buff);
			Trim(RXbuff, &commands[0],&commands[1]);
			// if(length >= 11){
			// 	printf("X: %d \r\n", commands[0]);
			// 	printf("Y: %d \r\n", commands[1]);
			// }
			// else{
			// 	printf("Invalid Length %d \r\n", length);
			// }
		}
	// printf("Nothing Recieved\r\n");
}

float get_x_direction(void) {
    return commands[0];
}

float get_y_direction(void) {
    return commands[1];
}

void eputs(char *String)
{
	while(*String)
	{
		putchar(*String);
		String++;
	}
}

void PrintNumber(long int val, int Base, int digits) {
	code const char HexDigit[]="0123456789ABCDEF";
	int j;
	#define NBITS 32
	xdata char buff[NBITS+1];
	buff[NBITS]=0;

	if(val<0)
	{
		putchar('-');
		val*=-1;
	}

	j=NBITS-1;
	while ( (val>0) | (digits>0) )
	{
		buff[j--]=HexDigit[val%Base];
		val/=Base;
		if(digits!=0) digits--;
	}
	eputs(&buff[j+1]);
}