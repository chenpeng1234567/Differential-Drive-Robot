/**
  ****************************(C) COPYRIGHT 2025 CRP****************************
  * @file       Chassis_Task.c/h
  * @brief      电机驱动任务
  * @note
  * @history
  *  Version        Date            Author          Modification
  *  V1.0.0      2025-04-27          crp            First version
  ****************************(C) COPYRIGHT 2025 CRP****************************
*/
#include "ZLAC8015D_motor_Task.h"
#include "bsp_can.h"

uint8_t TPDO_Config_Status = 0;

//初始化控制
void ZLAC8015D_Test(void)
{
		Velocity_Set_Init(0x01);//速度模式+使能
//		while(1)
//		{
//			Profile_Velocity_Test(0x01);
//		}

}

//保存参数配置至EEPROM
uint8_t Save_EEPROM(uint8_t ID)
{
	uint8_t Data[8] = {0x2B, 0x10, 0x20, 0x00, 0x01, 0x00, 0x00, 0x00};
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);
}

//恢复出厂配置
uint8_t Reset_Driver(uint8_t ID)
{
	uint8_t Data[8] = {0x2B, 0x09, 0x20, 0x00, 0x01, 0x00, 0x00, 0x00};
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);
}

//停机
uint8_t Halt(uint8_t ID)
{
	uint8_t Data[8] = {0x2B, 0x40, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00};
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);
}

//清除故障
uint8_t Troubleshoot(uint8_t ID)
{
	uint8_t Data[8] = {0x2B, 0x40, 0x60, 0x00, 0x80, 0x00, 0x00, 0x00};
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);
}

//读取左电机编码器,在can中断里面读
uint8_t Request_Left_Encoder_Position(uint8_t ID)
{
	uint8_t Data[8] = {0x40, 0x64, 0x60, 0x01, 0x00, 0x00, 0x00, 0x00}; 
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);		
}

//读取右电机编码器,在can中断里面读
uint8_t Request_Right_Encoder_Position(uint8_t ID)
{
	uint8_t Data[8] = {0x40, 0x64, 0x60, 0x02, 0x00, 0x00, 0x00, 0x00};  
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);		
}

//读取左右电机速度,在can中断里面读
uint8_t Request_Velocity(uint8_t ID)
{
	uint8_t Data[8] = {0x40, 0x6C, 0x60, 0x03, 0x00, 0x00, 0x00, 0x00};  
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);		
}

//读取左右电机电流
uint8_t Request_Current(uint8_t ID)
{
	uint8_t Data[8] = {0x40, 0x77, 0x60, 0x03, 0x00, 0x00, 0x00, 0x00};
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);		
}

//读取故障码
uint8_t Request_Trouble_code(uint8_t ID)
{
	uint8_t Data[8] = {0x40, 0x3F, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00};
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);
}

//读取软件版本号
uint8_t Request_Software_Version(uint8_t ID)
{
	uint8_t Data[8] = {0x40, 0x31, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00};
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);
}

//读取左电机温度
uint8_t Request_Left_Temperature(uint8_t ID)
{
	uint8_t Data[8] = {0x40, 0x32, 0x20, 0x01, 0x00, 0x00, 0x00, 0x00};
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);
}

//读取右电机温度
uint8_t Request_Right_Temperature(uint8_t ID)
{
	uint8_t Data[8] = {0x40, 0x32, 0x20, 0x02, 0x00, 0x00, 0x00, 0x00};
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);
}

//电机停止并保持使能转态
uint8_t Stop_Drive(uint8_t ID)
{
	uint8_t Data[8] = {0x2B, 0x40, 0x60, 0x00, 0x02, 0x00, 0x00, 0x00};
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);
}

//电机使能（解除急停状态）
uint8_t Remove_Stop(uint8_t ID)
{
	uint8_t Data[8] = {0x2B, 0x40, 0x60, 0x00, 0x0F, 0x00, 0x00, 0x00};
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);
}

//以下映射全部都有问题，因为我不用，所以我也没做更改
//RPDO事件触发
//RPDO0映射0x6040（控制字）
//RPDO0-COB-ID:0x200 + ID
uint8_t RPDO0_Config(uint8_t ID)
{
	uint8_t Data[8] = {0x2F, 0x00, 0x14, 0x02, 0xFE, 0x00, 0x00, 0x00};//RPDO0事件触发
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);
	delay_ms(5);

	Data[0] = 0x23;
	Data[1] = 0x00;
	Data[2] = 0x16;
	Data[3] = 0x01;
	Data[4] = 0x10;
	Data[5] = 0x00;
	Data[6] = 0x40;
	Data[7] = 0x60;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//RPDO0映射0x6040
	delay_ms(5);

	Data[0] = 0x2F;
	Data[1] = 0x00;
	Data[2] = 0x16;
	Data[3] = 0x00;
	Data[4] = 0x01;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//RPDO0开启1个映射
	delay_ms(5);

	return 0x00;
}

