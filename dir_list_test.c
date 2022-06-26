#include <stdio.h>
#include"bsp_dir.h"
#include"bsp_list.h"

int main(int argc, char const *argv[])
{
    
    // 链表初始化
    P_Node head = InitList( NULL , "NULL"  ) ;

    // 目录深度搜索
    int num = SearchDepth( "../../.." , head ,".bmp") ;
    printf("成功检索文件%d个.\n" , num );

    // 遍历显示链表的内容（播放列表）
    DisplayList( head );

  





    return 0;
}
