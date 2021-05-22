#include"reg52.h"
#include"intrins.h"

sbit SDA=P2^1;
sbit SCL=P2^0;

void Delay5us()		//@11.0592MHz
{
	;
	;
}

void Start()
{
	SDA=1;
	Delay5us();
	SCL=1;
	Delay5us();
	SDA=0;
	Delay5us();
}

void Stop()
{
	SDA=0;
	Delay5us();
	SCL=1;
	Delay5us();
	SDA=1;
	Delay5us();
}

void Response()   //应答信号
{
	unsigned char i;
	SCL=1;
	Delay5us();
	while((SDA==1)&(i<250))
	{
		i++;
	}	
	SCL=0;
	Delay5us();
}

void Init()   //初始化总线
{
	SDA=1;
	SCL=1;
}

void Write_Byte(unsigned char dat)
{
	unsigned char i,temp;
	SCL=0;
	Delay5us();
	temp=dat;
	for(i=0;i<8;i++)
	{
		temp=temp<<1;
		SDA=CY;
		Delay5us();
		SCL=1;
		Delay5us();
		SCL=0;
		Delay5us();
	}
	SDA=1;
	Delay5us();
}

unsigned char Read_Byte()
{
	unsigned char i,j,k;
	SCL=0;
	Delay5us();
	SDA=1;
	Delay5us();
	for(i=0;i<8;i++)
	{
		SCL=1;
		Delay5us();
		j=SDA;
		if(j)
		k=(k<<1)|j;
		SCL=0;
		Delay5us();
	}
	return k;
}


void main()
{
	Init();
	Start();
	Write_Byte(0xa0);  //0xa0器件地址是a，0是下一次要写
	Response();
	Write_Byte(3); //写要写入芯片存储器地址
	Response();
	Write_Byte(0xfe); //写数据
	Response();
	Stop();
	
	Start();
	Write_Byte(0xa0);  //器件地址
	Response();
	Write_Byte(3); //写要写入芯片存储器地址
	Response();
	Start();
	Write_Byte(0xa1);  //换方向
	Response();
	P1=Read_Byte();
	Stop();
	while(1)
	{
		
	}
}