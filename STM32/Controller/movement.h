#define Y_MIDPOINT 2044
#define X_MIDPOINT 2136
#define MINIMUM_PERCENT_ACTIVE 0.1

void standardized_joystick_values(float* x_value, float* y_value);
float y_direction_to_PWM_percent(float y_value);