//RPDO1事件触发
//RPDO1映射0x60FF 03（目标速度）
//RPDO1-COB-ID:0x300 + ID
uint8_t RPDO1_Config(uint8_t ID)
{
	uint8_t Data[8];
	
	Data[0] = 0x2F;
	Data[1] = 0x01;
	Data[2] = 0x14;
	Data[3] = 0x02;
	Data[4] = 0xFE;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//RPDO1事件触发
	delay_ms(5);

	Data[0] = 0x23;
	Data[1] = 0x01;
	Data[2] = 0x16;
	Data[3] = 0x01;
	Data[4] = 0x20;
	Data[5] = 0x03;
	Data[6] = 0xFF;
	Data[7] = 0x60;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//RPDO1映射0x60FF 03
	delay_ms(5);
	
	Data[0] = 0x2F;
	Data[1] = 0x01;
	Data[2] = 0x16;
	Data[3] = 0x00;
	Data[4] = 0x01;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//RPDO1开启1个映射
	delay_ms(5);

	return 0x00;
}

//RPDO2事件触发
//RPDO2映射0x607A 01（左电机目标位置）
//RPDO2-COB-ID:0x400 + ID
uint8_t RPDO2_Config(uint8_t ID)
{
	uint8_t Data[8];
	
	Data[0] = 0x2F;
	Data[1] = 0x02;
	Data[2] = 0x14;
	Data[3] = 0x02;
	Data[4] = 0xFE;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//RPDO2事件触发
	delay_ms(5);

	Data[0] = 0x23;
	Data[1] = 0x02;
	Data[2] = 0x16;
	Data[3] = 0x01;
	Data[4] = 0x20;
	Data[5] = 0x01;
	Data[6] = 0x7A;
	Data[7] = 0x60;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//RPDO2映射0x607A 01
	delay_ms(5);
	
	Data[0] = 0x2F;
	Data[1] = 0x02;
	Data[2] = 0x16;
	Data[3] = 0x00;
	Data[4] = 0x01;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//RPDO2开启1个映射
	delay_ms(5);

	return 0x00;
}

//RPDO3事件触发
//RPDO3映射0x607A 02（右电机目标位置）
//RPDO3-COB-ID:0x500 + ID
uint8_t RPDO3_Config(uint8_t ID)
{
	uint8_t Data[8];
	
	Data[0] = 0x2F;
	Data[1] = 0x03;
	Data[2] = 0x14;
	Data[3] = 0x02;
	Data[4] = 0xFE;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//RPDO3事件触发
	delay_ms(5);

	Data[0] = 0x23;
	Data[1] = 0x03;
	Data[2] = 0x16;
	Data[3] = 0x01;
	Data[4] = 0x20;
	Data[5] = 0x02;
	Data[6] = 0x7A;
	Data[7] = 0x60;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//RPDO3映射0x607A 02
	delay_ms(5);
	
	Data[0] = 0x2F;
	Data[1] = 0x03;
	Data[2] = 0x16;
	Data[3] = 0x00;
	Data[4] = 0x01;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//RPDO3开启1个映射
	delay_ms(5);

	return 0x00;
}

//TPDO定时器触发
//TPDO0定时器100ms
//TPDO0映射0x606C 03（反馈速度）
//TPDO0-COB-ID:0x180 + ID
uint8_t TPDO0_Config(uint8_t ID)
{
	uint8_t Data[8];
	
	Data[0] = 0x2F;
	Data[1] = 0x00;
	Data[2] = 0x18;
	Data[3] = 0x02;
	Data[4] = 0xFF;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO0事件触发
	delay_ms(5);
	
	Data[0] = 0x2B;
	Data[1] = 0x00;
	Data[2] = 0x18;
	Data[3] = 0x05;
	Data[4] = 0xC8;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO0定时器200*0.5ms
	delay_ms(5);


	Data[0] = 0x23;
	Data[1] = 0x00;
	Data[2] = 0x1A;
	Data[3] = 0x01;
	Data[4] = 0x20;
	Data[5] = 0x03;
	Data[6] = 0x6C;
	Data[7] = 0x60;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO0映射0x606C 03
	delay_ms(5);

	Data[0] = 0x2F;
	Data[1] = 0x00;
	Data[2] = 0x1A;
	Data[3] = 0x00;
	Data[4] = 0x01;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO0开启1个映射
	delay_ms(5);

	return 0x00;
}

