/**
  ****************************(C) COPYRIGHT 2025 CRP****************************
  * @file       Chassis_Task.c/h
  * @brief      �����������
  * @note
  * @history
  *  Version        Date            Author          Modification
  *  V1.0.0      2025-04-27          crp            First version
  ****************************(C) COPYRIGHT 2025 CRP****************************
*/
#include "ZLAC8015D_motor_Task.h"
#include "bsp_can.h"

uint8_t TPDO_Config_Status = 0;

//��ʼ������
void ZLAC8015D_Test(void)
{
		Velocity_Set_Init(0x01);//�ٶ�ģʽ+ʹ��
//		while(1)
//		{
//			Profile_Velocity_Test(0x01);
//		}

}

//�������������EEPROM
uint8_t Save_EEPROM(uint8_t ID)
{
	uint8_t Data[8] = {0x2B, 0x10, 0x20, 0x00, 0x01, 0x00, 0x00, 0x00};
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);
}

//�ָ���������
uint8_t Reset_Driver(uint8_t ID)
{
	uint8_t Data[8] = {0x2B, 0x09, 0x20, 0x00, 0x01, 0x00, 0x00, 0x00};
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);
}

//ͣ��
uint8_t Halt(uint8_t ID)
{
	uint8_t Data[8] = {0x2B, 0x40, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00};
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);
}

//�������
uint8_t Troubleshoot(uint8_t ID)
{
	uint8_t Data[8] = {0x2B, 0x40, 0x60, 0x00, 0x80, 0x00, 0x00, 0x00};
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);
}

//��ȡ����������,��can�ж������
uint8_t Request_Left_Encoder_Position(uint8_t ID)
{
	uint8_t Data[8] = {0x40, 0x64, 0x60, 0x01, 0x00, 0x00, 0x00, 0x00}; 
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);		
}

//��ȡ�ҵ��������,��can�ж������
uint8_t Request_Right_Encoder_Position(uint8_t ID)
{
	uint8_t Data[8] = {0x40, 0x64, 0x60, 0x02, 0x00, 0x00, 0x00, 0x00};  
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);		
}

//��ȡ���ҵ���ٶ�,��can�ж������
uint8_t Request_Velocity(uint8_t ID)
{
	uint8_t Data[8] = {0x40, 0x6C, 0x60, 0x03, 0x00, 0x00, 0x00, 0x00};  
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);		
}

//��ȡ���ҵ������
uint8_t Request_Current(uint8_t ID)
{
	uint8_t Data[8] = {0x40, 0x77, 0x60, 0x03, 0x00, 0x00, 0x00, 0x00};
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);		
}

//��ȡ������
uint8_t Request_Trouble_code(uint8_t ID)
{
	uint8_t Data[8] = {0x40, 0x3F, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00};
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);
}

//��ȡ����汾��
uint8_t Request_Software_Version(uint8_t ID)
{
	uint8_t Data[8] = {0x40, 0x31, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00};
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);
}

//��ȡ�����¶�
uint8_t Request_Left_Temperature(uint8_t ID)
{
	uint8_t Data[8] = {0x40, 0x32, 0x20, 0x01, 0x00, 0x00, 0x00, 0x00};
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);
}

//��ȡ�ҵ���¶�
uint8_t Request_Right_Temperature(uint8_t ID)
{
	uint8_t Data[8] = {0x40, 0x32, 0x20, 0x02, 0x00, 0x00, 0x00, 0x00};
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);
}

//���ֹͣ������ʹ��ת̬
uint8_t Stop_Drive(uint8_t ID)
{
	uint8_t Data[8] = {0x2B, 0x40, 0x60, 0x00, 0x02, 0x00, 0x00, 0x00};
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);
}

//���ʹ�ܣ������ͣ״̬��
uint8_t Remove_Stop(uint8_t ID)
{
	uint8_t Data[8] = {0x2B, 0x40, 0x60, 0x00, 0x0F, 0x00, 0x00, 0x00};
	return Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);
}

