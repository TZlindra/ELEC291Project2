#include "movement.h"

#define Y_MIDPOINT 2044
#define X_MIDPOINT 2136
#define MINIMUM_PERCENT_ACTIVE 0.1

#define Y_STRING "Y: "

void standardized_joystick_values(float* x_value, float* y_value)
{
    *x_value = -1 * (*x_value - X_MIDPOINT);
    *y_value = -1 * (*y_value - Y_MIDPOINT);
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

//    SendCommand(Y_STRING, y_value);
}

float x_direction(float x_value)
{
    // checks if ADC is more than 10% higher than the initial value before starting to move
    if (x_value > X_MIDPOINT + MINIMUM_PERCENT_ACTIVE * X_MIDPOINT || x_value < X_MIDPOINT - MINIMUM_PERCENT_ACTIVE * X_MIDPOINT)
    {
        if (x_value > X_MIDPOINT)
        {
            return 4095 - X_MIDPOINT;
        }
        else if (x_value < X_MIDPOINT)
        {
            return X_MIDPOINT;
        }
    }

    return 0;

   //SendCommand(Y_STRING, y_value);
}