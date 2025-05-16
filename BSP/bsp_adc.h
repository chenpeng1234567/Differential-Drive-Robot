#ifndef _BSP_ADC_H
#define _BSP_ADC_H	

/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
#include "stm32f10x_adc.h"
#include "stm32f10x_rcc.h"
#include "misc.h"

/* �������� ------------------------------------------------------------------*/
void Adc_Init(void);
u16 Get_X_Adc(void); 
u16 Get_Y_Adc(void); 

 
#endif /* _BSP_ADC_H */
