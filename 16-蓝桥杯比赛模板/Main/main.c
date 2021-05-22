#include<main.h>

//extern unsigned char state_INT;

void main()
{
	Init_INT0();
	while(1)
	{
//		SMG_Static();
		Working();
		LEDINT();
	}
}