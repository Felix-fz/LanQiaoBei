#include"SMG.h"


unsigned char code SMG_Duanma[18] = 
   {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
    0x80,0x90,0x88,0x80,0xc6,0xc0,0x86,0x8e,
    0xbf,0x7f};
		
void ShowSMG_Bit(unsigned char dat, unsigned pos)
{
	InitHC138(6);  //??????
	P0 = 0x01 << pos;
	InitHC138(7);  //??????
	P0 = dat;
}

void SMG_Static()
{
  char i,j;  //??,?????
	for(i = 0; i < 8; i++)
	{
		for(j = 0;j < 10; j++)
		{
			ShowSMG_Bit(SMG_Duanma[j],i);
			Delay(60000);
		}
	}
  
	for(j = 0;j < 16; j++)
	{
		InitHC138(6);  //??????
		P0 = 0xff;
		InitHC138(7);  //??????
		P0 = SMG_Duanma[j];
		Delay(600000000);
		Delay(600000000);
		Delay(600000000);
		Delay(600000000);
	}
	
}