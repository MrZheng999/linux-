/*******************************************************************************
 * 文件名: bsp_list.c
 * 作者: 译文哥  、郑劲松
 * 日期：2022年6月25日
 * 版本：v0.0.0
 * linux中为创建链表目录的支持包
 *******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bsp_list.h"


/*********************************************************************************
 * Function:  InitList
 * Description： 初始节点和头节点
 * Parameters:     NewName ：文件的路径名  NewTpye：文件的类型 
 * Return:      成功：返回0
 * Others:
 **********************************************************************************/
P_Node InitList(char *NewName, char *NewTpye)
{

    // 在【堆】空间中申请内存  malloc / calloc
    P_Node new = calloc(1, sizeof(Node));

    // 初始化数据域
    if (NewName != NULL) // 头节点初始化， 不需要理会数据域 （头节点不存放有效数据）
    {
        // new->PahtName = NewName;  把新的路径名存入到新节点的数据域中 strcpy / memcpy
        strncpy(new->PahtName, NewName, ARR_LEN); // 初始化名字
        strncpy(new->Type, NewTpye, Type_LEN);    // 初始化名字
    }

    // 指针域初始化
    new->Next = new->Prev = new;

    return new;
}

/*********************************************************************************
 * Function:  Add2ListHead
 * Description： 从链表头部添加节点
 * Parameters:     head ：链表的头指针  new：新的数据指针  
 * Return:      成功：返回0
 * Others:
 **********************************************************************************/
int Add2ListHead(P_Node head, P_Node new)
{

    if (head == NULL)
    {
        printf("链表异常....\n");
        return -1;
    }

    // 1. 新节点的后继 指向第一个有效数据
    new->Next = head->Next;

    // 2. 新节点的前驱指针 指向头节点
    new->Prev = head;

    // 3. 头节点的后继执行新节点
    head->Next = new;

    // 4. 第一个有效数据节点的前驱指向 新节点
    new->Next->Prev = new;

    return 0;
}

/*********************************************************************************
 * Function:  Add2ListTail
 * Description： 从链表尾部添加节点
 * Parameters:     head ：链表的头指针  new ：新的节点指针
 * Return:      成功插入：返回 0
 * Others:
 **********************************************************************************/
int Add2ListTail(P_Node head, P_Node new)
{

    if (head == NULL)
    {
        printf("链表异常....\n");
        return -1;
    }

    // 1. 新节点的后继 指向头节点
    new->Next = head;

    // 2. 新节点的前驱指针 指向最后一个有效数据节点
    new->Prev = head->Prev;

    // 3. 头节点的前驱执行新节点
    head->Prev = new;

    // 4. 最后一个有效数据节点的后继指向 新节点
    new->Prev->Next = new;

    return 0;
}

/*********************************************************************************
 * Function:  SearchNode
 * Description： 查找数据
 * Parameters:     head ：链表的头指针  Name：文件的路径名  Type  ：文件的类型
 * Return:      查找成功：返回 数据的节点指针  查找失败：返回空指针
 * Others:
 **********************************************************************************/
P_Node SearchNode(P_Node head, char *fname, char *type)
{
    if (head == NULL)
    {
        printf("链表异常....\n");
        exit(-1);
    }
    //遍历链表
    for (P_Node tmp = head->Next; tmp != head; tmp = tmp->Next)
    {

        char *Same = strstr(tmp->PahtName, fname); //查找文件名有没有出现
        if (Same == NULL)
        {
            continue;
        }
        //找到文件
        if (0 == strcmp(tmp->Type, type)) //并且文件类型正确
        {
            return tmp;
        }
    }

    return NULL;
}

int DisplayList(P_Node head)
{

    if (head == NULL || head->Next == head)
    {
        printf("链表为空或异常....\n");
        return -1;
    }

    //     临时指针 = 第一个有效节点
    for (P_Node tmp = head->Next; tmp != head; tmp = tmp->Next)
    {
        printf("当前节点数据：%s:%s\n", tmp->PahtName, tmp->Type);
    }

    return 0;
}

/*********************************************************************************
 * Function:  ModifyNode
 * Description： 修改数据
 * Parameters:     head ：链表的头指针  new ：新的节点指针
 * Return:      成功插入：返回 0
 * Others:
 **********************************************************************************/
int ModifyNode(P_Node head, char *NewName, char *NewType, char *OldName, char *OldType)
{

    P_Node Find = SearchNode(head, OldName, OldType);
    if (Find == NULL)
    {
        printf("修改时查找旧数据异常....\n");
        return -1;
    }

    strncpy(Find->PahtName, NewName, ARR_LEN); // 修改化名字
    strncpy(Find->Type, NewType, Type_LEN);    // 修改类型

    return 0;
}

/*********************************************************************************
 * Function:  NodeDelete
 * Description： 删除数据
 * Parameters:     head ：链表的头指针  Name：文件的路径名  Type  ：文件的类型
 * Return:      成功删除：返回 0
 * Others:
 **********************************************************************************/
int NodeDelete(P_Node head, char *Name, char *Type)
{

    P_Node Find = SearchNode(head, Name, Type);
    if (Find == NULL)
    {
        printf("删除时查找旧数据异常....\n");
        return -1;
    }

    Find->Prev->Next = Find->Next;
    Find->Next->Prev = Find->Prev;
    //释放改节点的内存空间
    printf("删除的节点数据：路径名 : %s 文件类型 : %s  \n", Find->PahtName, Find->Type);
    free(Find);

    return 0;
}
