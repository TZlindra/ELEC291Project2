#include "global.h"

#define PERIOD_PIN P1_0 // Signal to Measure

unsigned long GetPeriod(int n);
unsigned long GetFrequency_Hz(void);
float GetCapacitance_mF(void);
int GetInductance_microH(void);
