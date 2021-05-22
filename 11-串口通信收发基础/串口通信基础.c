#include "reg52.h"
#include "stdio.h"

sfr AUXR=0x8e; //51单片机没有要设置地址

sbit S7=P3^0;

unsigned char urdat;
unsigned char Adata=0;
void SendByte(unsigned char dat);

void Delay(unsigned char t)
{
	while(t--);
}

void KeyScan()
{
	
	if(S7==0)
	{
		Delay(100);
		if(S7==0)
		{
			Adata++;

			while(S7==0);
			SendByte(Adata);			
		}
	}
}


//串口初始化函数
void InitUart()
{
	TMOD = 0x20;  //选择8位自动重装
	TH1=0xfd;  //查手册
	TL1=0xfd;  //重装模式下二者一样
	
	TR1=1;
	SCON=0x50;
	AUXR=0x00;
	
	ES=1;
	EA=1;
		
}



//接收时要用到中断服务函数
void ServiceUart() interrupt 4
{
	if(RI == 1)  //数据接收完毕，TI==1发送完毕
	{
		RI=0;   //完成清零
		urdat=SBUF;  //读出
		SendByte(urdat); //接收之后要发送
	}
}

//查询发送
void SendByte(unsigned char dat)
{
	SBUF=dat;
	while(TI==0);
	TI=0;
}

void SendStr(char *s)
{
	while(*s)
	{
		SendByte(*s++);
	}
}

void main()
{
	unsigned int tim=0;
	unsigned int i=0;
	unsigned char str[35];
	InitUart();
//	SendByte(0x5a);
//	SendByte(0xa5);
	
	while(1)
	{
		tim++;
//		KeyScan();
		sprintf(str,"%d",tim);
		SendStr(str);
		for(i=0;i<60000;i++);
//		for(i=0;i<60000;i++);
//		for(i=0;i<60000;i++);
//		for(i=0;i<60000;i++);
		
	}
}