/*
movement.c and movement.h are files designed to control the robot's movement
It will recieve 4 movement signals from the EMF8, 2 for each wheel.
    These signals will be interpreted to supply
    either GND OR 3.3 V, to 4 corresponding pins for CW and CCW movement
*Additionally, it will receive a PWM signal to determine torque for how MUCH movement is required
*/
#include <EFM8LB1.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "movement.h"


/*define the 4 movement pins, 2 for each motor*/
/*must be 3.3 V (?) pins*/
#define threethreevolt P3_2
#define LEFT_MOTOR_LHS  P2_4
#define LEFT_MOTOR_RHS  P2_3
#define RIGHT_MOTOR_LHS P2_2
#define RIGHT_MOTOR_RHS P2_1

#define SYSCLK      72000000L  // SYSCLK frequency in Hz
#define BAUDRATE      115200L  // Baud rate of UART in bps

/*
char _c51_external_startup (void)
{
	// Disable Watchdog with key sequence
	SFRPAGE = 0x00;
	WDTCN = 0xDE; //First key
	WDTCN = 0xAD; //Second key

	VDM0CN |= 0x80;
	RSTSRC = 0x02;

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

	P0MDOUT |= 0x10; // Enable UART0 TX as push-pull output
	XBR0     = 0x01; // Enable UART0 on P0.4(TX) and P0.5(RX)
	XBR1     = 0X00;
	XBR2     = 0x40; // Enable crossbar and weak pull-ups

	#if (((SYSCLK/BAUDRATE)/(2L*12L))>0xFFL)
		#error Timer 0 reload value is incorrect because (SYSCLK/BAUDRATE)/(2L*12L) > 0xFF
	#endif
	// Configure Uart 0
	SCON0 = 0x10;
	CKCON0 |= 0b_0000_0000 ; // Timer 1 uses the system clock divided by 12.
	TH1 = 0x100-((SYSCLK/BAUDRATE)/(2L*12L));
	TL1 = TH1;      // Init Timer1
	TMOD &= ~0xf0;  // TMOD: timer 1 in 8-bit auto-reload
	TMOD |=  0x20;
	TR1 = 1; // START Timer1
	TI = 1;  // Indicate TX0 ready

	return 0;
}
*/

void TIMER0_Init(void)
{
	TMOD&=0b_1111_0000; // Set the bits of Timer/Counter 0 to zero
	TMOD|=0b_0000_0001; // Timer/Counter 0 used as a 16-bit timer
	TR0=0; // Stop Timer/Counter 0
}

void main (void) {
    TIMER0_Init();
    /*
        BIG ISSUE:
        how tf do we get the motors to spin at a certain voltage
        to achieve different speeds according to the PWM strenght

        fix?:
        set each pin to a timer value (i.e. the pwm period?)
    */
    //int PWM;
    //int input;  //array or int? TBD

    int test_input;

    int test_PWMx;
    int test_PWMy;

    int periodx;
    int periody;
    threethreevolt = 1; //constantly output 3.3 V to Pin 3.2

    test_input = 1;  //test forward movement
    test_PWMx = 0;   //test 50% strength forward
    test_PWMy = 50;  //only y movement at 50% hence 0% for x, and 50% for y

    // ISSUE: how to time pwm length?
    periodx = 0;      //test PWMx period
    periody = 0;      //test PWMy period




    switch (test_input) {
        case 1:
            straightnew();
            //straight(period);
            break;
        case 2:
            back(period);
            break;
        case 3:
            left(period);
            break;
        case 4:
            right(period);
            break;
        default:
            straightnew();
    }

}

void straightnew()
{
    LEFT_MOTOR_LHS = 1;
    LEFT_MOTOR_RHS = 0;
    RIGHT_MOTOR_LHS = 0;
    RIGHT_MOTOR_RHS = 1
}

//LEFT_MOTOR goes CCW
//RIGHT_MOTOR goes CW
void straight(int time_on) {
    int overflow_time;
    int time_off;
    int flag;
    // pwm is a percentage of on/off (ex. 30%)
    // make a timer that sets a overflow point to the time of 1 period of the pwm (needs to be calculated)
    // ex. at 30% of the set overflow value, change all motors to off
    // if it overflows, the cycle if complete, return to main
    flag = 1;
    time_off = overflow_time - time_on;

    while(flag = 1) {
        //start_timer
        // ON STATE
        LEFT_MOTOR_LHS = 1;
        LEFT_MOTOR_RHS = 0;
        RIGHT_MOTOR_LHS = 0;
        RIGHT_MOTOR_RHS = 1;
        if (time_off)  //limit being the 30% of the set timer overflow value
        {
            LEFT_MOTOR_LHS = 0;
            LEFT_MOTOR_RHS = 0;
            RIGHT_MOTOR_LHS = 0;
            RIGHT_MOTOR_RHS = 0;
        }
        //wait for timer to reach set overflow
        //stop timer
        //if overflowed, set flag(?) and BREAK out of while loop
        if (current_timer_value = time_of_one_period){
            flag = 0;  //does
        }
        //reset timer(?)
        //return to main to recieve new input or repeat cycle if same input.
    }
    return;
}

void back(int period) {
    LEFT_MOTOR_LHS = 0;
    LEFT_MOTOR_RHS = 1;
    RIGHT_MOTOR_LHS = 1;
    RIGHT_MOTOR_RHS = 0;
}

void left(int period) {
    LEFT_MOTOR_LHS = 0;
    LEFT_MOTOR_RHS = 0;
    RIGHT_MOTOR_LHS = 1;
    RIGHT_MOTOR_RHS = 0;
}

void right(int period) {
    LEFT_MOTOR_LHS = 1;
    LEFT_MOTOR_RHS = 0;
    RIGHT_MOTOR_LHS = 0;
    RIGHT_MOTOR_RHS = 0;
}

void back_left (int period) {
    // to achieve a smooth back left, gradually decrease the spd of the left motor
    // while maintaining the spd of the right motor using PWMs
}


void back_right (int period) {
    // to achieve a smooth back right, gradually decrease the spd of the right motor
    // while maintaining the spd of the left motor using PWMS
}