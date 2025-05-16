#include "Led_Task.h"

uint8_t CAN_TEXT[8] = {1,2,3,4,5,6,7,8};
/************************************************
函数名称 ： Led_Task
功    能 ： Led的任务函数
参    数 ： 无
返 回 值 ： 无
作    者 ： MLY
*************************************************/
void Led_Task(void *arg)
{

    while (1)
    {
			 //Can_Send_Msg_TEXT(0x12,8,&CAN_TEXT[0]);
			
       vTaskDelay(1000);
    }
}


/************************************************ 
函数名称 ： Led_Tast_Creat
功    能 ： 创建任务
参    数 ： 无
返 回 值 ： 无
作    者 ： MLY
*************************************************/
void Led_Tast_Creat(void)
{
	xTaskCreate(Led_Task, "Led_Task", 256, NULL, 1, NULL);
}
