#include"interrupt.h"

sbit L1 = P0^0;
sbit L8 = P0^7;

void Init_INT0()
{
	IT0 = 1; 
	EX0 = 1; 
	EA = 1;  
}

unsigned char state_INT = 0;  

void ServiceINT0()  interrupt 0
{
	state_INT = 1; 
}

void LEDINT()
{
	if(state_INT == 1)
	{
		L8 = 0;
		Delay(100000000);
		Delay(100000000);
		Delay(100000000);
		Delay(100000000);
		L8 = 1;
	}
	state_INT = 0; //???????0
}

void Working()
{
	InitHC138(4);   //?????
	L1=0;
	Delay(100000000);
	Delay(100000000);
	L1=1;
	Delay(100000000);
	Delay(100000000);
}