#include"key.h"

sbit S5=P3^2;
sbit S4=P3^3;

void KeyScan()
{
	if(S4==0)
	{
//		Delay_Nixie(100);
		Display();
		if(S4==0)
		{
			t_s=0;
			t_m=0;
			t_h=0;
		}
		while(S4==0)
		{
			Display();
		}
	}
	if(S5==0)
	{
//		Delay_Nixie(100);
		Display();
		if(S5==0)
		{
			TR0=~(TR0);
		}
		while(S5==0)
		{
			Display();
		}
	}
}