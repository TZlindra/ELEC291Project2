#include <EFM8LB1.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void UART1_Init(unsigned long baudrate);
void JDYInit(void);

void putchar1(char c);
void sendstr1(char * s);
char getchar1(void);
char getchar1_with_timeout(void);
void getstr1(char* s);
bit RXU1(void);
void waitms_or_RI1(unsigned int ms);
void SendATCommand(char * s);
void SendFreq(int freq);
void GetData(void);

void TX_I(void);
void RX_Data(void)