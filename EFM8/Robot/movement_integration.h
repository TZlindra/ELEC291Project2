enum State
{
    idle_enum,
    left_enum,
    right_enum,
    straight_enum,
    backward_enum
};

#include <EFM8LB1.h>
#include <stdlib.h>
#include <stdio.h>

#define LEFT_MOTOR_LHS  P2_4    //brown
#define LEFT_MOTOR_RHS  P2_3    //black
#define RIGHT_MOTOR_LHS P2_2    //grey/brown
#define RIGHT_MOTOR_RHS P2_1    //red

#define TIMER_3_FREQ 10000L

void idle(void);
void straight(void);
void backward(void);
void horizontal(float PWM_percent_x);
void TIMER3Init(void);
void PWM_manager(float x_value, float y_value);
enum State movement_manager(float PWM_percent_x, float PWM_percent_y, float prev_PWM_percent_x, float prev_PWM_percent_y, enum State state);
void movement_init(void);
void movement_loop(float x, float y);