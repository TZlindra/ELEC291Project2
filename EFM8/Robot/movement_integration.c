#include "movement_integration.h"

#define LEFT_MOTOR_LHS  P2_4    //brown
#define LEFT_MOTOR_RHS  P2_3    //black
#define RIGHT_MOTOR_LHS P2_2    //grey/brown
#define RIGHT_MOTOR_RHS P2_1    //red

volatile int count = 0;

enum State state;
int PWM_percent_y = 0;
int PWM_percent_x = 0;
float left_wheel = 0;
float right_wheel = 0;
float new_right_wheel;
int prev_PWM_percent_x = 0;
int prev_PWM_percent_y = 0;


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

    // to account for the RIGHT wheel being stronger than the LEFT wheel
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
/*
void Timer3_ISR (void) interrupt INTERRUPT_TIMER3
{
	SFRPAGE=0x0;
	TMR3CN0&=0b_0011_1111; // Clear Timer3 interrupt flags

    //P1_2 = !P1_2;
    P1_3 = !P1_3;
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
*/
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

void movement_init(void)
{
    idle();
    state = idle_enum;
    TIMER5Init();
}
void movement_loop(float x, float y)
{
        printf("JDY x: %f, JDY y: %f\r\n", x, y);
        PWM_percent_x = x;
        PWM_percent_y = y;
        printf("PWM_percent x: %f, PWM_percent y: %f\r\n", x, y);

        state = movement_manager(PWM_percent_x, PWM_percent_y, prev_PWM_percent_x, prev_PWM_percent_y, state);
		PWM_manager(PWM_percent_x, PWM_percent_y);
        prev_PWM_percent_x = PWM_percent_x;
        prev_PWM_percent_y = PWM_percent_y;
}