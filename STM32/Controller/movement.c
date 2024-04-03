#include "movement.h"

void standardize_directions(float* x_value, float* y_value) {
    *x_value = -1 * (*x_value - X_MIDPOINT);
    *y_value = -1 * (*y_value - Y_MIDPOINT);
}

int standardize_y(float y_value, int sensitivity_y) {
    int standardized = 0;

    // checks if ADC is more than 5% higher than the initial value before starting to move
    if (y_value > MINIMUM_PERCENT_ACTIVE * (4095 - Y_MIDPOINT) || y_value < - MINIMUM_PERCENT_ACTIVE * Y_MIDPOINT) {
            if (y_value >= 0) standardized = (int)(100 * y_value / (4095 - Y_MIDPOINT));
            else if (y_value < 0) standardized = (int)(100 * y_value / (Y_MIDPOINT));
            if (sensitivity_y == 1) standardized /= 2;
            else if (sensitivity_y == 2) standardized /= 4;
    }

    return standardized;
}

int standardize_x(float x_value, int sensitivity_x) {
    int standardized = 0;

    // checks if ADC is more than 5% higher than the initial value before starting to move
    if (x_value > MINIMUM_PERCENT_ACTIVE * (4095 - X_MIDPOINT) || x_value < - MINIMUM_PERCENT_ACTIVE * X_MIDPOINT) {
        if (x_value >= 0) standardized = (int)(100 * x_value / (X_MIDPOINT));
        else if (x_value < 0) standardized = (int)(100 * x_value / (4095 - X_MIDPOINT));

        if (sensitivity_x == 1) standardized /= 2;
        else if (sensitivity_x == 2) standardized /= 4;
    }

    return standardized;
}