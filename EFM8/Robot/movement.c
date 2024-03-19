/*
movement.c and movement.h are files designed to control the robot's movement
It will recieve 4 movement signals from the EMF8, 2 for each wheel.
    These signals will be interpreted to supply
    either GND OR 3.3 V to 4 corresponding pins for CW and CCW movement
*Additionally, it will receive a PWM signal to determine torque for how MUCH movement is required
*/

#include "movement.h"

/*define the 4 movement pins, 2 for each motor*/
/*must be 3.3 V (?) pins*/
#define LEFT_MOTOR_LHS  Px_x
#define LEFT_MOTOR_RHS  Px_x
#define RIGHT_MOTOR_LHS Px_x
#define RIGHT_MOTOR_RHS Px_x