//����ӳ��ȫ���������⣬��Ϊ�Ҳ��ã�������Ҳû������
//RPDO�¼�����
//RPDO0ӳ��0x6040�������֣�
//RPDO0-COB-ID:0x200 + ID
uint8_t RPDO0_Config(uint8_t ID)
{
	uint8_t Data[8] = {0x2F, 0x00, 0x14, 0x02, 0xFE, 0x00, 0x00, 0x00};//RPDO0�¼�����
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
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//RPDO0ӳ��0x6040
	delay_ms(5);

	Data[0] = 0x2F;
	Data[1] = 0x00;
	Data[2] = 0x16;
	Data[3] = 0x00;
	Data[4] = 0x01;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//RPDO0����1��ӳ��
	delay_ms(5);

	return 0x00;
}

//RPDO1�¼�����
//RPDO1ӳ��0x60FF 03��Ŀ���ٶȣ�
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
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//RPDO1�¼�����
	delay_ms(5);

	Data[0] = 0x23;
	Data[1] = 0x01;
	Data[2] = 0x16;
	Data[3] = 0x01;
	Data[4] = 0x20;
	Data[5] = 0x03;
	Data[6] = 0xFF;
	Data[7] = 0x60;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//RPDO1ӳ��0x60FF 03
	delay_ms(5);
	
	Data[0] = 0x2F;
	Data[1] = 0x01;
	Data[2] = 0x16;
	Data[3] = 0x00;
	Data[4] = 0x01;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//RPDO1����1��ӳ��
	delay_ms(5);

	return 0x00;
}

//RPDO2�¼�����
//RPDO2ӳ��0x607A 01������Ŀ��λ�ã�
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
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//RPDO2�¼�����
	delay_ms(5);

	Data[0] = 0x23;
	Data[1] = 0x02;
	Data[2] = 0x16;
	Data[3] = 0x01;
	Data[4] = 0x20;
	Data[5] = 0x01;
	Data[6] = 0x7A;
	Data[7] = 0x60;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//RPDO2ӳ��0x607A 01
	delay_ms(5);
	
	Data[0] = 0x2F;
	Data[1] = 0x02;
	Data[2] = 0x16;
	Data[3] = 0x00;
	Data[4] = 0x01;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//RPDO2����1��ӳ��
	delay_ms(5);

	return 0x00;
}

//RPDO3�¼�����
//RPDO3ӳ��0x607A 02���ҵ��Ŀ��λ�ã�
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
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//RPDO3�¼�����
	delay_ms(5);

	Data[0] = 0x23;
	Data[1] = 0x03;
	Data[2] = 0x16;
	Data[3] = 0x01;
	Data[4] = 0x20;
	Data[5] = 0x02;
	Data[6] = 0x7A;
	Data[7] = 0x60;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//RPDO3ӳ��0x607A 02
	delay_ms(5);
	
	Data[0] = 0x2F;
	Data[1] = 0x03;
	Data[2] = 0x16;
	Data[3] = 0x00;
	Data[4] = 0x01;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//RPDO3����1��ӳ��
	delay_ms(5);

	return 0x00;
}

//TPDO��ʱ������
//TPDO0��ʱ��100ms
//TPDO0ӳ��0x606C 03�������ٶȣ�
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
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO0�¼�����
	delay_ms(5);
	
	Data[0] = 0x2B;
	Data[1] = 0x00;
	Data[2] = 0x18;
	Data[3] = 0x05;
	Data[4] = 0xC8;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO0��ʱ��200*0.5ms
	delay_ms(5);


	Data[0] = 0x23;
	Data[1] = 0x00;
	Data[2] = 0x1A;
	Data[3] = 0x01;
	Data[4] = 0x20;
	Data[5] = 0x03;
	Data[6] = 0x6C;
	Data[7] = 0x60;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO0ӳ��0x606C 03
	delay_ms(5);

	Data[0] = 0x2F;
	Data[1] = 0x00;
	Data[2] = 0x1A;
	Data[3] = 0x00;
	Data[4] = 0x01;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO0����1��ӳ��
	delay_ms(5);

	return 0x00;
}

