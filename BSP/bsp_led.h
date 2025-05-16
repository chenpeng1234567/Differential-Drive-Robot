#ifndef _BSP_LED_H
#define _BSP_LED_H

/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

/* �궨�� --------------------------------------------------------------------*/
#define LED_GPIO_CLK              RCC_APB2Periph_GPIOC
#define BLED_PIN                  GPIO_Pin_13
#define LED_GPIO_PORT             GPIOC

///* LED���� */
#define BLED_ON()                  GPIO_SetBits(LED_GPIO_PORT, BLED_PIN)
#define BLED_OFF()                 GPIO_ResetBits(LED_GPIO_PORT, BLED_PIN)
#define BLED_TOGGLE()              (LED_GPIO_PORT->ODR ^= BLED_PIN)

void LED_Initializes(void);

#endif /* _BSP_LED_H */
