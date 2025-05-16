#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tx2_task.h"

// ȫ�ֽṹ�������debug ʱ��ֱ���� Watch �۲�
Position position;

/**
 * @brief  ���ַ����н������꣬��д��ṹ��
 * @param  input     �����ַ��������磺"λ�����꣺x=1.23, y=4.56, z=7.89"
 * @param  position  ����ṹ��ָ��
 * @retval int       0 �ɹ���-1 ʧ��
 */
int parse_pose_line(const char* input, Position* position)
{
    // Ԥ����ȥ����β���з���\r �� \n��
    char buffer[100];
    char* newline = NULL;

    strncpy(buffer, input, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';  // ��֤��βΪ '\0'

    newline = strpbrk(buffer, "\r\n");
    if (newline) *newline = '\0';

    // ƥ���ʽ����
		if (sscanf(buffer, "pose: x=%f, y=%f, z=%f, yaw=%f", &position->x, &position->y, &position->z, &position->yaw) == 4)  {
        return 0;  // �����ɹ�
    } else if (sscanf(buffer, "pose: x=%f, y=%f, z=%f", &position->x, &position->y, &position->z) == 3) {
        position->yaw = 0.0f;  // Ĭ�� yaw Ϊ 0
        return 0;
    }else {
        return -1;  // ʧ��
    }
}


// ��ѭ������
void loop(void *arg)
{
    while (1)
    {
        if (uart2_rx_flag)
        {
            uart2_rx_flag = 0;

            if (parse_pose_line((char*)uart2_rx_buf, &position) == 0)
            {
                printf("��������ɹ���x=%.3f, y=%.3f, z=%.3f, yaw=%.3f\n",position.x, position.y, position.z, position.yaw);
            }
            else
            {
                printf("�������ʧ�ܣ�%s\n", uart2_rx_buf);
            }
        }

        vTaskDelay(10);  // ����ʵ��������� RTOS ��ʱ
    }
}
/************************************************ 
�������� �� TX2_Tast_Creat
��    �� �� ��������
��    �� �� ��
�� �� ֵ �� ��
��    �� �� CRP
*************************************************/
void TX2_Tast_Creat(void)
{
	xTaskCreate(loop, "loop", 256, NULL, 1, NULL);
}

