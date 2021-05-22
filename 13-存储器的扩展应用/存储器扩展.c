#include"reg52.h"
#include"absacc.h"
#include"intrins.h"


void Delay()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 43;
	j = 6;
	k = 203;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}



void LEDRunning()
{
	XBYTE[0x8000]=0xf0;
	Delay();
	XBYTE[0x8000]=0x0f;
	Delay();
	XBYTE[0x8000]=0xff;
	Delay();

}

void SMGRunning()
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		XBYTE[0xc000]=0x01<<i;
		XBYTE[0xe000]=0x00;
		Delay();
	
	}	
	XBYTE[0xe000]=0xff;
	Delay();

}

void main()
{
	while(1)
	{
		LEDRunning();
		SMGRunning();
	}
}