#include "movement.h"

#define Y_MIDPOINT 2044
#define X_MIDPOINT 2136
#define MINIMUM_PERCENT_ACTIVE 0.1

void standardized_joystick_values(float* x_value, float* y_value)
{
    *x_value = *x_value - X_MIDPOINT;
    *y_value = *y_value - Y_MIDPOINT;
}

float y_direction_to_PWM_percent(float y_value)
{
    // checks if ADC is more than 10% higher than the initial value before starting to move
    if (y_value > Y_MIDPOINT + MINIMUM_PERCENT_ACTIVE * Y_MIDPOINT || y_value < Y_MIDPOINT - MINIMUM_PERCENT_ACTIVE * Y_MIDPOINT)
    {
        if (y_value > Y_MIDPOINT)
        {
            return y_value / (4095 - Y_MIDPOINT);
        }
        else if (y_value < Y_MIDPOINT)
        {
            return y_value / (Y_MIDPOINT);
        }
    }

    return 0;

}

void JDY_PWM_Transmission_X(float x_percent, float y_percent)
{
    int x = 1;
}