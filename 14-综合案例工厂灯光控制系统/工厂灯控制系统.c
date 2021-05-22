#include"reg52.h"
#include"intrins.h"

sbit S4=P3^3;
sbit S5=P3^2;

sfr AUXR=0x8e;

unsigned char code SMG_Duan[19]=
		{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
    0x80,0x90,0x88,0x80,0xc6,0xc0,0x86,0x8e,
    0xbf,0x7f,0x3f};
unsigned char stat_led = 0xff;		//定义LED灯当前开关状态	
unsigned char count=0,t_s=0,t_m=0,t_h=0;
		
		
void Delay()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 5;
	j = 52;
	k = 195;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}



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
		case 0:
			P2=(P2&0x1f)|0x00;
		break;
	}
}


//***********系统初始化函数***********
void InitSystem()
{

	SelectHC573(5);
	P0=0x00;
	
}
//********************************************

//**********CheckLED**************************
void CheckLED()
{
	char i;
	SelectHC573(4);
	for(i = 0; i < 9; i++)
	{
		stat_led = 0xfe << i;				//逐个点亮LED
		P0 = stat_led;
		Delay();
	}
	for(i = 0; i < 9; i++)
	{
		stat_led = ~(0xfe << i);		//逐个熄灭LED
		P0 = stat_led;
		Delay();
	}
	SelectHC573(0);
}

//*********************************************


//**********CheckSMG*************************
void CheckSMG()
{
	char i;
	SelectHC573(7);
	P0 = 0x00;
	for(i = 0; i < 9; i++)
	{
		SelectHC573(6);
		P0 = 0x01 << i;			//逐个点亮数码管
		Delay();
	}
	for(i = 0; i < 9; i++)
	{
		SelectHC573(6);
		P0 = ~(0x01 << i);					//逐个熄灭数码管
		Delay();
	}
	SelectHC573(0);
}



//**********定时器函数************************
void Init_Timer0()
{
	TMOD=0x21;
	TH1=(65535-50000)/256;   //50ms
	TL1=(65535-50000)%256;
	
	ET0=1;
	EA=1;
	TR0=1;
}

void Server_Timer0() interrupt 1
{
	TH1=(65535-50000)/256;   //50ms
	TL1=(65535-50000)%256;
	
	count++;
	if(count==20)
	{
		t_s++;
		count=0;
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

//********************************************

//*********数码管显示函数*********************
void DelaySMG(unsigned char t)
{
	while(t--);
}

void SMGDisplay_Bit(unsigned char i,unsigned char value)
{
	SelectHC573(6);
	P0=0x01<<i;
	SelectHC573(7);
	P0=value;
//	DelaySMG(500);
}

void SMGDisplay()
{
	SMGDisplay_Bit(0,SMG_Duan[t_h/10]);
	DelaySMG(500);
	SMGDisplay_Bit(1,SMG_Duan[t_h%10]);
	DelaySMG(500);
	
	SMGDisplay_Bit(2,SMG_Duan[16]);
	DelaySMG(500);
	
	SMGDisplay_Bit(3,SMG_Duan[t_m/10]);
	DelaySMG(500);
	SMGDisplay_Bit(4,SMG_Duan[t_m%10]);
	DelaySMG(500);
	
	SMGDisplay_Bit(5,SMG_Duan[16]);
	DelaySMG(500);
	
	SMGDisplay_Bit(6,SMG_Duan[t_s/10]);
	DelaySMG(500);
	SMGDisplay_Bit(7,SMG_Duan[t_s%10]);
	DelaySMG(500);
}
//*******************************************

//*******************独立按键****************
void ScanKeys()
{
	if(S5 == 0)							//检测S5信号
	{
		SMGDisplay();				//消抖
		if(S5 == 0)						//确认信号
		{
			while(S5 == 0)			//等待S5松开
			{
				SMGDisplay();	
			}
			SelectHC573(4);        //松开后在选通LED
			stat_led = (stat_led | 0x40) & (~stat_led | 0xbf);    
			P0 = stat_led;			//执行灯光状态
			SelectHC573(0);     //关闭外设
		}
	}
	
	if(S4 == 0)							
	{
		SMGDisplay();					
		if(S4 == 0)						
		{
			while(S4 == 0)			
			{
				SMGDisplay();	
			}
			SelectHC573(4);
			stat_led = (stat_led | 0x80) & (~stat_led | 0x7f); 
			P0 = stat_led;			
			SelectHC573(0);
		}
	}
}

//*******************串口相关********************************

void Init_Uart()
{
	TMOD=0x21;
	TH1=0xfd;
	TL1=0xfd;
	
	TR1=1;      //打开定时器T1
	SCON=0x50;  //8位自动重装
	AUXR=0x00;  //辅助寄存器初始化为0
	ES=1;       //打开串口
	EA=1;      
}

unsigned char command=0x00;  //存放上位机命令变量

void Serve_Uart() interrupt 4
{
	if(RI==1)    //判断是接收进入单片机
	{
		command = SBUF;  //读命令
		RI=0;            //清零标志位
	}
}

void SendByte(unsigned char dat)
{
	SBUF=dat;
	while(TI==0);  //读入命令直到TI变为1即命令全部发送
	TI=0;          //手动清零
}

void ExecuteCommand()  //执行上位机的命令
{
	if(command!=0x00)
	{
		switch(command & 0xf0)  //根据具体命令选出类型，因为本设计高四位是命令类型，所以选出高四位
		{
			case 0xa0:
				SelectHC573(4);
				stat_led=(stat_led|0x0f)&(~command|0xf0);  //保持LED灯的其他
				P0=stat_led;
			SelectHC573(0);
			command=0x00;
			break;
			case 0xb0:  
				SendByte((t_h / 10 << 4) | (t_h % 10));
				SendByte((t_m / 10 << 4) | (t_m % 10));
				SendByte((t_s / 10 << 4) | (t_s % 10));
		
			command=0x00;
			break;
		}
		
	} 
}


//*************************************************************


void main()
{
	InitSystem();
	CheckLED();
	CheckSMG();
	Init_Timer0();
	Init_Uart();
//	SendByte('A');
	while(1)
	{
		SMGDisplay();
		ScanKeys();
		ExecuteCommand();
	}
}