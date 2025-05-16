#include "bsp.h"

#include "FreeRTOS.h"
#include "task.h"
#include "Led_Task.h"
#include "Remoter_Task.h"
#include "tx2_task.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4	 
	
	  /* 1����ʼ�� */
  BSP_Init();       
	
		/* 2���������� */
	Led_Tast_Creat();
	RemoteControl_Task_Creat();
	TX2_Tast_Creat();
	
	/* 3��������� */
	vTaskStartScheduler();	

}
