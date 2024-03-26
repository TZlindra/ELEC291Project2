#include "frequency_calc.h"

int calculateCT(void)
{
    return ((C1*C2)/(C1+C2));
}

float calculate_inductance(int frequency)
{
    int CT = calculateCT();
    return (1/(2*PI*frequency*2*PI*frequency)/CT);
}
/*
int SpeakerFrequencyManager(int metal_frequency)
{
    if (metal_frequency > BASE_FREQUENCY + MINIMUM_FREQUENCY_ACTIVE)
    {
        return 1;
    }
    else if (metal_frequency > SECOND_RATIO_FREQUENCY)
    {
        return 2;
    }
    else if (metal_frequency > THIRD_RATIO_FREQUENCY)
    {
        return 3;
    }
    else if (metal_frequency > FOURTH_RATIO_FREQUENCY)
    {
        return 4;
    }


    return 0;
}
*/