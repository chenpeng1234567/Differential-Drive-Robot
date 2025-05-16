#include "bsp_led.h"

/************************************************
函数名称 ： LED_Initializes
功    能 ： LED初始化
参    数 ： 无
返 回 值 ： 无
*************************************************/
void LED_Initializes(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(LED_GPIO_CLK,ENABLE);        //开启时钟
	
	GPIO_InitStruct.GPIO_Pin = BLED_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;                                 //推挽输出
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(LED_GPIO_PORT,&GPIO_InitStruct);                                            //初始化IO
}

 
