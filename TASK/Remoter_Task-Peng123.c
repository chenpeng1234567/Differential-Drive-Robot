/**
  ****************************(C) COPYRIGHT 2025 CRP****************************
  * @file       Chassis_Task.c/h
  * @brief      遥控器控制任务
  * @note
  * @history
  *  Version        Date            Author          Modification
  *  V1.0.0      2025-04-27          crp            First version
  ****************************(C) COPYRIGHT 2025 CRP****************************
*/

#include "Remoter_Task.h"

SBUS_Data_t sbus_data;

static uint8_t sbus_rx_buffer[SBUS_FRAME_LEN];
static uint8_t sbus_rx_index = 0;
static uint8_t sbus_frame_started = 0;

void Remoter_Task_Init(void)
{
//    uart_init(100000); // 初始化串口，波特率100k，8E2，SBUS标准
}

/**
 * @brief  处理接收到的每个字节，拼接成一帧
 */
void SBUS_Process(uint8_t byte)
{
    if (!sbus_frame_started)
    {
        if (byte == 0x0F) // SBUS帧头
        {
            sbus_frame_started = 1;
            sbus_rx_index = 0;
            sbus_rx_buffer[sbus_rx_index++] = byte;
        }
    }
    else
    {
        sbus_rx_buffer[sbus_rx_index++] = byte;
        if (sbus_rx_index >= SBUS_FRAME_LEN)
        {
            // 解析数据
            sbus_data.channels[0]  = ((sbus_rx_buffer[1]    | sbus_rx_buffer[2] << 8) & 0x07FF);
            sbus_data.channels[1]  = ((sbus_rx_buffer[2] >> 3 | sbus_rx_buffer[3] << 5) & 0x07FF);
            sbus_data.channels[2]  = ((sbus_rx_buffer[3] >> 6 | sbus_rx_buffer[4] << 2 | sbus_rx_buffer[5] << 10) & 0x07FF);
            sbus_data.channels[3]  = ((sbus_rx_buffer[5] >> 1 | sbus_rx_buffer[6] << 7) & 0x07FF);
            sbus_data.channels[4]  = ((sbus_rx_buffer[6] >> 4 | sbus_rx_buffer[7] << 4) & 0x07FF);
            sbus_data.channels[5]  = ((sbus_rx_buffer[7] >> 7 | sbus_rx_buffer[8] << 1 | sbus_rx_buffer[9] << 9) & 0x07FF);
            sbus_data.channels[6]  = ((sbus_rx_buffer[9] >> 2 | sbus_rx_buffer[10] << 6) & 0x07FF);
            sbus_data.channels[7]  = ((sbus_rx_buffer[10] >> 5 | sbus_rx_buffer[11] << 3) & 0x07FF);

            sbus_data.channels[8]  = ((sbus_rx_buffer[12]    | sbus_rx_buffer[13] << 8) & 0x07FF);
            sbus_data.channels[9]  = ((sbus_rx_buffer[13] >> 3 | sbus_rx_buffer[14] << 5) & 0x07FF);
            sbus_data.channels[10] = ((sbus_rx_buffer[14] >> 6 | sbus_rx_buffer[15] << 2 | sbus_rx_buffer[16] << 10) & 0x07FF);
            sbus_data.channels[11] = ((sbus_rx_buffer[16] >> 1 | sbus_rx_buffer[17] << 7) & 0x07FF);
            sbus_data.channels[12] = ((sbus_rx_buffer[17] >> 4 | sbus_rx_buffer[18] << 4) & 0x07FF);
            sbus_data.channels[13] = ((sbus_rx_buffer[18] >> 7 | sbus_rx_buffer[19] << 1 | sbus_rx_buffer[20] << 9) & 0x07FF);
            sbus_data.channels[14] = ((sbus_rx_buffer[20] >> 2 | sbus_rx_buffer[21] << 6) & 0x07FF);
            sbus_data.channels[15] = ((sbus_rx_buffer[21] >> 5 | sbus_rx_buffer[22] << 3) & 0x07FF);

            // 处理Failsafe
            sbus_data.failsafe = (sbus_rx_buffer[23] >> 3) & 0x01;

            sbus_frame_started = 0;
        }
    }
}

