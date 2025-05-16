#include "bsp.h"

#include "FreeRTOS.h"
#include "task.h"
#include "Led_Task.h"
#include "Remoter_Task.h"
#include "tx2_task.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4	 
	
	  /* 1、初始化 */
  BSP_Init();       
	
		/* 2、创建任务 */
	Led_Tast_Creat();
	RemoteControl_Task_Creat();
	TX2_Tast_Creat();
	
	/* 3、任务调度 */
	vTaskStartScheduler();	

}