//TPDO1��ʱ������
//TPDO1��ʱ��100ms
//TPDO1ӳ��0x6077 03(��������)
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
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO1��ʱ������
	delay_ms(5);
	
	Data[0] = 0x2B;
	Data[1] = 0x01;
	Data[2] = 0x18;
	Data[3] = 0x05;
	Data[4] = 0xC8;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDOA��ʱ��200*0.5ms
	delay_ms(5);

	Data[0] = 0x23;
	Data[1] = 0x01;
	Data[2] = 0x1A;
	Data[3] = 0x01;
	Data[4] = 0x20;
	Data[5] = 0x03;
	Data[6] = 0x77;
	Data[7] = 0x60;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO1ӳ��0x6077 03
	delay_ms(5);
	
	Data[0] = 0x2F;
	Data[1] = 0x01;
	Data[2] = 0x1A;
	Data[3] = 0x00;
	Data[4] = 0x01;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO1����1��ӳ��
	delay_ms(5);

	return 0x00;
}

//TPDO2��ʱ������
//TPDO2��ʱ��ʱ��100ms
//TPDO2ӳ��0x6064 01����������λ�ã�
//TPDO2ӳ��0x6064 02���ҵ������λ�ã�
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
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO2�¼�����
	delay_ms(5);
	
	Data[0] = 0x2B;
	Data[1] = 0x02;
	Data[2] = 0x18;
	Data[3] = 0x05;
	Data[4] = 0xC8;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO2��ʱ��200*0.5ms
	delay_ms(5);


	Data[0] = 0x23;
	Data[1] = 0x02;
	Data[2] = 0x1A;
	Data[3] = 0x01;
	Data[4] = 0x20;
	Data[5] = 0x01;
	Data[6] = 0x64;
	Data[7] = 0x60;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO2ӳ��0x6064 01
	delay_ms(5);
	
	Data[0] = 0x23;
	Data[1] = 0x02;
	Data[2] = 0x1A;
	Data[3] = 0x02;
	Data[4] = 0x20;
	Data[5] = 0x02;
	Data[6] = 0x64;
	Data[7] = 0x60;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO2ӳ��0x6064 02
	delay_ms(5);

	
	Data[0] = 0x2F;
	Data[1] = 0x02;
	Data[2] = 0x1A;
	Data[3] = 0x00;
	Data[4] = 0x02;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO2����2��ӳ��
	delay_ms(5);

	return 0x00;
}

//TPDO3�¼�����
//TPDO3ӳ��0x603F 00�������룩
//TPDO0��ֹʱ��500ms
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
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO3�¼�����
	delay_ms(5);

	Data[0] = 0x2B;
	Data[1] = 0x03;
	Data[2] = 0x18;
	Data[3] = 0x03;
	Data[4] = 0xE8;
	Data[5] = 0x03;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO3��ֹʱ��1000*0.5ms
	delay_ms(5);

	
	Data[0] = 0x23;
	Data[1] = 0x03;
	Data[2] = 0x1A;
	Data[3] = 0x01;
	Data[4] = 0x20;
	Data[5] = 0x00;
	Data[6] = 0x3F;
	Data[7] = 0x60;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO3ӳ��0x603F 00
	delay_ms(5);
	
	Data[0] = 0x2F;
	Data[1] = 0x03;
	Data[2] = 0x1A;
	Data[3] = 0x00;
	Data[4] = 0x01;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//TPDO3����1��ӳ��
	delay_ms(5);

	return 0x00;
}

//NMT����
//д��0x01 0x01������1������PDO����
uint8_t NMT_Control(uint8_t Data0, uint8_t ID)
{
	  uint8_t Data[2];
    Data[0] = Data0;
    Data[1] = ID;
	
	return Can_Send_Msg_TEXT(0x000, 0x02, Data);
}

