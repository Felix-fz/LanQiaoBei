#ifndef _IIC_H
#define _IIC_H

#include"common.h"

////º¯ÊýÉùÃ÷
//void IIC_Start(void); 
//void IIC_Stop(void);  
//void IIC_Ack(bit ackbit); 
//void IIC_SendByte(unsigned char byt); 
//bit IIC_WaitAck(void);  
//unsigned char IIC_RecByte(void); 

unsigned char PCF8591_ADC(unsigned char addr);
void PCF8591_DAC(unsigned char dat);
void E2Prom_Write(unsigned char addr,dat);  //Ð´Èëe2prom
unsigned char E2Prom_Read(unsigned char addr);

#endif
