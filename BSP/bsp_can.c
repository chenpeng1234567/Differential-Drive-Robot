#include "bsp_can.h"
#include "bsp_usart.h"	  
//// 定义设备ID
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


//// CAN初始化
void CAN1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    CAN_InitTypeDef CAN_InitStructure;
    CAN_FilterInitTypeDef CAN_FilterInitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
	
    // 1. 使能时钟
    RCC_APB2PeriphClockCmd(CANx_GPIO_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(CANx_CLK, ENABLE);

    // 2. 配置CAN引脚 (PA11: CAN_RX, PA12: CAN_TX)
    GPIO_InitStructure.GPIO_Pin = CANx_RX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // 上拉输入
    GPIO_Init(CANx_GPIO_PORT, &GPIO_InitStructure);
      
    GPIO_InitStructure.GPIO_Pin = CANx_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(CANx_GPIO_PORT, &GPIO_InitStructure);

    // 3. 配置CAN工作模式
    CAN_InitStructure.CAN_TTCM = DISABLE; // 禁止时间触发通信模式
    CAN_InitStructure.CAN_ABOM = DISABLE;  // 自动离线管理
    CAN_InitStructure.CAN_AWUM = DISABLE;  // 自动唤醒模式
    CAN_InitStructure.CAN_NART = DISABLE; // 禁止自动重传
    CAN_InitStructure.CAN_RFLM = DISABLE; // 禁止锁定接收FIFO
    CAN_InitStructure.CAN_TXFP = DISABLE; // 禁止发送FIFO优先级
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; // 正常模式

    // 4. 配置波特率 (500 kbps)
    // 假设APB1时钟为36 MHz
    // 波特率 = APB1时钟 / (Prescaler * (BS1 + BS2 + 1))
    // 这里设置为 36 MHz / (12 * (3 + 2 + 1)) = 500 kbps
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;   // 同步跳转宽度为1个时间单位
    CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;   // 时间段1为3个时间单位
    CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;   // 时间段2为2个时间单位
    CAN_InitStructure.CAN_Prescaler = 12;       // 分频系数

    // 初始化CAN
    CAN_Init(CANx, &CAN_InitStructure);

    // 5. 配置CAN过滤器
    CAN_FilterInitStructure.CAN_FilterNumber = 0; // 使用过滤器0
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask; // 掩码模式
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit; // 32位模式
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000; // 过滤器ID高16位
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;  // 过滤器ID低16位
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000; // 掩码高16位
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;  // 掩码低16位
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0; // 使用FIFO0
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE; // 启用过滤器
    CAN_FilterInit(&CAN_FilterInitStructure);

    // 6. 启用CAN接收中断
    CAN_ITConfig(CANx, CAN_IT_FMP0, ENABLE); // 启用FIFO0消息挂起中断

    // 7. 配置NVIC
    NVIC_InitStructure.NVIC_IRQChannel = CANx_RX_IRQn; // CAN1接收中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = CANx_RX_Priority;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

//中断服务函数			    
//void CANx_RX_IRQHandler(void)
//{
//  	CanRxMsg RxMessage;
//    CAN_Receive(CANx, 0, &RxMessage);
//      // 处理接收到的消息
//			switch (RxMessage.StdId)
//			{
//					case DEVICE_ID_1:
//							// 处理设备1的响应
//							break;
//					case DEVICE_ID_2:
//							// 处理设备2的响应
//							break;
//					case DEVICE_ID_3:
//							// 处理设备3的响应
//							break;
//					default:
//							// 未知ID
//							break;
//			}
//		// 清除中断标志
//    CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
//}

void CANx_RX_IRQHandler(void)//读取电机速度
{
    CanRxMsg RxMessage;
    CAN_Receive(CANx, 0, &RxMessage);

    if ((RxMessage.StdId >= 0x580) && (RxMessage.StdId <= 0x5FF))
    {
        //uint8_t node_id = RxMessage.StdId - 0x580;
        uint8_t command = RxMessage.Data[0];
        uint16_t index = RxMessage.Data[1] | (RxMessage.Data[2] << 8);

        if (command == 0x43 && index == 0x606C)  // 速度反馈
        {
						motor_left_vel = (int16_t)((RxMessage.Data[5]) | (RxMessage.Data[4] << 8));
						motor_right_vel = (int16_t)((RxMessage.Data[7]) | (RxMessage.Data[6] << 8));
        }
    }
    CAN_ClearITPendingBit(CANx, CAN_IT_FMP0);
}
 
//can发送一组数据(固定格式:ID为0X12,标准帧,数据帧)	
//len:数据长度(最大为8)				     
//msg:数据指针,最大为8个字节.
//返回值:0,成功;
//		 其他,失败;
u8 Can_Send_Msg_TEXT(uint32_t id,u8 length,u8* msg)
{	
	u8 mbox;
	u16 i=0;
	CanTxMsg TxMessage;
	TxMessage.StdId=id;			// 标准标识符 
	TxMessage.ExtId=0;			// 设置扩展标示符 
	TxMessage.IDE=CAN_Id_Standard; 	// 标准帧
	TxMessage.RTR=CAN_RTR_Data;		// 数据帧
	TxMessage.DLC=length;				// 要发送的数据长度
	for(i=0;i<length;i++)
	TxMessage.Data[i]=msg[i];			          
	mbox= CAN_Transmit(CANx, &TxMessage);   
	i=0; 
	while((CAN_TransmitStatus(CANx, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//等待发送结束
	if(i>=0XFFF)return 1;
	return 0;	
}

//can口接收数据查询
//buf:数据缓存区;	 
//返回值:0,无数据被收到;
//		 其他,接收的数据长度;
u8 Can_Receive_Msg(u8 *buf)
{		   		   
 	u32 i;
	CanRxMsg RxMessage;
    if( CAN_MessagePending(CANx,CAN_FIFO0)==0)return 0;		//没有接收到数据,直接退出 
    CAN_Receive(CANx, CAN_FIFO0, &RxMessage);//读取数据	
    for(i=0;i<8;i++)
    buf[i]=RxMessage.Data[i];  
	return RxMessage.DLC;	
}
