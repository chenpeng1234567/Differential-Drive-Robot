#include "bsp_can.h"
#include "bsp_usart.h"	  
//// �����豸ID
#define DEVICE_ID_1 0x01
#define DEVICE_ID_2 0x02
#define DEVICE_ID_3 0x03

#define CANx                    CAN1
#define CANx_RX_PIN             GPIO_Pin_11
#define CANx_TX_PIN             GPIO_Pin_12
#define CANx_GPIO_PORT          GPIOA                    
#define CANx_RX_IRQn            USB_LP_CAN1_RX0_IRQn
#define CANx_RX_Priority        6                       
#define CANx_RX_IRQHandler      USB_LP_CAN1_RX0_IRQHandler
#define CANx_CLK                RCC_APB1Periph_CAN1
#define CANx_GPIO_CLK           RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO

int32_t motor_left_vel = 0;
int32_t motor_right_vel = 0;


//// CAN��ʼ��
void CAN1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    CAN_InitTypeDef CAN_InitStructure;
    CAN_FilterInitTypeDef CAN_FilterInitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
	
    // 1. ʹ��ʱ��
    RCC_APB2PeriphClockCmd(CANx_GPIO_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(CANx_CLK, ENABLE);

    // 2. ����CAN���� (PA11: CAN_RX, PA12: CAN_TX)
    GPIO_InitStructure.GPIO_Pin = CANx_RX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // ��������
    GPIO_Init(CANx_GPIO_PORT, &GPIO_InitStructure);
      
    GPIO_InitStructure.GPIO_Pin = CANx_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // �����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(CANx_GPIO_PORT, &GPIO_InitStructure);

    // 3. ����CAN����ģʽ
    CAN_InitStructure.CAN_TTCM = DISABLE; // ��ֹʱ�䴥��ͨ��ģʽ
    CAN_InitStructure.CAN_ABOM = DISABLE;  // �Զ����߹���
    CAN_InitStructure.CAN_AWUM = DISABLE;  // �Զ�����ģʽ
    CAN_InitStructure.CAN_NART = DISABLE; // ��ֹ�Զ��ش�
    CAN_InitStructure.CAN_RFLM = DISABLE; // ��ֹ��������FIFO
    CAN_InitStructure.CAN_TXFP = DISABLE; // ��ֹ����FIFO���ȼ�
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; // ����ģʽ

    // 4. ���ò����� (500 kbps)
    // ����APB1ʱ��Ϊ36 MHz
    // ������ = APB1ʱ�� / (Prescaler * (BS1 + BS2 + 1))
    // ��������Ϊ 36 MHz / (12 * (3 + 2 + 1)) = 500 kbps
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;   // ͬ����ת���Ϊ1��ʱ�䵥λ
    CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;   // ʱ���1Ϊ3��ʱ�䵥λ
    CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;   // ʱ���2Ϊ2��ʱ�䵥λ
    CAN_InitStructure.CAN_Prescaler = 12;       // ��Ƶϵ��

    // ��ʼ��CAN
    CAN_Init(CANx, &CAN_InitStructure);

    // 5. ����CAN������
    CAN_FilterInitStructure.CAN_FilterNumber = 0; // ʹ�ù�����0
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask; // ����ģʽ
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit; // 32λģʽ
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000; // ������ID��16λ
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;  // ������ID��16λ
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000; // �����16λ
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;  // �����16λ
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0; // ʹ��FIFO0
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE; // ���ù�����
    CAN_FilterInit(&CAN_FilterInitStructure);

    // 6. ����CAN�����ж�
    CAN_ITConfig(CANx, CAN_IT_FMP0, ENABLE); // ����FIFO0��Ϣ�����ж�

    // 7. ����NVIC
    NVIC_InitStructure.NVIC_IRQChannel = CANx_RX_IRQn; // CAN1�����ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = CANx_RX_Priority;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

//�жϷ�����			    
//void CANx_RX_IRQHandler(void)
//{
//  	CanRxMsg RxMessage;
//    CAN_Receive(CANx, 0, &RxMessage);
//      // ������յ�����Ϣ
//			switch (RxMessage.StdId)
//			{
//					case DEVICE_ID_1:
//							// �����豸1����Ӧ
//							break;
//					case DEVICE_ID_2:
//							// �����豸2����Ӧ
//							break;
//					case DEVICE_ID_3:
//							// �����豸3����Ӧ
//							break;
//					default:
//							// δ֪ID
//							break;
//			}
//		// ����жϱ�־
//    CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
//}

void CANx_RX_IRQHandler(void)//��ȡ����ٶ�
{
    CanRxMsg RxMessage;
    CAN_Receive(CANx, 0, &RxMessage);

    if ((RxMessage.StdId >= 0x580) && (RxMessage.StdId <= 0x5FF))
    {
        //uint8_t node_id = RxMessage.StdId - 0x580;
        uint8_t command = RxMessage.Data[0];
        uint16_t index = RxMessage.Data[1] | (RxMessage.Data[2] << 8);

        if (command == 0x43 && index == 0x606C)  // �ٶȷ���
        {
						motor_left_vel = (int16_t)((RxMessage.Data[5]) | (RxMessage.Data[4] << 8));
						motor_right_vel = (int16_t)((RxMessage.Data[7]) | (RxMessage.Data[6] << 8));
        }
    }
    CAN_ClearITPendingBit(CANx, CAN_IT_FMP0);
}
 
//can����һ������(�̶���ʽ:IDΪ0X12,��׼֡,����֡)	
//len:���ݳ���(���Ϊ8)				     
//msg:����ָ��,���Ϊ8���ֽ�.
//����ֵ:0,�ɹ�;
//		 ����,ʧ��;
u8 Can_Send_Msg_TEXT(uint32_t id,u8 length,u8* msg)
{	
	u8 mbox;
	u16 i=0;
	CanTxMsg TxMessage;
	TxMessage.StdId=id;			// ��׼��ʶ�� 
	TxMessage.ExtId=0;			// ������չ��ʾ�� 
	TxMessage.IDE=CAN_Id_Standard; 	// ��׼֡
	TxMessage.RTR=CAN_RTR_Data;		// ����֡
	TxMessage.DLC=length;				// Ҫ���͵����ݳ���
	for(i=0;i<length;i++)
	TxMessage.Data[i]=msg[i];			          
	mbox= CAN_Transmit(CANx, &TxMessage);   
	i=0; 
	while((CAN_TransmitStatus(CANx, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//�ȴ����ͽ���
	if(i>=0XFFF)return 1;
	return 0;	
}

//can�ڽ������ݲ�ѯ
//buf:���ݻ�����;	 
//����ֵ:0,�����ݱ��յ�;
//		 ����,���յ����ݳ���;
u8 Can_Receive_Msg(u8 *buf)
{		   		   
 	u32 i;
	CanRxMsg RxMessage;
    if( CAN_MessagePending(CANx,CAN_FIFO0)==0)return 0;		//û�н��յ�����,ֱ���˳� 
    CAN_Receive(CANx, CAN_FIFO0, &RxMessage);//��ȡ����	
    for(i=0;i<8;i++)
    buf[i]=RxMessage.Data[i];  
	return RxMessage.DLC;	
}
