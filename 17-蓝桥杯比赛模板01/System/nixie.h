#ifndef _NIXIE_H_
#define _NIXIE_H_

#include"common.h"
#include"interrupt.h"

void Display_Bit(unsigned char pos,unsigned char value);
void Display_Buffer_Change(unsigned char d0,d1,d2,d3,d4,d5,d6,d7);
void Display();

extern unsigned char t_s, t_m, t_h;
extern unsigned char temp;
#endif