//TPDO1定时器触发
//TPDO1定时器100ms
//TPDO1映射0x6077 03(反馈电流)
//TPDO1-COB-ID:0x280 + ID
uint8_t TPDO1_Config(uint8_t ID)
{
	uint8_t Data[8];
	
	Data[0] = 0x2F;
	Data[1] = 0x01;
	Data[2] = 0x18;
	Data[3] = 0x02;
	Data[4] = 0xFF;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO1定时器触发
	delay_ms(5);
	
	Data[0] = 0x2B;
	Data[1] = 0x01;
	Data[2] = 0x18;
	Data[3] = 0x05;
	Data[4] = 0xC8;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDOA定时器200*0.5ms
	delay_ms(5);

	Data[0] = 0x23;
	Data[1] = 0x01;
	Data[2] = 0x1A;
	Data[3] = 0x01;
	Data[4] = 0x20;
	Data[5] = 0x03;
	Data[6] = 0x77;
	Data[7] = 0x60;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO1映射0x6077 03
	delay_ms(5);
	
	Data[0] = 0x2F;
	Data[1] = 0x01;
	Data[2] = 0x1A;
	Data[3] = 0x00;
	Data[4] = 0x01;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO1开启1个映射
	delay_ms(5);

	return 0x00;
}

//TPDO2定时器触发
//TPDO2定时器时间100ms
//TPDO2映射0x6064 01（左电机反馈位置）
//TPDO2映射0x6064 02（右电机反馈位置）
//TPDO2-COB-ID:0x380 + ID
uint8_t TPDO2_Config(uint8_t ID)
{
	uint8_t Data[8];
	
	Data[0] = 0x2F;
	Data[1] = 0x02;
	Data[2] = 0x18;
	Data[3] = 0x02;
	Data[4] = 0xFF;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO2事件触发
	delay_ms(5);
	
	Data[0] = 0x2B;
	Data[1] = 0x02;
	Data[2] = 0x18;
	Data[3] = 0x05;
	Data[4] = 0xC8;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO2定时器200*0.5ms
	delay_ms(5);


	Data[0] = 0x23;
	Data[1] = 0x02;
	Data[2] = 0x1A;
	Data[3] = 0x01;
	Data[4] = 0x20;
	Data[5] = 0x01;
	Data[6] = 0x64;
	Data[7] = 0x60;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO2映射0x6064 01
	delay_ms(5);
	
	Data[0] = 0x23;
	Data[1] = 0x02;
	Data[2] = 0x1A;
	Data[3] = 0x02;
	Data[4] = 0x20;
	Data[5] = 0x02;
	Data[6] = 0x64;
	Data[7] = 0x60;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO2映射0x6064 02
	delay_ms(5);

	
	Data[0] = 0x2F;
	Data[1] = 0x02;
	Data[2] = 0x1A;
	Data[3] = 0x00;
	Data[4] = 0x02;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO2开启2个映射
	delay_ms(5);

	return 0x00;
}

//TPDO3事件触发
//TPDO3映射0x603F 00（故障码）
//TPDO0禁止时间500ms
//TPDO3-COB-ID:0x480 + ID
uint8_t TPDO3_Config(uint8_t ID)
{
	uint8_t Data[8];
	
	Data[0] = 0x2F;
	Data[1] = 0x03;
	Data[2] = 0x18;
	Data[3] = 0x02;
	Data[4] = 0xFE;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO3事件触发
	delay_ms(5);

	Data[0] = 0x2B;
	Data[1] = 0x03;
	Data[2] = 0x18;
	Data[3] = 0x03;
	Data[4] = 0xE8;
	Data[5] = 0x03;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO3禁止时间1000*0.5ms
	delay_ms(5);

	
	Data[0] = 0x23;
	Data[1] = 0x03;
	Data[2] = 0x1A;
	Data[3] = 0x01;
	Data[4] = 0x20;
	Data[5] = 0x00;
	Data[6] = 0x3F;
	Data[7] = 0x60;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO3映射0x603F 00
	delay_ms(5);
	
	Data[0] = 0x2F;
	Data[1] = 0x03;
	Data[2] = 0x1A;
	Data[3] = 0x00;
	Data[4] = 0x01;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO3开启1个映射
	delay_ms(5);

	return 0x00;
}

//NMT发送
//写入0x01 0x01：开启1号驱动PDO传输
uint8_t NMT_Control(uint8_t Data0, uint8_t ID)
{
	  uint8_t Data[2];
    Data[0] = Data0;
    Data[1] = ID;
	
	return Can_Send_Msg_TEXT(0x000, 0x02, Data);
}

