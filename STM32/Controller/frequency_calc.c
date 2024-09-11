#include "frequency_calc.h"

int calculateCT(void) {
    return ((C1*C2)/(C1+C2));
}

float calculate_inductance(int frequency) {
    int CT = calculateCT();
    return (1/(2*PI*frequency*2*PI*frequency)/CT);
}
