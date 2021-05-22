#include"reg52.h"

void Delay(unsigned char t)
{
	while(t--);
	while(t--);
}

void SelcetHC573(unsigned char channel)
{
	switch(channel)
	{
		case 4:
			P2=(P2 & 0x1f)|0x80;
		break;
		case 5:
			P2=(P2 & 0x1f)|0xa0;
		break;
		case 6:
			P2=(P2 & 0x1f)|0xc0;
		break;
		case 7:
			P2=(P2 & 0x1f)|0xe0;
		break;
	}
	
}

void LEDRunning()
{
	SelcetHC573(4);
	P0=0xf0;
	Delay(60000);
	Delay(60000);
	P0=0x0f;
	Delay(60000);
	Delay(60000);
	P0=0xff;
	Delay(60000);
	Delay(60000);
}

void SMGRunning()
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		SelcetHC573(6);
		P0=0x01<<i;
		SelcetHC573(7);
		P0=0x00;
		Delay(60000);
		Delay(60000);
	}	
	P0=0xff;
	Delay(60000);
	Delay(60000);
}

void main()
{
	while(1)
	{
		LEDRunning();
		SMGRunning();
	}
}