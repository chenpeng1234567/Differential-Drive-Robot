#ifndef _ZLAC8015D_MOTOR_TASK_H
#define _ZLAC8015D_MOTOR_TASK_H

/* 包含的头文件 --------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"

#include "bsp.h"

/* 变量申明 ------------------------------------------------------------------*/
extern uint8_t TPDO_Config_Status;
//电机变量
extern int32_t encoder_left_value;//左编码器
extern int32_t encoder_right_value;//右编码器
extern int32_t motor_left_vel;//左轮速度
extern int32_t motor_right_vel;//右轮速度


/* 函数申明 ------------------------------------------------------------------*/
uint8_t Halt(uint8_t ID);//停机
uint8_t Troubleshoot(uint8_t ID);//清除故障
uint8_t Request_Left_Encoder_Position(uint8_t ID);//读取左电机编码器,在can中断里面读
uint8_t Request_Right_Encoder_Position(uint8_t ID);//读取右电机编码器,在can中断里面读
uint8_t Request_Velocity(uint8_t ID);//读取左右电机速度,在can中断里面读
uint8_t Request_Current(uint8_t ID);//读取左右电机电流
uint8_t Request_Trouble_code(uint8_t ID);//读取故障码
uint8_t Request_Software_Version(uint8_t ID);//读取软件版本号
uint8_t Request_Left_Temperature(uint8_t ID);//读取左电机温度
uint8_t Request_Right_Temperature(uint8_t ID);//读取右电机温度

uint8_t Stop_Drive(uint8_t ID);//电机停止并保持使能转态
uint8_t Remove_Stop(uint8_t ID);//电机使能（解除急停状态）

//以下映射全部都有问题，因为我不用，所以我也没做更改
uint8_t RPDO0_Config(uint8_t ID);//RPDO0配置
uint8_t RPDO1_Config(uint8_t ID);//RPDO1配置
uint8_t RPDO2_Config(uint8_t ID);//RPDO2配置
uint8_t RPDO3_Config(uint8_t ID);//RPDO3配置
uint8_t TPDO0_Config(uint8_t ID);//TPDO0配置
uint8_t TPDO1_Config(uint8_t ID);//TPDO1配置
uint8_t TPDO2_Config(uint8_t ID);//TPDO2配置
uint8_t TPDO3_Config(uint8_t ID);//TPDO3配置
uint8_t NMT_Control(uint8_t ID, uint8_t Data0);//NMT控制

uint8_t Driver_Enable(uint8_t ID);//使能切换

void Profile_Velocity_Test(uint8_t ID);//速度模式测试
void ZLAC8015D_Test(void);//ZLAC8015D测试程序
void motor_forward(uint8_t ID);//50rpm前进

uint8_t Velocity_Set_Init(uint8_t ID);//速度模式   同步模式
uint8_t Relative_Position_Set_Init(uint8_t ID);//相对位置模式
uint8_t Absolute_position_Set_Init(uint8_t ID);//绝对位置模式
uint8_t Moment_Set_Init(uint8_t ID);//力矩模式

#endif /* _ZLAC8015D_MOTOR_TASK_H */
