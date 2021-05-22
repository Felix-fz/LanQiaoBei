#include"interrupt.h"

void Init_Timer0()   //1ms@11.0592
{
	AUXR |= 0x80;		
	TMOD &= 0xF0;		//16位自动
	TL0 = 0xCD;		
	TH0 = 0xD4;	
	
	TF0 = 0;		
	TR0 = 1;
	ET0=1;	 //中断0开关
	EA=1;
}

void Serve_Timer0() interrupt 1
{
	Display_DT();
	MatrixKeyScan();
}