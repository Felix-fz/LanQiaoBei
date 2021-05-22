#include"main.h"

unsigned char tmp=0,iic_temp;

void main()
{
	SelectHC573(4);
	P0=0xff;

	Init_Timer0();
	
	Init_DS1302(0x23,0x59,0x55);  //向时钟芯片写入时间数据23:59:55
	E2Prom_Write(0,11);
	PCF8591_DAC(100); //D->A 0.9V作用 3V在255份中占100份
	while(1)
	{
		if(timer0_flag==1)
		{
			tmp=E2Prom_Read();
//			tmp=rd_temperature(); 
//			DS1302_Read();
//			iic_temp=PCF8591_ADC(1); //AIN1
			timer0_flag=0;
			
		}

		Display_Buffer_Change(t_m/10,t_m%10,16,sec/16,sec%16,16,tmp/10,tmp%10);
//		Display_Buffer_Change(16,16,16,16,16,iic_temp/100,(iic_temp%100)/10,iic_temp%10);
	}
}