#include <EFM8LB1.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LEFT_MOTOR_LHS  P2_4
#define LEFT_MOTOR_RHS  P2_3
#define RIGHT_MOTOR_LHS P2_2
#define RIGHT_MOTOR_RHS P2_1

#define SYSCLK    72000000L // SYSCLK Frequency in Hz
#define BAUDRATE  115200L

#define TIMER_3_FREQ 10000L
#define TIMER_4_FREQ 10000L

int count = 0;

enum State state;
int PWM_percent_y = 100;
int PWM_percent_x = 20;
float left_wheel = 0;
float right_wheel = 0;
int prev_PWM_percent_x = 0;
int prev_PWM_percent_y = 0;

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

	P0MDOUT|=0b_1100_0010;
	P1MDOUT|=0b_1111_1111;
	P2MDOUT|=0b_0001_1111;
    
	XBR0     = 0x00;
	XBR1     = 0X00;
	XBR2     = 0x40; // Enable crossbar and weak pull-ups
    

    /*
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
    */
    return 0;
}

enum State
{
    idle_enum,
    left_enum,
    right_enum,
    straight_enum,
    backward_enum
};

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

void TIMER4Init(void)
{
//Initialize timer 4 for periodic interrupts
	SFRPAGE=0x10;
	TMR4CN0=0x00;   // Stop Timer4; Clear TF4; WARNING: lives in SFR page 0x10
	CKCON1|=0b_0000_0001; // Timer 4 uses the system clock
	TMR4RL=(0x10000L-(SYSCLK/(2*TIMER_4_FREQ))); // Initialize reload value
	TMR4=0xffff;   // Set to reload immediately
	EIE2|=0b_0000_0100;     // Enable Timer4 interrupts
	TR4=1;
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
    LEFT_MOTOR_LHS = (count > left_wheel) ? 0:1;
    RIGHT_MOTOR_LHS = (count > right_wheel) ? 0:1;

    count++;
    
    
}
/*
void Timer3_ISR (void) interrupt INTERRUPT_TIMER3
{
	SFRPAGE=0x0;
	TMR3CN0&=0b_0011_1111; // Clear Timer3 interrupt flags
	P1_2 = !P1_2;

    if (count > 100)
    {
        LEFT_MOTOR_LHS = 1;

        count = 0;
    }
    else if (count > left_wheel)
    {
        LEFT_MOTOR_LHS = 0;
    }
    count++;
}

void Timer4_ISR (void) interrupt INTERRUPT_TIMER4
{
	SFRPAGE=0x10;
	TF4H = 0; // Clear Timer4 interrupt flag
	P1_3 = !P1_3;

    if (count > 100)
    {
        RIGHT_MOTOR_LHS = 1;

        count = 0;
    }
    else if (count > right_wheel)
    {
        RIGHT_MOTOR_LHS = 0;
    }
    count++;
}
*/
/*
void idle(void)
{
    LEFT_MOTOR_LHS = 0;
    LEFT_MOTOR_RHS = 0;
    RIGHT_MOTOR_LHS = 0;
    RIGHT_MOTOR_RHS = 0;
}

void straight(void)
{
    LEFT_MOTOR_LHS = 1;
    LEFT_MOTOR_RHS = 0;
    RIGHT_MOTOR_LHS = 1;
    RIGHT_MOTOR_RHS = 0;
}

void backward(void)
{
    LEFT_MOTOR_LHS = 0;
    LEFT_MOTOR_RHS = 1;
    RIGHT_MOTOR_LHS = 0;
    RIGHT_MOTOR_RHS = 1;
}

void left(float PWM_percent_y)
{
    if (PWM_percent_y > 0)
    {
        RIGHT_MOTOR_LHS = 1;
        RIGHT_MOTOR_RHS = 0;
        LEFT_MOTOR_LHS = 1;
        LEFT_MOTOR_RHS = 0;
    }
    else
    {
        RIGHT_MOTOR_LHS = 0;
        RIGHT_MOTOR_RHS = 1;
        LEFT_MOTOR_LHS = 0;
        LEFT_MOTOR_RHS = 1;
    }

}

void right(float PWM_percent_y)
{

    if (PWM_percent_y > 0)
    {
        LEFT_MOTOR_LHS = 1;
        LEFT_MOTOR_RHS = 0;
        RIGHT_MOTOR_LHS = 1;
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
            left(PWM_percent_y);
        }
        else if (PWM_percent_x > 0)
        {
            state = right_enum;
            right(PWM_percent_y);
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
*/
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


}

int main(void)
{
    PWM_manager(PWM_percent_x, PWM_percent_x);
	//Serial_Init();
    TIMER3Init();
    //TIMER4Init();
    //straight();
    //state = straight_enum;



    while(1)
    {
        PWM_manager(PWM_percent_x, PWM_percent_x);
        //state = movement_manager(PWM_percent_x, PWM_percent_y, prev_PWM_percent_x, prev_PWM_percent_y, state);


        //prev_PWM_percent_x = PWM_percent_x;
        //prev_PWM_percent_y = PWM_percent_y;
    }

}