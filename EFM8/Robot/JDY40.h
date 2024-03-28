#include <EFM8LB1.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void putchar1(char c);
void sendstr1(char * s);
char getchar1(void);
char getchar1_with_timeout(void);

void getstr1(char* s);
bit RXU1(void);
void waitms_or_RI1(unsigned int ms);
void SendATCommand(char * s);

void TX_Freq(int freq);
void TX_I(void);
void RX_Data(void)