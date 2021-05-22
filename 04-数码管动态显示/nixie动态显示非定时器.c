#include<STC15F2K60S2.H>
#include"intrins.h"



//段码设置好不会再变，设置表格形式减少内存
unsigned char code SMG_Duanma[20] = 
   {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
    0x80,0x90,0x88,0x80,0xc6,0xc0,0x86,0x8e,
    0xbf,0x7f,0x3f,0xff};
void DisplaySMG_DT();		
unsigned char display_buffer[8]={0,0,0,0,0,0,0,0};

unsigned char cnt=0;
unsigned char t_s=0,t_m=0,t_h=0;

void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}
	
void SelectHC573(unsigned char channel)
{
	switch(channel)
	{
		case 4:
			P2=(P2 & 0x1f)| 0x80;
			break;
		case 5:
			P2=(P2 & 0x1f)| 0xa0;
			break;
		case 6:
			P2=(P2 & 0x1f)| 0xc0;
			break;
		case 7:
			P2=(P2 & 0x1f)| 0xe0;
			break;
		case 0:
			P2=(P2 & 0x1f)|0x00;
	}
}

void DisplaySMG_Bit(unsigned char value , unsigned char pos)
{
	SelectHC573(7);
	P0=0xff;   //消影
	SelectHC573(6);
	P0 = 0x01 << pos;     //选择位置
	SelectHC573(0);
	SelectHC573(7);
	P0 = value;    //选择该位显示的内容
}


void Display_SMG_Buffer_Change(unsigned char d0,d1,d2,d3,d4,d5,d6,d7)
{
	display_buffer[0]=d0;
	display_buffer[1]=d1;
	display_buffer[2]=d2;
	display_buffer[3]=d3;
	display_buffer[4]=d4;
	display_buffer[5]=d5;
	display_buffer[6]=d6;
	display_buffer[7]=d7;
	DisplaySMG_DT();
}

//*******************非中断函数**********************


//void DisplaySMG_DT()
//{
//	DisplaySMG_Bit(SMG_Duanma[display_buffer[0]],0);
//	Delay();
//	DisplaySMG_Bit(SMG_Duanma[display_buffer[1]],1);
//	Delay();
//	DisplaySMG_Bit(SMG_Duanma[display_buffer[2]],2);
//	Delay();
//	DisplaySMG_Bit(SMG_Duanma[display_buffer[3]],3);
//	Delay();
//	
//	DisplaySMG_Bit(SMG_Duanma[display_buffer[4]],4);
//	Delay();
//	DisplaySMG_Bit(SMG_Duanma[display_buffer[5]],5);
//	Delay();
//	
//	DisplaySMG_Bit(SMG_Duanma[display_buffer[6]],6);
//	Delay();
//	DisplaySMG_Bit(SMG_Duanma[display_buffer[7]],7);
//	Delay();
//}

void DisplaySMG_DT()
{
	unsigned char num=0;
	while(num<8)
	{
		DisplaySMG_Bit(SMG_Duanma[display_buffer[num]],num);
		Delay1ms();
		num++;
	}
	if(num==8)
		num=0;
}



void DelaySMG(unsigned int t)
{
	while(t--)
	{
		DisplaySMG_DT();
	}
}

void Init_Timer0()
{
	TMOD=0x01;
	TH0=(65535-50000)/256;
	TL0=(65535-50000)%256;
	
	ET0=1;
	TR0=1;
	EA=1;
}

void Server_Timer0() interrupt 1
{
	TH0=(65535-50000)/256;
	TL0=(65535-50000)%256;
	
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




void main()
{
	unsigned char t_t=60;
	SelectHC573(4);
	P0=0xff;
	Init_Timer0();

	while(1)
	{
		Display_SMG_Buffer_Change((t_h/10),(t_h%10),16,(t_m/10),(t_m%10),16,(t_s/10),(t_s%10));
		
		DelaySMG(10);
	}
}






































