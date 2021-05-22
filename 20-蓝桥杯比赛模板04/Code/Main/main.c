#include"main.h"


void main()
{
	Init_Timer0();
	while(1)
	{
		if(keyflag==1)  // 判断按键标志位
		{
			KeyEliminatBuffet();
			Display_Buffer_Change(0,0,0,0,0,0,keyvalue/10,keyvalue%10);
			keyflag=0;    // 标志位归零，重新开始扫描
		}
//		MatrixKeyScanNi();
//		Display_Buffer_Change(0,0,0,0,0,0,keyvalue/10,keyvalue%10);
	}
}