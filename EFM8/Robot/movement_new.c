#include <EFM8LB1.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define LEFT_MOTOR_LHS  P2_4
#define LEFT_MOTOR_RHS  P2_3
#define RIGHT_MOTOR_LHS P2_2
#define RIGHT_MOTOR_RHS P2_1

#define SYSCLK    72000000L // SYSCLK Frequency in Hz

#define TIMER_0_FREQ 1000L

int count = 0;
enum State state;
float PWM_percent_y = 0.5;
float PWM_percent_x = 0.5;
float prev_PWM_percent_x;
float prev_PWM_percent_y;

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

void TIMER0_Init(void)
{
	// Initialize timer 0 for periodic interrupts
	TR0=0;
	TF0=0;
	CKCON0|=0b_0000_0100; // Timer 0 uses the system clock
	TMOD&=0xf0;
	TMOD|=0x01; // Timer 0 in mode 1: 16-bit timer
	// Initialize reload value
	TMR0=65536L-(SYSCLK/(2*TIMER_0_FREQ));
	ET0=1;     // Enable Timer0 interrupts
	TR0=1;     // Start Timer0
}

void Timer0_ISR (void) interrupt INTERRUPT_TIMER0
{
	SFRPAGE=0x0;
	// Timer 0 in 16-bit mode doesn't have auto reload
	TMR0=0x10000L-(SYSCLK/(2*TIMER_0_FREQ));

    // For testing
    P1_2 = !P1_2;

    if (state != idle_enum)
    {
        if (count > 100)
        {
            // turn on
            if (state == left_enum)
            {
                RIGHT_MOTOR_LHS = 1;
            }
            else if (state == right_enum)
            {
                LEFT_MOTOR_LHS = 1;
            }
            else
            {
                LEFT_MOTOR_LHS = 1;
                RIGHT_MOTOR_LHS = 1;
            }
            count = 0;
        }
        else if (count > PWM_percent_y*100)
        {
            //turn off
            if (state == left_enum)
            {
                RIGHT_MOTOR_LHS = 0;
            }
            else if (state == right_enum)
            {
                LEFT_MOTOR_LHS = 0;
            }
            else
            {
                LEFT_MOTOR_LHS = 0;
                RIGHT_MOTOR_LHS = 0;
            }
        }
        count++;

    }


}

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
    // to change later
    LEFT_MOTOR_LHS = 0;
    LEFT_MOTOR_RHS = 0;

    if (PWM_percent_y > 0)
    {
        RIGHT_MOTOR_LHS = 1;
        RIGHT_MOTOR_RHS = 0;
    }
    else
    {
        RIGHT_MOTOR_LHS = 0;
        RIGHT_MOTOR_RHS = 1;
    }

}

void right(float PWM_percent_y)
{
    // to change later
    RIGHT_MOTOR_LHS = 0;
    RIGHT_MOTOR_RHS = 0;

    if (PWM_percent_y > 0)
    {
        LEFT_MOTOR_LHS = 1;
        LEFT_MOTOR_RHS = 0;
    }
    else
    {
        LEFT_MOTOR_LHS = 0;
        LEFT_MOTOR_RHS = 1;
    }

}

enum State movement_manager(float PWM_percent_x, float PWM_percent_y, float prev_PWM_percent_x, float prev_PWM_percent_y, enum State state)
{

    if (prev_PWM_percent_x != PWM_percent_x && prev_PWM_percent_y != PWM_percent_y){
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

int main(void)
{
    TIMER0_Init();
    while(1)
    {
        state = movement_manager(PWM_percent_x, PWM_percent_y, prev_PWM_percent_x, prev_PWM_percent_y, state);
        prev_PWM_percent_x = PWM_percent_x;
        prev_PWM_percent_y = PWM_percent_y;

        /* // For testing
        while(P0_1 == 0)
        {
        	P1_2=1;
        }
        P1_2=0;
        */

    }

}