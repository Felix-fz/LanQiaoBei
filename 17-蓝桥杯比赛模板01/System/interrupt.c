#include"interrupt.h"

unsigned char cnt=0;
unsigned char t_s=0;
unsigned char t_m=0;
unsigned char t_h=0;

void Init_Timer0()
{
	TMOD=0x01;    //选择16位非自动重装模式
	TH1=(65535-50000)/256;
	TL1=(65535-50000)%256;
	
	ET0=1;
	TR0=1;
	EA=1;
}

void Serve_Timer0() interrupt 1
{
	TH1=(65535-50000)/256;
	TL1=(65535-50000)%256;
	
	cnt++;
	if(cnt==20)
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
}
	
