#include <EFM8LB1.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

volatile int inductance = 0;

#define test_button1    P2_6    //test button
#define test_button2    P2_5    //test button
#define LEFT_MOTOR_LHS  P2_4    //brown
#define LEFT_MOTOR_RHS  P2_3    //black
#define RIGHT_MOTOR_LHS P2_2    //grey/brown
#define RIGHT_MOTOR_RHS P2_1    //red

#define TIMER_3_FREQ 10000L
#define TIMER_5_FREQ 10000L

//#define TIMER_4_FREQ 10000L

int count = 0;

enum State state;
int PWM_percent_y = 100;
int PWM_percent_x = 0;
float left_wheel = 0;
float right_wheel = 0;
float new_right_wheel;
int prev_PWM_percent_x = 0;
int prev_PWM_percent_y = 0;

void TX_I(void);

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

	P0MDOUT|=0b_0000_0010;
	P1MDOUT|=0b_1111_1111;
	P2MDOUT|=0b_0001_1111;

    //P2MDIN |= 0b_0110_0000;

	return 0;
}
void TIMER0_Init(void) {
	TMOD &= 0b_1111_0000; // Set the Bits of Timer/Counter 0 to 0
	TMOD |= 0b_0000_0001; // Timer/Counter 0 Used As 16-Bit Timer
	TR0 = 0; // Stop Timer/Counter 0
}


/*void TIMER1_Init(void {

)\
*/
// Uses Timer3 to delay <us> micro-seconds.
/*
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


void Serial_Init(void) {
	waitms(500); // Give Putty a chance to start.
	printf("\x1b[2J"); // Clear screen using ANSI escape sequence.
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
*/
void idle(void)
{
    LEFT_MOTOR_LHS = 0;
    LEFT_MOTOR_RHS = 0;
    RIGHT_MOTOR_LHS = 0;
    RIGHT_MOTOR_RHS = 0;
}

void straight(void)
{
    LEFT_MOTOR_RHS = 0;
    RIGHT_MOTOR_RHS = 0;
}

void backward(void)
{
    LEFT_MOTOR_RHS = 1;
    RIGHT_MOTOR_RHS = 1;
}

void horizontal(float PWM_percent_x)
{

    if (PWM_percent_x > 0)
    {
        LEFT_MOTOR_RHS = 0;
        RIGHT_MOTOR_RHS = 0;
    }
    else
    {
        LEFT_MOTOR_LHS = 0;
        LEFT_MOTOR_RHS = 1;
        RIGHT_MOTOR_LHS = 0;
        RIGHT_MOTOR_RHS = 1;
    }

}

enum State
{
    idle_enum,
    left_enum,
    right_enum,
    straight_enum,
    backward_enum
};

