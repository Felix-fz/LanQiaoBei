#include"reg52.h"

sbit L1 = P0^0;
sbit L8 = P0^7;

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

void Delay(unsigned int t)
{
	while(t--);
}

void Working()
{
	SelectHC573(4);   //先选定串口
	L1=0;
	Delay(100000000);
	Delay(100000000);
	L1=1;
	Delay(100000000);
	Delay(100000000);
}

////中断法1
//void Init_INT0()//中断初始化
//{
//	IT0 = 1; //选择中断0是下降沿触发（=0就是低电平触发）
//	EX0 = 1; //打开外部使能
//	EA = 1;  //打开总开关
//}

//void ServiceINT0()  interrupt 0
//{
//	L8 = 0;
//	Delay(100000000);
//	Delay(100000000);
//	Delay(100000000);
//	Delay(100000000);
//	L8 = 1;
//}

//中断法2
void Init_INT0()//中断初始化
{
	IT0 = 1; //选择中断0是下降沿触发（=0就是低电平触发）
	EX0 = 1; //打开外部使能
	EA = 1;  //打开总开关
}

unsigned char state_INT = 0;  //设置中断标志变量
void ServiceINT0()  interrupt 0
{
	state_INT = 1; //中断产生时标志位变，中断服务函数少做事情，不影响程序的实时性
}

void LEDINT()
{
	if(state_INT == 1)
	{
		L8 = 0;
		Delay(100000000);
		Delay(100000000);
		Delay(100000000);
		Delay(100000000);
		L8 = 1;
	}
	state_INT = 0; //做完中断状态归0
}

void main()
{
	Init_INT0();  //打开开关
	while(1)
	{
		Working();
		LEDINT();    //由于引入中断状态变量，每次中断产生都是在完整执行一次Working之后
	}
}