/*
流水灯闪三下，在做流水
*/

#include"reg52.h"

sbit  HC138_A = P2^5;
sbit  HC138_B = P2^6;
sbit  HC138_C = P2^7;

//关闭蜂鸣器外设
void cls_buzz(void)
{
	P2 = (P2&0x1F|0xA0);
	P0 = 0x00;
	P2 &= 0x1F;
}

void Delay(unsigned int t)
{
	while(t--);
	while(t--);
}

void LEDRunning()
{
	int i;
	HC138_A = 0;
	HC138_B = 0;
	HC138_C = 1;
	for(i=0;i<3;i++)
	{
		P0=0x00;
		Delay(60000);
		P0=0xff;
		Delay(60000);	
	}
	for(i=3;i<=8;i++)
	{
		P0 = 0xff<<i;
		Delay(60000);
		Delay(60000);
	}
	for(i=1;i<=8;i++)
	{
		P0 = ~(0xff<<i);
		Delay(60000);
		Delay(60000);
	}
	
}

void main()
{
	cls_buzz();
	while(1)
	{
		LEDRunning();
	}
}