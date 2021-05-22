/*
  程序说明: IIC总线驱动程序
  软件环境: Keil uVision 4.10 
  硬件环境: CT107单片机综合实训平台 8051，12MHz
  日    期: 2011-8-9
*/

#include "iic.h"


#define somenop Delay5us()   


#define SlaveAddrW 0xA0
#define SlaveAddrR 0xA1

//总线引脚定义
sbit SDA = P2^1;  /* 数据线 */
sbit SCL = P2^0;  /* 时钟线 */


//总线启动条件
void IIC_Start(void)
{
	SDA = 1;
	SCL = 1;
	somenop;
	SDA = 0;
	somenop;
	SCL = 0;	
}

//总线停止条件
void IIC_Stop(void)
{
	SDA = 0;
	SCL = 1;
	somenop;
	SDA = 1;
}

//应答位控制
void IIC_Ack(bit ackbit)
{
	if(ackbit) 
	{	
		SDA = 0;
	}
	else 
	{
		SDA = 1;
	}
	somenop;
	SCL = 1;
	somenop;
	SCL = 0;
	SDA = 1; 
	somenop;
}

//等待应答
bit IIC_WaitAck(void)
{
	SDA = 1;
	somenop;
	SCL = 1;
	somenop;
	if(SDA)    
	{   
		SCL = 0;
		IIC_Stop();
		return 0;
	}
	else  
	{ 
		SCL = 0;
		return 1;
	}
}

//通过I2C总线发送数据
void IIC_SendByte(unsigned char byt)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{   
		if(byt&0x80) 
		{	
			SDA = 1;
		}
		else 
		{
			SDA = 0;
		}
		somenop;
		SCL = 1;
		byt <<= 1;
		somenop;
		SCL = 0;
	}
}

//从I2C总线上接收数据
unsigned char IIC_RecByte(void)
{
	unsigned char da;
	unsigned char i;
	
	for(i=0;i<8;i++)
	{   
		SCL = 1;
		somenop;
		da <<= 1;
		if(SDA) 
		da |= 0x01;
		SCL = 0;
		somenop;
	}
	return da;
}

unsigned char PCF8591_ADC(unsigned char addr)  //返回的是0-255之间的数字，要算电压要3*值/256
{
	unsigned char dat;  //接收数据的变量
	//写数据
	IIC_Start();  //IIC开始工作
	IIC_SendByte(0x90);   //告诉IIC，PCF8591地址，w
	IIC_WaitAck();    //等待应答
	
	IIC_SendByte(addr);  //选择要读的AIN口
	IIC_WaitAck(); 
	
	IIC_Stop();       //IIC总线空置
	
	//读数据
	IIC_Start();
	IIC_SendByte(0x91);  //R 
	IIC_WaitAck(); 
	dat=IIC_RecByte();
	IIC_Ack(0);  //单片机应答PF8591
	IIC_Stop();   
	
	return dat;
}


void PCF8591_DAC(unsigned char dat)  //DA
{
	IIC_Start();  //IIC开始工作
	IIC_SendByte(0x90);   //告诉IIC，PCF8591地址，w
	IIC_WaitAck();    //等待应答
	
	IIC_SendByte(0x40);  //告诉芯片是数字量转模拟量
	IIC_WaitAck(); 

	IIC_SendByte(dat);  //发送8位电压数据，不能是浮点数啥的
	IIC_WaitAck(); 
	IIC_Stop();   

}


unsigned char E2Prom_Read(unsigned char addr)  //e2prom读出函数
{
	unsigned char dat;  //接收数据的变量

	IIC_Start();  //IIC开始工作
	IIC_SendByte(0xa0);   //告诉IIC，AT24C02地址，w
	IIC_WaitAck();    //等待应答
	
	IIC_SendByte(addr);  //要读出数据地址
	IIC_WaitAck(); 
	
	IIC_Stop();       //IIC总线空置
	
	//读数据
	IIC_Start();
	IIC_SendByte(0xa1);  //R数据 
	IIC_WaitAck(); 
	dat=IIC_RecByte();
	IIC_Ack(0);  //单片机应答AT24C02
	IIC_Stop();   
	
	return dat;
}


void E2Prom_Write(unsigned char addr,dat)  //写入e2prom
{
	IIC_Start();  //IIC开始工作
	IIC_SendByte(0xa0);   //告诉IIC，AT24C02地址，w
	IIC_WaitAck();    //等待应答
	
	IIC_SendByte(addr);  //告诉芯片数据在芯片内存储的位置
	IIC_WaitAck(); 

	IIC_SendByte(dat);  //所存储的数据发给芯片
	IIC_WaitAck(); 
	IIC_Stop();   
}
