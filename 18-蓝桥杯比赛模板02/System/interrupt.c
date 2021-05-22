#include"interrupt.h"

unsigned int cnt=0;
unsigned char t_s=0,t_m=0,t_h=0;
bit timer0_flag=0;   //中断标志位

void Init_Timer0()		//1ms@11.0592MHz
{
	AUXR |= 0x80;		
	TMOD &= 0xF0;		    //16位自动重载模式
	TL0 = 0xCD;		
	TH0 = 0xD4;		
	TF0 = 0;		        //清除标志位
	TR0 = 1;	          //打开定时器0
	
	ET0=1;
	EA=1;
}


void Serve_Timer0() interrupt 1
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
	if(t_m==60)
	{
		t_h++;
		t_m=0;
	}
	Display_SMG_DT();
	
	timer0_flag=1;
}