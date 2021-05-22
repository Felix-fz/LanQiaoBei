#include"common.h"

void Delay5us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 11;
	while (--i);
}


void SelectHC573(unsigned char channel)  //Ñ¡Í¨Ëø´æÆ÷º¯Êý
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
			P2=(P2&0x1f)|0xff;
		break;
	}
}