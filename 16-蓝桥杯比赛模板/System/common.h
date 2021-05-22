#ifndef _COMMON_H_
#define _COMMON_H_

#include<STC15F2K60S2.h>  
#include<intrins.h>

#define uchar unsigned char
#define uint unsigned int

void Delay(uint t);
void InitHC138(unsigned char n);

#endif