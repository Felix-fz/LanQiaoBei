#include"common.h"

void SelectHC573(unsigned char channel)
{
	switch(channel)
	{
		case 4:
			P2=(P2&0x1f)|0x80; //选出3位，|80使得第3位是1
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

//void Delay_Nixie(unsigned char t)
//{
//	while(t--);
//}
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
