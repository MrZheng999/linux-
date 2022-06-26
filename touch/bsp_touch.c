/*******************************************************************************
 * 文件名: bsp_touch.c
 * 作者: 译文哥  、郑劲松
 * 日期：2022年6月24日
 * 版本：v0.0.1
 * linux中触摸屏支持包
 *******************************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/input.h>

#include "bsp_touch.h"

/*********************************************************************************
 * Function:  TouchInit
 * Description： 初始化触摸屏
 * Parameters:    空
 * Return:       返回文件描述符
 * Others:
 **********************************************************************************/
int TouchInit(void)
{

    // 打开触摸屏
    int fd_ts = open(TOUCH_PAHT, O_RDONLY);
    if (-1 == fd_ts)
    {
        perror("touch init error");
        exit(-1); // 直接终止进程 （退出程序）
    }

    return fd_ts; // 结束本函数 （退出本函数）
}

/*********************************************************************************
 * Function:   GetTouchData
 * Description： 获取触摸屏的信息
 * Parameters:   fd_ts:文件描述符
 * Return:       无
 * Others:
 **********************************************************************************/
void GetTouchData(int fd_ts)
{
    struct input_event event;
    //读取触摸屏的设备文件
    read(fd_ts, &event, sizeof(event));

    //获取触摸屏的数据
    printf("Time:%d:%d Type:%d Code:%d Value:%d\n",
           event.time.tv_sec,
           event.time.tv_usec,
           event.type,
           event.code,
           event.value);
}

/*********************************************************************************
 * Function:   GetCoordinates
 * Description： 点击触摸屏后获取触摸屏点击点的x、y轴坐标
 * Parameters:   fd_ts:文件描述符
 * Return:       xyValue型的结构体（x、y轴坐标）
 * Others:
 **********************************************************************************/
xyValue GetCoordinates(int fd_ts)
{
    xyValue x_y;

    struct input_event event;
    while (1)
    {

        // 读取触摸屏的设备文件
        read(fd_ts, &event, sizeof(event));

        if (event.type == EV_ABS) // 判断是否为 触摸屏事件
        {
            if (event.code == ABS_X) // 判断是否为 X 轴
            {
                x_y.x = event.value * 800 / 1024;
            }
            else if (event.code == ABS_Y) // 判断是否为 Y 轴
            {
                x_y.y = event.value * 480 / 600;
            }
        }

        else if (event.type == EV_KEY && event.code == BTN_TOUCH && event.value == 0)
        {
            printf("--(%d,%d)--\n", x_y.x, x_y.y);
            if (x_y.x > 800 || x_y.x < 0 || x_y.y > 480 || x_y.y < 0)
            {
                continue;
            }

            return x_y;
        }
    }
}
/*********************************************************************************
 * Function:   SlideBackward
 * Description： 滑动触摸屏后获取滑动的方向
 * Parameters:   fd_ts:文件描述符
 * Return:       枚举型数据（滑动的方向）
 * Others:
 **********************************************************************************/
Direction SlideBackward(int fd_ts)
{
    // 动态变化的坐标值
    int x = 0;
    int y = 0;
    // 起始坐标
    int s_x = 0;
    int s_y = 0;
    // 结束坐标
    int e_x = 0;
    int e_y = 0;

    // 获取到两个坐标值  起始 / 结束
    struct input_event event;
    while (1)
    {
        // 读取触摸屏的设备文件
        read(fd_ts, &event, sizeof(event));
        // 分析得到坐标值 (松手后返回坐标值)
        if (event.type == EV_ABS) // 判断是否为 触摸屏事件
        {
            if (event.code == ABS_X) // 判断是否为 X 轴
            {
                x = event.value * 800 / 1024;
            }
            else if (event.code == ABS_Y) // 判断是否为 Y 轴
            {
                y = event.value * 480 / 600;
            }
        }

        // 判断是否为按下  开始
        else if (event.type == EV_KEY && event.code == BTN_TOUCH && event.value == 1)
        {
            s_x = x;
            s_y = y;
        }
        // 判断是否为松手  结束了
        else if (event.type == EV_KEY && event.code == BTN_TOUCH && event.value == 0)
        {
            e_x = x;
            e_y = y;

            break; // 跳出 循环体
        }
    }

    int DifferenceX = s_x - e_x;
    int DifferenceY = s_y - e_y;

    if (abs(DifferenceX) > abs(DifferenceY)) // 如果是 横向移动
    {
        if (DifferenceX > 0)
        {
            /* 从右往左移动 */
            return left;
        }
        else
        {
            /* 从左往右移动 */
            return right;
        }
    }
    else // 纵向移动
    {
        if (DifferenceY > 0)
        {
            /* 从下往上移动 */
            return up;
        }
        else
        {
            /* 从上往下移动 */
            return down;
        }
    }
}

/*********************************************************************************
 * Function:   ReleaseTouchscreen
 * Description： 关闭触摸屏设备文件
 * Parameters:   fd_ts:文件描述符
 * Return:      无
 * Others:
 **********************************************************************************/
void ReleaseTouchscreen(int fd_ts)
{
    //关闭触摸屏设备文件
    int fd = close(fd_ts);
    if (-1 == fd)
    {
        perror("touch close error");
        exit(-1); // 直接终止进程 （退出程序）
    }
}
