void Delay_usJDY(unsigned char us);
void waitmsJDYJDY(unsigned int ms);

void ConfigPinsUART2(void);
void SendATCommand (char * s);
void SendCommand(char * s, int value);
void ReceiveCommand(void);
void ConfigJDY40(void);
void JDY_PWM_Transmission_Y(float y_value);
void JDY_PWM_Transmission_X(float x_value);