//使能电机
uint8_t Driver_Enable(uint8_t ID)
{
	uint8_t Data_2Byte[2];
	
	Data_2Byte[0] = 0x06;
	Data_2Byte[1] = 0x00;
	Can_Send_Msg_TEXT(0x200 + ID, 0x02, Data_2Byte);
	
	Data_2Byte[0] = 0x07;
	Data_2Byte[1] = 0x00;
	Can_Send_Msg_TEXT(0x200 + ID, 0x02, Data_2Byte);
	delay_ms(5);
	
	Data_2Byte[0] = 0x0F;
	Data_2Byte[1] = 0x00;
	return Can_Send_Msg_TEXT(0x200 + ID, 0x02, Data_2Byte);
}

//速度模式测试
void Profile_Velocity_Test(uint8_t ID)
{
	uint8_t Data_4Byte[4];
	
	Data_4Byte[0] = 0x64;
	Data_4Byte[1] = 0x00;
	Data_4Byte[2] = 0x64;
	Data_4Byte[3] = 0x00;
	Can_Send_Msg_TEXT(0x300 + ID, 0x04, Data_4Byte);//同步100rpm
	delay_ms(5000);
	
	Data_4Byte[0] = 0x9C;
	Data_4Byte[1] = 0xFF;
	Data_4Byte[2] = 0x9C;
	Data_4Byte[3] = 0xFF;
	Can_Send_Msg_TEXT(0x300 + ID, 0x04, Data_4Byte);//同步-100rpm
	delay_ms(5000);
}

void motor_forward(uint8_t ID)//设置前进模式rpm50
{
	uint8_t Data[8] = {0x23, 0xFF, 0x60, 0x03, 0x32, 0x00, 0x32, 0x00};
	Can_Send_Msg_TEXT(0x600 + ID, 0x04, Data);
	delay_ms(5);
}

//速度模式   同步模式
uint8_t Velocity_Set_Init(uint8_t ID)
{
	uint8_t Data[8] = {0x2F, 0x60, 0x60, 0x00, 0x03, 0x00, 0x00, 0x00};//设置速度模式
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);
	delay_ms(5);

	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x06;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//使能
	delay_ms(5);
	
	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x07;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//使能
	delay_ms(5);
	
	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x0F;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//使能
	delay_ms(5);

//	Data[0] = 0x23;
//	Data[1] = 0xFF;
//	Data[2] = 0x60;
//	Data[3] = 0x03;
//	Data[4] = 0x64;
//	Data[5] = 0x00;
//	Data[6] = 0x64;
//	Data[7] = 0x00;
//	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//设置同步目标速度100rpm
//	delay_ms(5000);

//	Data[0] = 0x23;
//	Data[1] = 0xFF;
//	Data[2] = 0x60;
//	Data[3] = 0x03;
//	Data[4] = 0x9C;
//	Data[5] = 0xFF;
//	Data[6] = 0x9C;
//	Data[7] = 0xFF;
//	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//设置同步目标速度-100rpm
//	delay_ms(5000);
//	
//	Data[0] = 0x23;
//	Data[1] = 0xFF;
//	Data[2] = 0x60;
//	Data[3] = 0x03;
//	Data[4] = 0x64;
//	Data[5] = 0x00;
//	Data[6] = 0x32;
//	Data[7] = 0x00;
//	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//设置同步左速度100rpm右速度50rpm
//	delay_ms(5000);
//	
//	Data[0] = 0x23;
//	Data[1] = 0xFF;
//	Data[2] = 0x60;
//	Data[3] = 0x03;
//	Data[4] = 0x32;
//	Data[5] = 0x00;
//	Data[6] = 0x9C;
//	Data[7] = 0xFF;
//	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//设置同步左速度50rpm右速度-100rpm
//	delay_ms(5000);
	
	return 0x00;
}