//ʹ�ܵ��
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

//�ٶ�ģʽ����
void Profile_Velocity_Test(uint8_t ID)
{
	uint8_t Data_4Byte[4];
	
	Data_4Byte[0] = 0x64;
	Data_4Byte[1] = 0x00;
	Data_4Byte[2] = 0x64;
	Data_4Byte[3] = 0x00;
	Can_Send_Msg_TEXT(0x300 + ID, 0x04, Data_4Byte);//ͬ��100rpm
	delay_ms(5000);
	
	Data_4Byte[0] = 0x9C;
	Data_4Byte[1] = 0xFF;
	Data_4Byte[2] = 0x9C;
	Data_4Byte[3] = 0xFF;
	Can_Send_Msg_TEXT(0x300 + ID, 0x04, Data_4Byte);//ͬ��-100rpm
	delay_ms(5000);
}

void motor_forward(uint8_t ID)//����ǰ��ģʽrpm50
{
	uint8_t Data[8] = {0x23, 0xFF, 0x60, 0x03, 0x32, 0x00, 0x32, 0x00};
	Can_Send_Msg_TEXT(0x600 + ID, 0x04, Data);
	delay_ms(5);
}

//�ٶ�ģʽ   ͬ��ģʽ
uint8_t Velocity_Set_Init(uint8_t ID)
{
	uint8_t Data[8] = {0x2F, 0x60, 0x60, 0x00, 0x03, 0x00, 0x00, 0x00};//�����ٶ�ģʽ
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
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//ʹ��
	delay_ms(5);
	
	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x07;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//ʹ��
	delay_ms(5);
	
	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x0F;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//ʹ��
	delay_ms(5);

//	Data[0] = 0x23;
//	Data[1] = 0xFF;
//	Data[2] = 0x60;
//	Data[3] = 0x03;
//	Data[4] = 0x64;
//	Data[5] = 0x00;
//	Data[6] = 0x64;
//	Data[7] = 0x00;
//	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//����ͬ��Ŀ���ٶ�100rpm
//	delay_ms(5000);

//	Data[0] = 0x23;
//	Data[1] = 0xFF;
//	Data[2] = 0x60;
//	Data[3] = 0x03;
//	Data[4] = 0x9C;
//	Data[5] = 0xFF;
//	Data[6] = 0x9C;
//	Data[7] = 0xFF;
//	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//����ͬ��Ŀ���ٶ�-100rpm
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
//	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//����ͬ�����ٶ�100rpm���ٶ�50rpm
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
//	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//����ͬ�����ٶ�50rpm���ٶ�-100rpm
//	delay_ms(5000);
	
	return 0x00;
}

//���λ��ģʽ
uint8_t Relative_Position_Set_Init(uint8_t ID)
{
	uint8_t Data[8] = {0x2F, 0x60, 0x60, 0x00, 0x01, 0x00, 0x00, 0x00};//�������λ��ģʽ
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
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//������������ٶ�60r/min
	delay_ms(5);
	
	Data[0] = 0x23;
	Data[1] = 0x81;
	Data[2] = 0x60;
	Data[3] = 0x02;
	Data[4] = 0x3C;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//�����ҵ������ٶ�60r/min
	delay_ms(5);

	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x06;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//ʹ��
	delay_ms(5);
	
	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x07;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//ʹ��
	delay_ms(5);
	
	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x0F;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//ʹ��
	delay_ms(5);

	Data[0] = 0x23;
	Data[1] = 0x7A;
	Data[2] = 0x60;
	Data[3] = 0x01;
	Data[4] = 0x00;
	Data[5] = 0x7D;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//��������Ŀ��λ��32000
	delay_ms(50);

	Data[0] = 0x23;
	Data[1] = 0x7A;
	Data[2] = 0x60;
	Data[3] = 0x02;
	Data[4] = 0x00;
	Data[5] = 0x83;
	Data[6] = 0xFF;
	Data[7] = 0xFF;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//�����ҵ��Ŀ��λ��-32000
	delay_ms(50);
	
	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x4F;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//��������˶�
	delay_ms(50);
	
	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x5F;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//��������˶�
	delay_ms(50);
	
	return 0x00;
}

