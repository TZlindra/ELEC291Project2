#include "global.h"

#define LEFT_MOTOR_LHS  P2_4    //brown
#define LEFT_MOTOR_RHS  P2_3    //black
#define RIGHT_MOTOR_LHS P2_2    //grey/brown
#define RIGHT_MOTOR_RHS P2_1    //red

#define TIMER_5_FREQ 10000L
#define TIMER_3_FREQ 10000L
// #define TIMER_3_FREQ 1000L

void idle(void);
void straight(void);
void backward(void);
void TIMER5Init(void);
void PWM_manager(float x_value, float y_value);
void movement_manager(float PWM_percent_y, float prev_PWM_percent_y);
void movement_init(void);
void movement_loop(float x, float y);
void parking(void);