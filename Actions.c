#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "BlankQuestion.h"
#include "ChoiceQuestion.h"
#include "Control.h"
#include "list_note.h"
#include "windows.h"
#include "wchar.h"
typedef char string[256];
list *BList;
list *CList;
void BStart()
{
    FILE *BlankFile = fopen("BlankQuestions", "a+");
    if (BlankFile == NULL)
    {
        PrintLine("[ERROR]填空题题库读取发生错误");
        return;
    } // Load
    ListInit(BList);
    while (1)
    {
        string buffer;
        BlankQuestion *b = malloc(sizeof(BlankQuestion));
        if (b == NULL)
            ERRORCRASH("指针不存在");
        if (fscanf(BlankFile, "%X", &b->id) == EOF)
            break;
        fgetc(BlankFile); // 刷新缓冲
        fgets(buffer, sizeof(buffer), BlankFile);
        strcpy(b->context, buffer);
        fgets(buffer, sizeof(buffer), BlankFile);
        strcpy(b->answer, buffer);
        ListPush(BList, CreateNode(b));
    }
    fclose(BlankFile);
}
void CStart()
{
    FILE *ChoiceFile = fopen("ChoiceQuestions", "a+");
    if (ChoiceFile == NULL)
    {
        PrintLine("[ERROR]选择题题库读取发生错误");
        return;
    } // Load
    ListInit(CList);
    while (1)
    {
        string buffer;
        ChoiceQuestion *c = malloc(sizeof(ChoiceQuestion));
        if (c == NULL)
            ERRORCRASH("指针不存在");
        if (fscanf(ChoiceFile, "%X", &c->id) == EOF)
            break;
        fgetc(ChoiceFile); // 刷新缓冲
        fgets(buffer, sizeof(buffer), ChoiceFile);
        strcpy(c->context, buffer);
        fgets(buffer, sizeof(buffer), ChoiceFile);
        strcpy(c->A.context, buffer);
        fgets(buffer, sizeof(buffer), ChoiceFile);
        strcpy(c->B.context, buffer);
        fgets(buffer, sizeof(buffer), ChoiceFile);
        strcpy(c->C.context, buffer);
        fgets(buffer, sizeof(buffer), ChoiceFile);
        strcpy(c->D.context, buffer);
        c->answer = fgetc(ChoiceFile);
        ListPush(CList, CreateNode(c));
    }
    fclose(ChoiceFile);
}
void IOStart()
{
    BStart();
    CStart();
}
node *findB(node *node, unsigned int id)
{
    
    while (node != NULL)
    {
        if (node->data != NULL && (*(BlankQuestion *)node->data).id == id)
            return node;
        node = node->next;
    }
    return NULL;
}
node *findC(node *start, unsigned int id)
{
    while (start != NULL)
    {
        if (start->data != NULL && (*(ChoiceQuestion *)start->data).id == id)
            return start;
        start = start->next;
    }
    return NULL;
}
void bWrite(node *node, FILE *file)
{
    BlankQuestion *b = node->data;
    if (b != NULL)
        fprintf(file, "%08X\n%s%s", b->id, b->context, b->answer);
}
void cWrite(node *node, FILE *file)
{
    ChoiceQuestion *c = node->data;
    if (c != NULL)
        fprintf(file, "%08X\n%s%s%s%s%s%c\n", c->id, c->context, c->A.context, c->B.context, c->C.context, c->D.context, c->answer);
}

void RemoveQuestion()
{
    Clear();
    PrintLine("该题目类型为：\n[1]选择题\n[2]填空题\n[0]返回");
    unsigned int id;
    switch (_getch())
    {
    case 1:
        printf("题目id：");
        scanf("%X", &id);
        if (!RemoveNode(findC(CList, id)))
        {
            printf("该值不存在\n");
            system("pause");
            RemoveQuestion();
        }
        FILE *ChoiceFile = fopen("ChoiceQuestions", "w");
        Iterator(CList, cWrite, ChoiceFile); // 事实证明，任何试图模仿STL的代码都很弱智
        fclose(ChoiceFile);
        break;
    case 2:
        printf("题目id：");
        scanf("%X", &id);
        if (!RemoveNode(findB(BList, id)))
        {
            printf("该值不存在\n");
            system("pause");
            RemoveQuestion();
        }
        FILE *BlankFile = fopen("BlankQuestions", "w");
        Iterator(&BList, bWrite, BlankFile);
        fclose(BlankFile);
        break;
    case 0:
        break;
    default:
        RemoveQuestion();
        break;
    }
}
void Backup()
{
    system("copy BlankQuestions BlankQuestions.bak");
    system("copy ChoiceQuestions ChoiceQuestions.bak");
    printf("备份完成\n");
    system("pause");
}
void Delete()
{
    system("DEL BlankQuestions");
    system("DEL ChoiceQuestions");
    printf("删除完成\n");
    system("pause");
}

void Edit()
{
    system("pause");
    // 获取buffer字符串
    char buf[] = "Sivn's First Project";
    // cursor位置
    DWORD cbPos = 0;
    // 柄
    HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);

    // 写入buffer
    WriteConsole(stdOut, buf, strlen(buf), &cbPos, NULL);
    WriteConsole(stdIn, buf, strlen(buf), &cbPos, NULL);

    // 读取buffer长度
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(stdOut, &csbi);

    // 设置用户cursor位置
    csbi.dwCursorPosition.X -= strlen(buf);
    SetConsoleCursorPosition(stdOut, csbi.dwCursorPosition);

    // 输入
    string input;
    ReadConsole(stdIn, input, sizeof(input), &cbPos, NULL);
    input[cbPos - 2] = '\0';
}

void Detail()
{
    Clear();
    PrintLine("该题目类型为：\n[1]选择题\n[2]填空题\n[0]返回");
    unsigned int id;
    node *t;
    switch (_getch())
    {
    case 1:
        printf("题目id：");
        scanf("%X", &id);
        t = findC(CList, id);
        if (t == NULL)
        {
            printf("该值不存在\n");
            system("pause");
            Detail();
        }
        else
        {
            ChoiceQuestion *c = t->data;
            printf("%08X\n%sA:%sB:%sC:%sD:%s答案:%c\n", c->id, c->context, c->A.context, c->B.context, c->C.context, c->D.context, c->answer);
            system("pause");
        }
        break;
    case 2:
        printf("题目id：");
        scanf("%X", &id);
        t = findB(BList, id);
        if (t == NULL)
        {
            printf("该值不存在\n");
            system("pause");
            Detail();
        }
        else
        {
            BlankQuestion *b = t->data;
            printf("%08X\n%s%s", b->id, b->context, b->answer);
            system("pause");
        }
        break;
    case 0:
        break;
    default:
        Detail();
        break;
    }
}
void Search()
{
}
void Generate()
{
}
