#ifndef _REMOTER_TASK_H
#define _REMOTER_TASK_H

/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"

#include "bsp.h"
#include "bsp_usart.h"  
#include "ZLAC8015D_motor_Task.h"

/* �������� ------------------------------------------------------------------*/
#define SBUS_FRAME_LEN 25
#define SBUS_UART USART1  // ʹ�ô���1

// SBUSͨ������
#define SBUS_CH_NUM 16

// SBUS���ݽṹ��
typedef struct
{
    uint16_t channels[SBUS_CH_NUM];  // 16·ͨ��ֵ����λ��0-2047
    uint8_t  failsafe;               // Failsafe ��־λ
} SBUS_Data_t;

// �ⲿ����
extern SBUS_Data_t sbus_data;

// ��������
void SBUS_Process(uint8_t byte);
void Remoter_Task_Init(void);
void RemoteControl_Task(void *arg);
void motor_set_both_speed(uint8_t ID, int16_t left_rpm, int16_t right_rpm);
void RemoteControl_Task_Creat(void);

#endif /* _REMOTER_TASK_H */
