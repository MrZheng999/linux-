/*******************************************************************************
 * 文件名: bsp_list.h
 * 作者: 译文哥  、郑劲松
 * 日期：2022年6月25日
 * 版本：v0.0.0
 * linux中为创建链表目录的支持包
 *******************************************************************************/
#ifndef __LIST_H
#define __LIST_H

#define ARR_LEN 257
#define Type_LEN 10


// 结点设计
typedef struct Node
{
    /* data */
    char PahtName[ARR_LEN];
    char Type[Type_LEN]; // J = jpg 文件  B = Bmp 文件 M = MP3 文件  A = AVI 视频文件
    //......

    /* 指针域 */
    struct Node *Next;
    struct Node *Prev;
} Node, *P_Node;

/*
一下两组代码的意思两两等价
Node a ;
struct Node a ;

P_Node ptr ;
struct Node * ptr ;
*/


P_Node InitList(char *NewName, char *NewTpye);
int Add2ListHead(P_Node head, P_Node new);
int Add2ListTail(P_Node head, P_Node new);
P_Node SearchNode(P_Node head, char *fname, char *type);
int DisplayList(P_Node head);
int ModifyNode(P_Node head, char *NewName, char *NewType, char *OldName, char *OldType);
int NodeDelete(P_Node head, char *Name, char *Type);

#endif /*__LIST_H */