#include"main.h"

unsigned char temp=0;

void main()
{
	Init_Timer0();
	while(1)
	{
		Display_Buffer_Change(0,0,3,4,5,6,7,8);
		Display();
//		KeyScan();
//		temp=DS18B20_Read();
	}
}