/*******************************************************************************
 * 文件名: bsp_dir.h
 * 作者: 译文哥  、郑劲松
 * 日期：2022年6月26日
 * 版本：v0.0.0
 * linux中  使用bsp_dir.h  请包含  bsp_list.h
 *******************************************************************************/
#include "bsp_list.h"

#ifndef __DIR_H
#define __DIR_H

int SearchDepth(const char *Path, P_Node head, char *TypeName);

#endif /*__DIR_H */