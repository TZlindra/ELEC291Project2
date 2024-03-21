#include "frequency_calc.h"

#define C1 1E-9
#define C2 1E-9
#define PI 3.14159265358979323846
#define BASE_FREQUENCY
#define SECOND_RATIO_FREQUENCY
#define THIRD_RATIO_FREQUENCY
#define FOURTH_RATIO_FREQUENCY
#define MINIMUM_FREQUENCY_OFFSET

int calculateCT(void)
{
    return ((C1*C2)/(C1+C2));
}

float calculate_inductance(int frequency)
{
    int CT = calculateCT();
    return (1/(2*PI*frequency*2*PI*frequency)/CT);
}

int SpeakerFrequencyManager(int metal_frequency)
{
    int ratio;
    
    switch (1)
    {
        case (metal_frequency > BASE_FREQUENCY - MINIMUM_FREQUENCY_OFFSET:
            ratio = 1;
            break;
        case (metal_frequency > SECOND_RATIO_FREQUENCY):
            ratio = 2;
            break;
        case (metal_frequency > THIRD_RATIO_FREQUENCY):
            ratio = 3;
            break;
        case (metal_frequency > FOURTH_RATIO_FREQUENCY):
            ratio = 4;
            break;
        default:
            ratio = 0;
            break;
    }

    return ratio;
}

