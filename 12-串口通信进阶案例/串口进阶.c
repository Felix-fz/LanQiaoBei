#include"reg52.h"

//sfr AUXR= 0x8e;

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
		case 0:   //所有锁存器都关闭
			P2=(P2&0x1f)|0x00;
		break;
	}		
}

void InitSystem()  
{
	SelectHC573(5);  //关闭蜂鸣器和继电器
	P0=0x00;
	SelectHC573(4);
	P0=0xff;
}

//****************串口相关代码***************
void InitUart()
{
	TMOD = 0x20;
	TH1=0xfd;  //9600
	TL1=0xfd;
	TR1=1;   //Open Timer
	
	SCON=0x50; //配置串口位模式1(八位自动重装模式)
	AUXR=0x00;
	
	ES=1;
	EA=1;
}

unsigned char command =0x00; //存放上位机命令的变量

void ServiceUart() interrupt 4
{
	if(RI==1)    //单片机是接收完成进入的中断
	{
		command = SBUF; //读出
		RI=0;  //表示位清零
	}
	
	
//	if(TI==1)  //发送完成进入中断的
//	{
//	}
}

void SendByte(unsigned char dat)
{
	SBUF=dat;
	while(TI==0);  //要等TI==1就发完即跳出循环
	TI=0; //手动清零
}

void SendString(unsigned char *str)  //
{
	while(*str !='\0')
	{
		SendByte(*str++);
	}	
}

//*******************************************

void Working()   //翻译上位机命令
{
	if(command != 0x00)
	{
		switch(command & 0xf0)   //选出command的高四位
		{
			case 0xa0:
				P0=(P0|0x0f)&(~command|0xf0);
				command=0x00;
			break;
			case 0xb0:
				P0=(  P0|0xf0)&((~command<<4)|0x0f);
				//P0=(~command|0x0f)&(P0|0xf0);
				command=0x00;
			break;
			case 0xc0:
				SendString("The System is Running...\r\n");
				command=0x00;   //command要清零，不然在main中while(1)循环
			break;
		}
	}
}


void main()
{
	InitSystem();
	InitUart();
	SendString("Welcome to Cople!\r\n");
	while(1)
	{
		Working();
	}
}