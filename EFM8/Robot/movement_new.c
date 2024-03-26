#include <EFM8LB1.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define LEFT_MOTOR_LHS  P2_4
#define LEFT_MOTOR_RHS  P2_3
#define RIGHT_MOTOR_LHS P2_2
#define RIGHT_MOTOR_RHS P2_1

#define SYSCLK    72000000L // SYSCLK Frequency in Hz

#define TIMER_3_FREQ 10000L

int count = 0;
enum State state;
float PWM_percent_y = 0.5;
float PWM_percent_x = 0;
float prev_PWM_percent_x = 0;
float prev_PWM_percent_y = 0;

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

void Timer3_ISR (void) interrupt INTERRUPT_TIMER3
{
	SFRPAGE=0x0;
	TMR3CN0&=0b_0011_1111; // Clear Timer3 interrupt flags

    P1_2 = !P1_2;
    //P2_1 = !P2_1;

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

int main(void)
{
    TIMER3Init();
    left(0.5);
    state = left_enum;
    while(1)
    {
        state = movement_manager(PWM_percent_x, PWM_percent_y, prev_PWM_percent_x, prev_PWM_percent_y, state);
        prev_PWM_percent_x = PWM_percent_x;
        prev_PWM_percent_y = PWM_percent_y;
        
    
    }
    
}