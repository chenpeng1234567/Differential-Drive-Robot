#ifndef _BSP_SPI_H
#define _BSP_SPI_H
#include "bsp_sys.h"
	  
// SPI�����ٶ�����  
 				  
void SPI1_Init(void);			 //��ʼ��SPI��
void SPI1_SetSpeed(u8 SpeedSet); //����SPI�ٶ�   
u8 SPI1_ReadWriteByte(u8 TxData);//SPI���߶�дһ���ֽ�
		 
#endif


