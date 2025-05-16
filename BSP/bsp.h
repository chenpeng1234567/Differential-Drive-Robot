#ifndef _BSP_H
#define _BSP_H

/* 包含的头文件 --------------------------------------------------------------*/
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_lcd.h"
#include "bsp_adc.h"
#include "bsp_delay.h"
#include "bsp_nrf.h"
#include "bsp_can.h"
/* 函数申明 ------------------------------------------------------------------*/
void BSP_Init(void);

#endif /* _BSP_H */
