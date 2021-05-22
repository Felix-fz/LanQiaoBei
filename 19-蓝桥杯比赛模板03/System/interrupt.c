#include"interrupt.h"

unsigned int cnt=0;
unsigned char t_s=0,t_m=0;
bit timer0_flag=0;

void Init_Timer0()  //定时器0初始化函数
{
	AUXR |= 0x80;		
	TMOD &= 0xF0;		  //16位自动重装
	TL0 = 0xCD;		
	TH0 = 0xD4;		
	TF0 = 0;		
	TR0 = 1;	
	
	ET0=1;
	EA=1;
}


void Server_Timer0() interrupt 1
{
	cnt++;
	if(cnt==1000)
	{
		t_s++;
		cnt=0;
	}
	if(t_s==60)
	{
		t_m++;
		t_s=0;
	}
	Display_DT();
	timer0_flag=1;    //中断执行完等于1
}