#define F_CPU 32000000L
#define DEF_F 15000L
#define TICK_FREQ_TIM21 1000L

#define REQUEST "I"

void InitTimer21(void);

void JDS_Delay_us(unsigned char us);
void JDY_Delay_msJDY(unsigned int ms);

void ConfigPinsUART2(void);
void SendATCommand (char * s);
void SendCommand(char * s, int value);
void ReceiveCommand(void);
void ConfigJDY40(void);

void Send_X_Y(float x_value, float y_value);
int ReceiveInductance(int inductance);