void TIMER5Init(void)
{
    // Initialize timer 5 for periodic interrupts
	SFRPAGE=0x10;
	TMR5CN0=0x00;   // Stop Timer5; Clear TF5; WARNING: lives in SFR page 0x10
	CKCON1|=0b_0000_0100; // Timer 5 uses the system clock
	TMR5RL=(0x10000L-(SYSCLK/(2*TIMER_5_FREQ))); // Initialize reload value
	TMR5=0xffff;   // Set to reload immediately
	EIE2|=0b_0000_1000; // Enable Timer5 interrupts
	TR5=1;         // Start Timer5 (TMR5CN0 is bit addressable)
    EA = 1;
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

void PWM_manager(float x_value, float y_value)
{
    if (x_value >= 0) // RIGHT TURN
    {
        left_wheel = abs(y_value);
        right_wheel = (100 - abs(x_value)) * abs(y_value) / 100;
    }
    else if (x_value < 0) // LEFT TURN
    {
        left_wheel = (100 - abs(x_value)) * abs(y_value) / 100;
        right_wheel = abs(y_value);
    }


    // to account for the LEFT wheel being stronger than the RIGHT wheel
    if (abs(y_value) <= 25)
        new_right_wheel = 0.9*right_wheel;
    else if (abs(y_value) <= 50)
        new_right_wheel = 0.95*right_wheel;
    else if (abs(y_value) <= 75)
        new_right_wheel = 0.95*right_wheel;
    else if (abs(y_value) <= 100)
        new_right_wheel = 0.95*right_wheel;
    else
        new_right_wheel = 0.95*right_wheel;


}

enum State movement_manager(float PWM_percent_x, float PWM_percent_y, float prev_PWM_percent_x, float prev_PWM_percent_y, enum State state)
{
    if (prev_PWM_percent_x != PWM_percent_x || prev_PWM_percent_y != PWM_percent_y)
    {
        if (PWM_percent_y == 0 && PWM_percent_x == 0)
        {
            state = idle_enum;
            idle();
        }
        else if (PWM_percent_x < 0)
        {
            state = left_enum;
            horizontal(PWM_percent_y);
        }
        else if (PWM_percent_x > 0)
        {
            state = right_enum;
            horizontal(PWM_percent_y);
        }
        else if (PWM_percent_y > 0)
        {
            state = straight_enum;
            straight();
        }
        else
        {
            state = backward_enum;
            backward();
        }
    }

    return state;

}

void Timer5_ISR (void) interrupt INTERRUPT_TIMER5
{
	SFRPAGE=0x10;
	TF5H = 0; // Clear Timer5 interrupt flag

    P1_2 = !P1_2;
    //P1_3 = !P1_3;
    //P2_1 = !P2_1;



    if (count > 100)
    {
        count = 0;
    }
    if (PWM_percent_y >= 0)
    {
        LEFT_MOTOR_LHS = (count > left_wheel ) ? 0:1;
        RIGHT_MOTOR_LHS = (count > new_right_wheel) ? 0:1;
    }
    else
    {
        LEFT_MOTOR_LHS = (count > left_wheel) ? 1:0;
        RIGHT_MOTOR_LHS = (count > new_right_wheel) ? 1:0;
    }


    count++;
}

void Timer3_ISR (void) interrupt INTERRUPT_TIMER3
{

    SFRPAGE=0x0;
	TMR3CN0&=0b_0011_1111; // Clear Timer3 interrupt flags

    P1_2 = !P1_2;
    //P1_3 = !P1_3;
    //P2_1 = !P2_1;



    if (count > 100)
    {
        count = 0;
    }
    if (PWM_percent_y >= 0)
    {
        LEFT_MOTOR_LHS = (count > left_wheel ) ? 0:1;
        RIGHT_MOTOR_LHS = (count > new_right_wheel) ? 0:1;
    }
    else
    {
        LEFT_MOTOR_LHS = (count > left_wheel) ? 1:0;
        RIGHT_MOTOR_LHS = (count > new_right_wheel) ? 1:0;
    }


    count++;


}

void main (void)
{
	//float freq;
	//TIMER0_Init();
	//Serial_Init();
	//UART1_Init(9600);
	//TIMER3Init();
    TIMER5Init();
    new_right_wheel = left_wheel;
    idle();
	while(1){
        state = movement_manager(PWM_percent_x, PWM_percent_y, prev_PWM_percent_x, prev_PWM_percent_y, state);
		PWM_manager(PWM_percent_x, PWM_percent_y);
        prev_PWM_percent_x = PWM_percent_x;
        prev_PWM_percent_y = PWM_percent_y;
		//printf("Left Wheel: %f\n", left_wheel);
		//printf("Right Wheel: %f\n", right_wheel);

        if (P2_6 == 0)
        {
            PWM_percent_x += 10;
            while(P2_6 == 0);
        }
        if (P2_5 == 0)
        {
            PWM_percent_x -= 10;
            while(P2_5 == 0);
        }
        if (P3_2 == 0)
        {
            PWM_percent_y -= 10;
            while(P3_2 == 0);
        }
        if (P3_7 == 0)
        {
            PWM_percent_y += 10;
            while(P3_7 == 0);
        }

        //printf("PWM X: %d\n", PWM_percent_x);
        //printf("PWM Y: %d\n", PWM_percent_y);

        printf("Left Wheel: %f\n", left_wheel);
		printf("Right Wheel: %f\n", right_wheel);
        printf("NEW LEFT WHEEL: %f\n", new_right_wheel);
		//waitms(500);

	}
}