#ifndef _SMG_H_
#define _SMG_H_

#include"common.h"

void Display_Bit(unsigned char pos,value);  //数码管按位显示
void Display_DT(); //动态显示
void Display_Buffer_Change(unsigned char d0,d1,d2,d3,d4,d5,d6,d7);  //显示存储转换

#endif