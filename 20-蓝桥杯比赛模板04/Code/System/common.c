#include"common.h"

void SelectHC573(unsigned char channel)  //选通通道
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

void Delayms(unsigned char x)
{
    unsigned int i=0,j=0;
    for(i=0;i<x;i++)
        for(j=0;j<123;j++);

}