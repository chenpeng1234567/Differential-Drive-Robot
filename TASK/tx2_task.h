#ifndef _TX2_TASK_H
#define _TX2_TASK_H

/* 包含的头文件 --------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"

#include "bsp.h"

typedef struct {
    float x;
    float y;
    float z;
		float yaw;
} Position;


extern volatile uint8_t uart2_rx_flag;  // 一帧数据接收完成标志
extern volatile uint8_t uart2_rx_buf[UART2_RX_BUF_SIZE];
/* 函数申明 ------------------------------------------------------------------*/
int parse_xyz_struct(const char* input, Position* position);;
void loop(void *arg);
void TX2_Tast_Creat(void);

#endif /* _TX2_TASK_H */
