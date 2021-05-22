#include"reg52.h"

sbit L1=P0^0;
sbit S7=P3^0;

unsigned char cnt=0;
unsigned char pwm_duty=0;

void SelectHC573(unsigned char channel)
{
	switch(channel)
	{
		case 4:
			P2=(P2&0x1f)|0x80;
		break;
	}
}

//*****************定时器相关函数*****************
void Init_Timer0()
{
	TMOD=0x01;    //选16位重装，8位自动重装更好
	TH0=(65535-100)%256;  //100us的中断
	TL0=(65535-100)/256;

	ET0=1;
	EA=1;
//	TR0=1;  //可以打开，但是在本题可以在产生脉宽调制时再打开
}

void ServiceTimer0() interrupt 1
{
	TH0=(65535-100)%256;  
	TL0=(65535-100)/256;
	
	cnt++;
	if(cnt<=pwm_duty)
	{
		L1=0;
	}
	else if(cnt<100)
	{
		L1=1;
	}
	else if(cnt==100)
	{
		L1=0;
		cnt=0;
	}
}



//*************************************************


//************************按键相关函数**************
void Delay(unsigned char t)
{
	while(t--);
}

unsigned char state=0;

void KeyScan()
{
	if(S7==0)
	{
		Delay(100);
		if(S7==0)
		{
			switch(state)
			{
				case 0:     //按下按键才亮并且定时器打开，脉宽位10%
					L1=0;
					TR0=1;
					pwm_duty=10;
				  state=1;    //状态1
				break; 
				
				case 1:
					pwm_duty=50;
					state=2;
				break;
				
				case 2:
					pwm_duty=90;
					state=3;
				break;
				
				case 3:
					L1=1;  //关灯
					TR0=0; //关定时器
					state=0;
				break;
			}
			while(S7 == 0);
		}
	}
}

//************************************************





void main()
{
	SelectHC573(4);
	Init_Timer0();
	while(1)
	{
		KeyScan();
	}
}