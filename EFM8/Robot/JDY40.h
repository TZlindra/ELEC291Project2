#include "global.h"

#define SYSCLK 72000000

void JDY_Timer3us(unsigned char us);
void JDY_Delayms(unsigned int ms);

void putchar1(char c);
void sendstr1(char * s);
char getchar1(void);
char getchar1_with_timeout(void);
void getstr1(char * s);
bit RXU1(void);

void waitms_or_RI1(unsigned int ms);
void SendATCommand(char* s);

void Update_I(int inductance);

void RX_Data(void);
void TX_I(void);
void display_buffs(void);


int searchI(const char* array);
