#include "global.h"

#define PERIOD_PIN P1_0 // Signal to Measure

unsigned long GetPeriod (int n);
float GetFrequency(void);
float GetCapacitance_mF(void);
float GetInductance_mH(void);
