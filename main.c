#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Actions.c"
void Start()
{
    Clear();
    printf("欢迎来到试卷管理系统\n请输入序号执行操作\n");
    PrintLine("-------------------------------------");
    printf("[1]添加题目\n[2]删除题目\n[3]备份全部试题\n[4]删除全部试题\n[5]修改试题\n[6]试题查询\n[7]统计\n[8]搜索\n[9]生成试卷\n[0]退出程序\n");
    switch (GetControl())
    {
    case 1:
        AddQuestion();
        break;
    case 2:
        RemoveQuestion();
        break;
    case 3:
        Backup();
        break;
    case 4:
        Delete();
        break;
    case 5:
        Edit();
        break;
    case 6:
        Detail();
        break;
    case 7:

        break;
    case 8:
        Search();
        break;
    case 9:
        Generate();
        break;
    case 0:
        exit(0);
    default:
        Start();
        break;
    }
    Start();
}

int main()
{
    Clear();
    IOStart();
    Start();
}
