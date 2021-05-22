#include"main.h"

void main()
{
	unsigned char tempature;
	Init_Timer0();
	while(1)
	{
		if(timer0_flag==1)  //保证读取温度在两个中断之间
		{
			tempature=Read_Temperature();
			timer0_flag=0;
		}
		
		Display_Buffer_Change(t_m/10,t_m%10,16,t_s/10,t_s%10,16,tempature/10,tempature%10);
	}
}
	
	