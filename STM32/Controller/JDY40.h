#include "global.h"

#define DEF_F 15000L
#define TICK_FREQ_TIM21 1000L

void InitTimer21(void);

void JDS_Delay_us(unsigned char us);
void JDY_Delay_msJDY(unsigned int ms);

void ConfigPinsUART2(void);
void SendATCommand (char * s);
void SendCommand(char * s, int value);
void ReceiveCommand(void);
void ConfigJDY40(void);

void TX_XY(void);
void RX_I(void);

void Update_XY(int x_value, int y_value);
int Update_I(int inductance);

void display_buffs(void);