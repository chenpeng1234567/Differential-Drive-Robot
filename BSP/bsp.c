#include "bsp.h"

/************************************************
函数名称 ： BSP_Init
功    能 ： 底层驱动初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： MLY
*************************************************/
void BSP_Init(void)
{
	
	NRF24L01_Init();    	//初始化NRF24L01  
	delay_init();	    		//延时函数初始化	 
	uart_init(100000);		//初始化串口1
	LED_Initializes();		//初始化LED
	uart2_init(115200);   //初始化串口2
	
//	BSP_CAN_Init();
CAN1_Init();
}
