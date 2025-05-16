
#ifndef __BSP_CAN_H
#define __BSP_CAN_H
 
#include "stm32f10x.h"
 
 
void CAN1_Init(void);
u8 Can_Send_Msg_TEXT(uint32_t id,u8 length,u8* msg);
 
#endif
