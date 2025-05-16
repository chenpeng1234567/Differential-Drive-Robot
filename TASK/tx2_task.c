#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tx2_task.h"

// 全局结构体变量，debug 时可直接在 Watch 观察
Position position;

/**
 * @brief  从字符串中解析坐标，并写入结构体
 * @param  input     输入字符串，例如："位置坐标：x=1.23, y=4.56, z=7.89"
 * @param  position  坐标结构体指针
 * @retval int       0 成功，-1 失败
 */
int parse_pose_line(const char* input, Position* position)
{
    // 预处理：去掉结尾换行符（\r 或 \n）
    char buffer[100];
    char* newline = NULL;

    strncpy(buffer, input, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';  // 保证结尾为 '\0'

    newline = strpbrk(buffer, "\r\n");
    if (newline) *newline = '\0';

    // 匹配格式解析
		if (sscanf(buffer, "pose: x=%f, y=%f, z=%f, yaw=%f", &position->x, &position->y, &position->z, &position->yaw) == 4)  {
        return 0;  // 解析成功
    } else if (sscanf(buffer, "pose: x=%f, y=%f, z=%f", &position->x, &position->y, &position->z) == 3) {
        position->yaw = 0.0f;  // 默认 yaw 为 0
        return 0;
    }else {
        return -1;  // 失败
    }
}


// 主循环任务
void loop(void *arg)
{
    while (1)
    {
        if (uart2_rx_flag)
        {
            uart2_rx_flag = 0;

            if (parse_pose_line((char*)uart2_rx_buf, &position) == 0)
            {
                printf("坐标解析成功：x=%.3f, y=%.3f, z=%.3f, yaw=%.3f\n",position.x, position.y, position.z, position.yaw);
            }
            else
            {
                printf("坐标解析失败：%s\n", uart2_rx_buf);
            }
        }

        vTaskDelay(10);  // 根据实际情况设置 RTOS 延时
    }
}
/************************************************ 
函数名称 ： TX2_Tast_Creat
功    能 ： 创建任务
参    数 ： 无
返 回 值 ： 无
作    者 ： CRP
*************************************************/
void TX2_Tast_Creat(void)
{
	xTaskCreate(loop, "loop", 256, NULL, 1, NULL);
}

