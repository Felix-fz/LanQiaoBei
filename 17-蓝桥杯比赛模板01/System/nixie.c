#include"nixie.h"


unsigned char code duanma[20]=
		{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
    0x80,0x90,0x88,0x80,0xc6,0xc0,0x86,0x8e,
    0xbf,0x7f,0x3f,0xFF};
unsigned char display_buffer[8]={0,0,0,0,0,0,0,0};
		
void Display_Bit(unsigned char pos,unsigned char value)
{
	SelectHC573(6);
	P0=0x01<<pos;
	SelectHC573(7);
	P0=value;
}
void Display_Buffer_Change(unsigned char d0,d1,d2,d3,d4,d5,d6,d7)
{
	display_buffer[0]=d0;
	display_buffer[1]=d1;
	display_buffer[2]=d2;
	display_buffer[3]=d3;
	display_buffer[4]=d4;
	display_buffer[5]=d5;
	display_buffer[6]=d6;
	display_buffer[7]=d7;
}


void Display()
{
	unsigned char num=0;
	while(num<8)
	{
		Display_Bit(num,duanma[display_buffer[num]]);
		Delay1ms();
		num++;
	}
	if(num==8)
		num=0;
}