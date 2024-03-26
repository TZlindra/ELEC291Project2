#include "movement.h"

void standardize_directions(float* x_value, float* y_value) {
    *x_value = -1 * (*x_value - X_MIDPOINT);
    *y_value = -1 * (*y_value - Y_MIDPOINT);
}

float standardize_y(float y_value) {
    // checks if ADC is more than 5% higher than the initial value before starting to move
    if (y_value > MINIMUM_PERCENT_ACTIVE * (4095 - Y_MIDPOINT) || y_value < - MINIMUM_PERCENT_ACTIVE * Y_MIDPOINT)
    {
        if (y_value >= 0) return y_value / (4095 - Y_MIDPOINT);
        else if (y_value < 0) return y_value / (Y_MIDPOINT);
    }

    return 0;
}

float standardize_x(float x_value) {
    // checks if ADC is more than 5% higher than the initial value before starting to move
    if (x_value > MINIMUM_PERCENT_ACTIVE * (4095 - X_MIDPOINT) || x_value < - MINIMUM_PERCENT_ACTIVE * X_MIDPOINT) {
        if (x_value >= 0) return x_value / (X_MIDPOINT);
        else if (x_value < 0) return x_value / (4095 - X_MIDPOINT);
    }

    return 0;
}