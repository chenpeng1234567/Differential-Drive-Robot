#ifndef _ZLAC8015D_MOTOR_TASK_H
#define _ZLAC8015D_MOTOR_TASK_H

/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"

#include "bsp.h"

/* �������� ------------------------------------------------------------------*/
extern uint8_t TPDO_Config_Status;
//�������
extern int32_t encoder_left_value;//�������
extern int32_t encoder_right_value;//�ұ�����
extern int32_t motor_left_vel;//�����ٶ�
extern int32_t motor_right_vel;//�����ٶ�


/* �������� ------------------------------------------------------------------*/
uint8_t Halt(uint8_t ID);//ͣ��
uint8_t Troubleshoot(uint8_t ID);//�������
uint8_t Request_Left_Encoder_Position(uint8_t ID);//��ȡ����������,��can�ж������
uint8_t Request_Right_Encoder_Position(uint8_t ID);//��ȡ�ҵ��������,��can�ж������
uint8_t Request_Velocity(uint8_t ID);//��ȡ���ҵ���ٶ�,��can�ж������
uint8_t Request_Current(uint8_t ID);//��ȡ���ҵ������
uint8_t Request_Trouble_code(uint8_t ID);//��ȡ������
uint8_t Request_Software_Version(uint8_t ID);//��ȡ����汾��
uint8_t Request_Left_Temperature(uint8_t ID);//��ȡ�����¶�
uint8_t Request_Right_Temperature(uint8_t ID);//��ȡ�ҵ���¶�

uint8_t Stop_Drive(uint8_t ID);//���ֹͣ������ʹ��ת̬
uint8_t Remove_Stop(uint8_t ID);//���ʹ�ܣ������ͣ״̬��

//����ӳ��ȫ���������⣬��Ϊ�Ҳ��ã�������Ҳû������
uint8_t RPDO0_Config(uint8_t ID);//RPDO0����
uint8_t RPDO1_Config(uint8_t ID);//RPDO1����
uint8_t RPDO2_Config(uint8_t ID);//RPDO2����
uint8_t RPDO3_Config(uint8_t ID);//RPDO3����
uint8_t TPDO0_Config(uint8_t ID);//TPDO0����
uint8_t TPDO1_Config(uint8_t ID);//TPDO1����
uint8_t TPDO2_Config(uint8_t ID);//TPDO2����
uint8_t TPDO3_Config(uint8_t ID);//TPDO3����
uint8_t NMT_Control(uint8_t ID, uint8_t Data0);//NMT����

uint8_t Driver_Enable(uint8_t ID);//ʹ���л�

void Profile_Velocity_Test(uint8_t ID);//�ٶ�ģʽ����
void ZLAC8015D_Test(void);//ZLAC8015D���Գ���
void motor_forward(uint8_t ID);//50rpmǰ��

uint8_t Velocity_Set_Init(uint8_t ID);//�ٶ�ģʽ   ͬ��ģʽ
uint8_t Relative_Position_Set_Init(uint8_t ID);//���λ��ģʽ
uint8_t Absolute_position_Set_Init(uint8_t ID);//����λ��ģʽ
uint8_t Moment_Set_Init(uint8_t ID);//����ģʽ

#endif /* _ZLAC8015D_MOTOR_TASK_H */
