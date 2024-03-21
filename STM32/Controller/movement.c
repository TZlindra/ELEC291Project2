#include "movement.h"

#define Y_MIDPOINT 2044.0
#define X_MIDPOINT 2136.0

//#define Y_MIDPOINT 2050
//#define X_MIDPOINT 2100
#define MINIMUM_PERCENT_ACTIVE 0.05

#define X_STRING "X:"
#define Y_STRING "Y:"

void standardized_joystick_values(float* x_value, float* y_value)
{
    *x_value = -1 * (*x_value - X_MIDPOINT);
    *y_value = -1 * (*y_value - Y_MIDPOINT);
}

float y_direction_to_PWM_percent(float y_value)
{
    // checks if ADC is more than 5% higher than the initial value before starting to move
    if (y_value > MINIMUM_PERCENT_ACTIVE * (4095 - Y_MIDPOINT) || y_value < - MINIMUM_PERCENT_ACTIVE * Y_MIDPOINT)
    {
        if (y_value >= 0) return y_value / (4095 - Y_MIDPOINT);
        else if (y_value < 0) return y_value / (Y_MIDPOINT);
    }

    return 0;
}

float x_direction_to_PWM_percent(float x_value)
{
    // checks if ADC is more than 5% higher than the initial value before starting to move
    if (x_value > MINIMUM_PERCENT_ACTIVE * (4095 - X_MIDPOINT) || x_value < - MINIMUM_PERCENT_ACTIVE * X_MIDPOINT)
    {
        if (x_value >= 0) return x_value / (X_MIDPOINT);
        else if (x_value < 0) return x_value / (4095 - X_MIDPOINT);
    }

    return 0;
}