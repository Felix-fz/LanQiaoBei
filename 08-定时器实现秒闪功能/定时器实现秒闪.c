#include"reg52.h"

sbit L1=P0^0;
sbit L8=P0^7;

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

/******************************************************************
 *该函数是用定时器0定时0.5s，采用10次每次定时50ms
 *
********************************************************************/
//初始化函数配置定时器
void InitTimer0()
{
	TMOD=0x01;   //不能位操作一次性写入
	TH0=(65535-50000)/256;  //16位最大定时是65.5ms,对于大于65.5ms的采用多次定时
	TH0=(65535-50000)%256;
	
	ET0=1;
	EA=1;
	TR0=1;
}

//unsigned char count = 0;  //计数中断次数->得到计数0.5s
//unsigned char count1 = 0;   //得到计数10s
//void ServiceTimer0() interrupt 1    //中断服务函数(共五个中断源，注意定数器0在第一个中断源)
//{
//	TH0=(65535-50000)/256;  //重装初值，因为无法自动重装
//	TH0=(65535-50000)%256;
//	
//	count++;
//	count1++;
//	if(count == 10)  //50ms*10=500ms=0.5s
//	{
//		L1=~(L1);
//		count=0;
//	}
//	if(count1 == 100)  //50ms*100=5000ms=5s
//	{
//		L8 = ~(L8);
//		count1 = 0;
//	}
//}


//优化中断服务函数
unsigned char count = 0;  
void ServiceTimer0() interrupt 1    //中断服务函数(共五个中断源，注意定数器0在第一个中断源)
{
	TH0=(65535-50000)/256;  //重装初值，因为无法自动重装
	TH0=(65535-50000)%256;
	
	count++;
	if(count%10==0)  //100里面10的倍数
	{
		L1=~(L1);
	}
	if(count == 100)  //50ms*100=5000ms=5s
	{
		L8 = ~(L8);
		count = 0;
	}
	
}

//错误代码，不能写到中断服务函数外面
//void LEDWorking()
//{
//	if(count%10==0)  //100里面10的倍数
//	{
//		L1=~(L1);
//	}
//	if(count == 100)  //50ms*100=5000ms=5s
//	{
//		L8 = ~(L8);
//		count = 0;
//	}
//}


void main()
{
	InitTimer0();
	while(1)
	{
		SelectHC573(4);
//		LEDWorking();
	}
}