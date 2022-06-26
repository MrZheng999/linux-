/*******************************************************************************
 * 文件名: bsp_dir.c
 * 作者: 译文哥  、郑劲松
 * 日期：2022年6月26日
 * 版本：v0.0.0
 * linux中深度搜索目录
 *******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include "bsp_dir.h"

/*********************************************************************************
 * Function:  SearchDepth
 * Description： 深度搜索根据文件类型名，把文件链接到链表
 * Parameters:  Path ：文件的路径名  head：链表的头指针  TypeName ：文件类型名
 * Return:      成功：返回0
 * Others:
 **********************************************************************************/
int SearchDepth(const char *Path, P_Node head, char *TypeName)
{
    int count = 0;
    char TmpPath[257] = {0};
    // 打开目录文件
    DIR *fp = opendir(Path);
    if (NULL == fp)
    {
        // perror("open dir error");
        fprintf(stderr, "open dir : %s error:%s\n", Path, strerror(errno));
        return -1;
    }

    while (1)
    {

        // 读取目录项
        struct dirent *dir = readdir(fp);
        if (NULL == dir)
        {
            perror("read dir error");
            break;
        }

        bzero(TmpPath, 257); // 清空临时数组中的内容避免出现误会

        if (dir->d_name[0] == '.') // 如果文件名字以 . 开头的则为隐藏文件， 选择直接忽略
        {
            continue;
        }
        else if (dir->d_type == 4) // 检查是否为目录文件
        {
            // 把当前的路劲以及该目录文件的名字进行拼接作为递归下一个目录的完整路径
            snprintf(TmpPath, 257, "%s/%s", Path, dir->d_name);
            /* 递归调用自己*/
            count += SearchDepth(TmpPath, head, TypeName);
        }
        else if (dir->d_type == 8)
        {
            snprintf(TmpPath, 257, "%s/%s", Path, dir->d_name);
            printf("遍历寻找到普通文件：%s\n", TmpPath);

            char *tmp = strstr(dir->d_name, TypeName); // 在字符串 dir->d_name 找 .bmp 的出现
            if (tmp == NULL)                         // 当 tmp 指向NULL 的时候说明该文件路径名中没有出现后缀名
            {
                continue;
            }

            //判断如果等于指定的TypeName 就添加进链表
            if (0 == strcmp(tmp, TypeName))
            {
                // 用新的文件名等信息创建一个新的节点
                P_Node new = InitList(TmpPath, TypeName); // .jpg  .bmp .mp3 .avi ...

                // 把新节点插入到链表中
                Add2ListHead(head, new);

                count++;
            }
        }
    }

    // 关闭目录文件
    closedir(fp);

    return count;
}