void SWA_ch5(void)
{
	int16_t ch5 = sbus_data.channels[4]; // 对应 CH5
	if (ch5 > 1500) {
			// 开关打开了，比如启动自动模式
	}
	else {
			// 关闭状态，比如回到手动控制
	}
}

void SWB_ch6(void)
{
	// 假设 CH5 是一个开关
	int16_t ch6 = sbus_data.channels[5];

	static uint8_t last_ch6_state = 0;
	uint8_t current_ch6_state = (ch6 > 1500) ? 1 : 0;

	if (current_ch6_state && !last_ch6_state)
	{
			// 按键从“关”切到“开” —— 触发一次
			
	}

	last_ch6_state = current_ch6_state;
}

/**
 * @brief  摇杆控制车辆运动（主循环里调用）
 */
void RemoteControl_Task(void *arg)
{
	ZLAC8015D_Test( );
	while (1)
  {

		if (sbus_data.failsafe)
		{
				// 遥控失联：紧急停车
				motor_set_both_speed(0x01, 0, 0);
				vTaskDelay(pdMS_TO_TICKS(100));  // 等一会儿再重试
				continue; // 跳过这次循环
		}
		else{
			int16_t ch1 = (int16_t)sbus_data.channels[0];  // 通道1: 转向
			int16_t ch3 = (int16_t)sbus_data.channels[2];  // 通道3: 前进后退

			int16_t steering = ch1 - 1500;   // 左负右正
			int16_t throttle = ch3 - 1500;   // 前正后负

			int16_t left_wheel_speed;
			int16_t right_wheel_speed;

			// 死区处理
			if (steering > -30 && steering < 30) steering = 0;
			if (throttle > -30 && throttle < 30) throttle = 0;

			// 限幅
			if (steering > 500) steering = 500;
			if (steering < -500) steering = -500;
			if (throttle > 500) throttle = 500;
			if (throttle < -500) throttle = -500;

			// 计算左右轮速度
			left_wheel_speed  = throttle + steering;
			right_wheel_speed = throttle - steering;

			// 再限幅
			if (left_wheel_speed > 500) left_wheel_speed = 500;
			if (left_wheel_speed < -500) left_wheel_speed = -500;
			if (right_wheel_speed > 500) right_wheel_speed = 500;
			if (right_wheel_speed < -500) right_wheel_speed = -500;

			// 发送到底盘
			motor_set_both_speed(0x01, left_wheel_speed, right_wheel_speed);
			// 加一个小延时，比如 20ms（50Hz刷新率）
			vTaskDelay(pdMS_TO_TICKS(20));
		}
	}
}

/**
 * @brief  同时设置左右轮速度
 */
void motor_set_both_speed(uint8_t ID, int16_t left_rpm, int16_t right_rpm)
{
    uint8_t Data[8] = {0x23, 0xFF, 0x60, 0x03, 0, 0, 0, 0};

    // 小端序填充
    Data[4] = (uint8_t)(left_rpm & 0xFF);
    Data[5] = (uint8_t)((left_rpm >> 8) & 0xFF);
    Data[6] = (uint8_t)(right_rpm & 0xFF);
    Data[7] = (uint8_t)((right_rpm >> 8) & 0xFF);

    // 发送CAN
    Can_Send_Msg_TEXT(0x600 + ID, 8, Data);

    delay_ms(5);
		
}

/************************************************ 
函数名称 ： RemoteControl_Task_Creat
功    能 ： 创建任务
参    数 ： 无
返 回 值 ： 无
作    者 ： CRP
*************************************************/
void RemoteControl_Task_Creat(void)
{
	xTaskCreate(RemoteControl_Task, "RemoteControl_Task", 256, NULL, 1, NULL);
}
