#include "global.h"

void JDY40Init(void);
void TIMER4_Init(void);

void putchar1(char c);
void sendstr1(char *s);
char getchar1(void);
char getchar1_with_timeout(void);
void getstr1(char *s);
bit RXU1(void);

void waitms_or_RI1(unsigned int ms);
void clearUART1Buffer(void);
void SendATCommand(char * s);

int stringToInt(char *str);
void splitString(const char *str, char *part1, char *part2);
void Trim(char *str, int *xin, int *yin);

void TX_I(void);
void RX_XY(void);

float get_x_direction(void);
float get_y_direction(void);
