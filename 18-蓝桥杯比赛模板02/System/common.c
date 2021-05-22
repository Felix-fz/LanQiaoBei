#include"common.h"

void SelectHC573(unsigned char channel)
{
	switch(channel)
	{
		case 4:
			P2=(P2&0x1f)|0x80;
		break;
		case 5:
			P2=(P1&0x1f)|0xa0;
		break;
		case 6:
			P2=(P2&0x1f)|0xd0;
		break;
		case 7:
			P2=(P1&0x1f)|0xe0;
		break;
		case 0:
			P2=(P2&0x1f)|0xff;
		break;
	}
}