//相对位置模式
uint8_t Relative_Position_Set_Init(uint8_t ID)
{
	uint8_t Data[8] = {0x2F, 0x60, 0x60, 0x00, 0x01, 0x00, 0x00, 0x00};//设置相对位置模式
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);
	delay_ms(5);
	
	Data[0] = 0x23;
	Data[1] = 0x81;
	Data[2] = 0x60;
	Data[3] = 0x01;
	Data[4] = 0x3C;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//设置左电机最大速度60r/min
	delay_ms(5);
	
	Data[0] = 0x23;
	Data[1] = 0x81;
	Data[2] = 0x60;
	Data[3] = 0x02;
	Data[4] = 0x3C;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//设置右电机最大速度60r/min
	delay_ms(5);

	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x06;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//使能
	delay_ms(5);
	
	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x07;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//使能
	delay_ms(5);
	
	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x0F;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//使能
	delay_ms(5);

	Data[0] = 0x23;
	Data[1] = 0x7A;
	Data[2] = 0x60;
	Data[3] = 0x01;
	Data[4] = 0x00;
	Data[5] = 0x7D;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//设置左电机目标位置32000
	delay_ms(50);

	Data[0] = 0x23;
	Data[1] = 0x7A;
	Data[2] = 0x60;
	Data[3] = 0x02;
	Data[4] = 0x00;
	Data[5] = 0x83;
	Data[6] = 0xFF;
	Data[7] = 0xFF;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//设置右电机目标位置-32000
	delay_ms(50);
	
	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x4F;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//启动相对运动
	delay_ms(50);
	
	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x5F;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//启动相对运动
	delay_ms(50);
	
	return 0x00;
}

//绝对位置模式
uint8_t Absolute_position_Set_Init(uint8_t ID)
{
	uint8_t Data[8] = {0x2F, 0x60, 0x60, 0x00, 0x01, 0x00, 0x00, 0x00};//设置绝对位置模式
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);
	delay_ms(5);
	
	Data[0] = 0x23;
	Data[1] = 0x81;
	Data[2] = 0x60;
	Data[3] = 0x01;
	Data[4] = 0x3C;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//设置左电机最大速度60r/min
	delay_ms(5);
	
	Data[0] = 0x23;
	Data[1] = 0x81;
	Data[2] = 0x60;
	Data[3] = 0x02;
	Data[4] = 0x3C;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//设置右电机最大速度60r/min
	delay_ms(5);

	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x06;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//使能
	delay_ms(5);
	
	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x07;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//使能
	delay_ms(5);
	
	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x0F;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//使能
	delay_ms(5);

	Data[0] = 0x23;
	Data[1] = 0x7A;
	Data[2] = 0x60;
	Data[3] = 0x01;
	Data[4] = 0x00;
	Data[5] = 0x7D;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//设置左电机目标位置32000
	delay_ms(50);

	Data[0] = 0x23;
	Data[1] = 0x7A;
	Data[2] = 0x60;
	Data[3] = 0x02;
	Data[4] = 0x00;
	Data[5] = 0x83;
	Data[6] = 0xFF;
	Data[7] = 0xFF;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//设置右电机目标位置-32000
	delay_ms(50);
	
	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x0F;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//启动绝对运动
	delay_ms(50);
	
	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x1F;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//启动绝对运动
	delay_ms(50);
	
	return 0x00;
}

//力矩模式
uint8_t Moment_Set_Init(uint8_t ID)
{
	uint8_t Data[8] = {0x2F, 0x60, 0x60, 0x00, 0x04, 0x00, 0x00, 0x00};//设置力矩模式
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);
	delay_ms(5);
	
	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x06;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//使能
	delay_ms(5);
	
	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x07;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//使能
	delay_ms(5);
	
	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x0F;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//使能
	delay_ms(5);

	Data[0] = 0x23;
	Data[1] = 0x71;
	Data[2] = 0x60;
	Data[3] = 0x03;
	Data[4] = 0xE8;
	Data[5] = 0x03;
	Data[6] = 0xE8;
	Data[7] = 0x03;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//设置同步目标转矩1000mA/s
	delay_ms(50);

	Data[0] = 0x23;
	Data[1] = 0x71;
	Data[2] = 0x60;
	Data[3] = 0x03;
	Data[4] = 0x18;
	Data[5] = 0xFC;
	Data[6] = 0x18;
	Data[7] = 0xFC;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//设置同步目标转矩-1000mA/s
	delay_ms(50);
	
	Data[0] = 0x23;
	Data[1] = 0x71;
	Data[2] = 0x60;
	Data[3] = 0x03;
	Data[4] = 0xE8;
	Data[5] = 0x03;
	Data[6] = 0x18;
	Data[7] = 0xFC;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//设置同步左转矩1000mA/s，右转矩-1000mA/s
	delay_ms(50);
	
	Data[0] = 0x23;
	Data[1] = 0x71;
	Data[2] = 0x60;
	Data[3] = 0x03;
	Data[4] = 0x18;
	Data[5] = 0xFC;
	Data[6] = 0xE8;
	Data[7] = 0x03;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//设置同步左转矩-1000mA/s，右转矩1000mA/s
	delay_ms(50);
	
	return 0x00;
}
