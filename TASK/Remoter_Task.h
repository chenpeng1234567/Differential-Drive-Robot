#ifndef _REMOTER_TASK_H
#define _REMOTER_TASK_H

/* 包含的头文件 --------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"

#include "bsp.h"
#include "bsp_usart.h"  
#include "ZLAC8015D_motor_Task.h"

/* 变量申明 ------------------------------------------------------------------*/
#define SBUS_FRAME_LEN 25
#define SBUS_UART USART1  // 使用串口1

// SBUS通道数量
#define SBUS_CH_NUM 16

// SBUS数据结构体
typedef struct
{
    uint16_t channels[SBUS_CH_NUM];  // 16路通道值，单位：0-2047
    uint8_t  failsafe;               // Failsafe 标志位
} SBUS_Data_t;

// 外部声明
extern SBUS_Data_t sbus_data;

// 函数声明
void SBUS_Process(uint8_t byte);
void Remoter_Task_Init(void);
void RemoteControl_Task(void *arg);
void motor_set_both_speed(uint8_t ID, int16_t left_rpm, int16_t right_rpm);
void RemoteControl_Task_Creat(void);

#endif /* _REMOTER_TASK_H */
