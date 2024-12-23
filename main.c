#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include "Actions.c"
void AddQuestion()
{
    Clear();
    printf("该题目类型为：\n[1]选择题\n[2]填空题\n[0]返回\n");
    switch (_getch())
    {
    case 1:
        Clear();
        ChoiceQuestion *c = malloc(sizeof(ChoiceQuestion));
        PrintLine("选择题");
        c->id = CList->size++;
        printf("题目内容：");
        strcpy(c->context, GetString());
        printf("A：");
        strcpy(c->A.context, GetString());
        printf("B：");
        strcpy(c->B.context, GetString());
        printf("C：");
        strcpy(c->C.context, GetString());
        printf("D：");
        strcpy(c->D.context, GetString());
    re:
        printf("\r答案：");
        string context;
        scanf("%s", context);
        if (strlen(context) == 1 && ((context[0] < 'D' && context[0] > 'A') || (context[0] < 'd' && context[0] > 'a')))
            c->answer = context[0];
        else
            goto re;
        ListPush(CList, CreateNode(c));
        FILE *ChoiceFile = fopen("ChoiceQuestions", "a");
        fprintf(ChoiceFile, "%08X\n%s\n%s\n%s\n%s\n%s\n%c\n", c->id, c->context, c->A.context, c->B.context, c->C.context, c->D.context, c->answer);
        fclose(ChoiceFile);
        break;
    case 2:
        Clear();
        BlankQuestion *b = malloc(sizeof(BlankQuestion));
        printf("填空题");
        b->id = BList->size++;
        printf("题目内容：");
        strcpy(b->context, GetString());
        printf("答案：");
        strcpy(b->answer, GetString());
        ListPush(BList, CreateNode(b));
        FILE *BlankFile = fopen("BlankQuestions", "a");
        fprintf(BlankFile, "%08X\n%s\n%s\n", b->id, b->context, b->answer);
        fclose(BlankFile);
        break;
    case 0:
        break;
    default:
        AddQuestion();
        break;
    }
}
void Start()
{
    Clear();
    printf("欢迎来到试卷管理系统\n请输入序号执行操作\n");
    PrintLine("-------------------------------------");
    printf("[1]添加题目\n[2]删除题目\n[3]备份全部试题\n[4]删除全部试题\n[5]修改试题\n[6]试题查询\n[7]统计\n[8]搜索\n[9]生成试卷\n[0]退出程序\n");
    switch (_getch())
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
