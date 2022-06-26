/*******************************************************************************
 * 文件名: bsp_touch.h
 * 作者: 译文哥  、郑劲松
 * 日期：2022年6月24日
 * 版本：v0.0.1
 * linux中触摸屏支持包
 *******************************************************************************/
#ifndef __TOUCH_H
#define __TOUCH_H

#define TOUCH_PAHT "/dev/input/event0" //触摸屏的设备文件路径

typedef struct CoordinateValues
{
    int x;//点击触摸屏后，获取x轴值
    int y;//点击触摸屏后，获取y轴值
} xyValue;

// 枚举类型实际上是一个取值范围受限制的 整形  0 1 2 3
typedef enum DirectionOf
{
    up,//值为整形的0，表示手在触摸屏向上划
    down,//值为整形的1，表示手在触摸屏向下划
    left,//值为整形的2，表示手在触摸屏向左划
    right//值为整形的3，表示手在触摸屏向右划
} Direction;

//触摸屏的函数声明
int TouchInit(void);
void GetTouchData(int fd_ts);
xyValue GetCoordinates(int fd_ts);
Direction SlideBackward(int fd_ts);
void ReleaseTouchscreen(int fd_ts);


#endif /*__TOUCH_H */