/************************
*单片机中断计时+数码管显示
**************************/

#include"reg52.h"

sbit S4=P3^3;
sbit S5=P3^2;

unsigned char code SMG_Duanma[18] = 
		{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
		0x80,0x90,0x88,0x80,0xc6,0xc0,0x86,0x8e,
    0xbf,0x7f};
		
unsigned char t_fen=0;
unsigned char t_miao=0;
unsigned char t_005miao=0;

void SelectHC573(unsigned char channel)
{
	switch(channel)
	{
		case 4:
			P2=(P2&0x1f)|0x80;
			break;
		case 5:
			P2=(P2&0x1f)|0xa0;
			break;
		case 6:
			P2=(P2&0x1f)|0xc0;
			break;
		case 7:
			P2=(P2&0x1f)|0xe0;
			break;
	}
}

void Display_bit(unsigned char value, unsigned char pos)
{
	SelectHC573(6);   //位选
	P0=0x01 << pos;   //0x01是点亮第一位数码管，<<左移pos位
	SelectHC573(7);    //段选
	P0=value;
}


void DelaySMG(unsigned int t)
{
	while(t--);
}

void DisplayTime()
{
	
	
	Display_bit(SMG_Duanma[t_005miao%10],7);
	DelaySMG(500);
	Display_bit(SMG_Duanma[t_005miao/10],6);
	DelaySMG(500);
	Display_bit(SMG_Duanma[16],5);
	DelaySMG(500);
	
	Display_bit(SMG_Duanma[t_miao%10],4);
	DelaySMG(500);
	Display_bit(SMG_Duanma[t_miao/10],3);
	DelaySMG(500);
	Display_bit(SMG_Duanma[16],2);
	DelaySMG(500);
	
	Display_bit(SMG_Duanma[t_fen%10],1);
	DelaySMG(500);
	Display_bit(SMG_Duanma[t_fen/10],0);
	DelaySMG(500);	
}

//************定时器函数***********
void  Init_Timer0()
{
	TMOD=0x01;
	TH0=(65535-50000)/256;  //设置50ms
	TL0=(65535-50000)%256;
	
	ET0=1;
	EA=1;
	TR0=1;
}

void ServiceTimer0() interrupt 1
{
	TH0=(65535-50000)/256;  //设置50ms
	TL0=(65535-50000)%256;
	
	t_005miao++;    //0.05s
	if(t_005miao==20)  
	{
		t_miao++;
		t_005miao=0;
	}	
	if(t_miao==60)
	{
		t_fen++;
		t_miao=0;
	}
	if(t_fen==99)
	{
		t_fen=0;
	}
}

//*********************************

void Delay(unsigned char t)
{
	while(t--);
}

void ScanKeys()
{
	if(S4==0)   //秒表启动与暂停
	{
		Delay(100);
		if(S4==0)
		{
			TR0=~(TR0);  //开关定时器
			while(S4==0)
			{
				DisplayTime();
			}
		}
	}
	
	if(S5==0)   //秒表清零
	{
		Delay(100);
		if(S5==0)
		{
			t_005miao=0;
			t_miao=0;
			t_fen=0;
			while(S5==0)
			{
				DisplayTime();
			}
		}
	}
}


void main()
{
	Init_Timer0();
	while(1)
	{
		DisplayTime();
		ScanKeys();
	}
}