//����λ��ģʽ
uint8_t Absolute_position_Set_Init(uint8_t ID)
{
	uint8_t Data[8] = {0x2F, 0x60, 0x60, 0x00, 0x01, 0x00, 0x00, 0x00};//���þ���λ��ģʽ
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
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//������������ٶ�60r/min
	delay_ms(5);
	
	Data[0] = 0x23;
	Data[1] = 0x81;
	Data[2] = 0x60;
	Data[3] = 0x02;
	Data[4] = 0x3C;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//�����ҵ������ٶ�60r/min
	delay_ms(5);

	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x06;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//ʹ��
	delay_ms(5);
	
	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x07;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//ʹ��
	delay_ms(5);
	
	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x0F;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//ʹ��
	delay_ms(5);

	Data[0] = 0x23;
	Data[1] = 0x7A;
	Data[2] = 0x60;
	Data[3] = 0x01;
	Data[4] = 0x00;
	Data[5] = 0x7D;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//��������Ŀ��λ��32000
	delay_ms(50);

	Data[0] = 0x23;
	Data[1] = 0x7A;
	Data[2] = 0x60;
	Data[3] = 0x02;
	Data[4] = 0x00;
	Data[5] = 0x83;
	Data[6] = 0xFF;
	Data[7] = 0xFF;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//�����ҵ��Ŀ��λ��-32000
	delay_ms(50);
	
	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x0F;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//���������˶�
	delay_ms(50);
	
	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x1F;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//���������˶�
	delay_ms(50);
	
	return 0x00;
}

//����ģʽ
uint8_t Moment_Set_Init(uint8_t ID)
{
	uint8_t Data[8] = {0x2F, 0x60, 0x60, 0x00, 0x04, 0x00, 0x00, 0x00};//��������ģʽ
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
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//ʹ��
	delay_ms(5);
	
	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x07;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//ʹ��
	delay_ms(5);
	
	Data[0] = 0x2B;
	Data[1] = 0x40;
	Data[2] = 0x60;
	Data[3] = 0x00;
	Data[4] = 0x0F;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//ʹ��
	delay_ms(5);

	Data[0] = 0x23;
	Data[1] = 0x71;
	Data[2] = 0x60;
	Data[3] = 0x03;
	Data[4] = 0xE8;
	Data[5] = 0x03;
	Data[6] = 0xE8;
	Data[7] = 0x03;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//����ͬ��Ŀ��ת��1000mA/s
	delay_ms(50);

	Data[0] = 0x23;
	Data[1] = 0x71;
	Data[2] = 0x60;
	Data[3] = 0x03;
	Data[4] = 0x18;
	Data[5] = 0xFC;
	Data[6] = 0x18;
	Data[7] = 0xFC;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//����ͬ��Ŀ��ת��-1000mA/s
	delay_ms(50);
	
	Data[0] = 0x23;
	Data[1] = 0x71;
	Data[2] = 0x60;
	Data[3] = 0x03;
	Data[4] = 0xE8;
	Data[5] = 0x03;
	Data[6] = 0x18;
	Data[7] = 0xFC;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//����ͬ����ת��1000mA/s����ת��-1000mA/s
	delay_ms(50);
	
	Data[0] = 0x23;
	Data[1] = 0x71;
	Data[2] = 0x60;
	Data[3] = 0x03;
	Data[4] = 0x18;
	Data[5] = 0xFC;
	Data[6] = 0xE8;
	Data[7] = 0x03;
	Can_Send_Msg_TEXT(0x600 + ID, 0x08, Data);//����ͬ����ת��-1000mA/s����ת��1000mA/s
	delay_ms(50);
	
	return 0x00;
}
