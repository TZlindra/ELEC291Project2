#include "movement_integration.h"

#define LEFT_MOTOR_LHS  P2_4    //brown
#define LEFT_MOTOR_RHS  P2_3    //black
#define RIGHT_MOTOR_LHS P2_2    //grey/brown
#define RIGHT_MOTOR_RHS P2_1    //red

#define TIMER_3_FREQ 10000L

int count = 0;

enum State state;
int PWM_percent_y = 0;
int PWM_percent_x = 0;
float left_wheel = 0;
float right_wheel = 0;
float new_right_wheel;
int prev_PWM_percent_x = 0;
int prev_PWM_percent_y = 0;

/*
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

void Timer3_ISR (void) interrupt INTERRUPT_TIMER3
{
	SFRPAGE=0x0;
	TMR3CN0&=0b_0011_1111; // Clear Timer3 interrupt flags

    //P1_2 = !P1_2;
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
	// TIMER3Init();
    idle();
    state = idle_enum;
}
void movement_loop(float x, float y)
{
        PWM_percent_x = x;
        PWM_percent_y = y;

        state = movement_manager(PWM_percent_x, PWM_percent_y, prev_PWM_percent_x, prev_PWM_percent_y, state);
		PWM_manager(PWM_percent_x, PWM_percent_y);
        prev_PWM_percent_x = PWM_percent_x;
        prev_PWM_percent_y = PWM_percent_y;

}