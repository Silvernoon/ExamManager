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
unsigned int Bsize;
unsigned int Csize;
void Start();
void BStart()
{
    FILE *BlankFile = fopen("BlankQuestions", "a+");
    if (BlankFile == NULL)
    {
        PrintLine("[ERROR]���������ȡ��������");
        return;
    } // Load
    BList = CreateNode(NULL);
    list *B = BList;
    while (1)
    {
        string buffer;
        BlankQuestion *b = malloc(sizeof(BlankQuestion));
        if (b == NULL)
            ERRORCRASH("ָ�벻����");
        if (fscanf(BlankFile, "%X", &b->id) == EOF)
            break;
        fgetc(BlankFile); // ˢ�»���
        fgets(buffer, sizeof(buffer), BlankFile);
        strcpy(b->context, buffer);
        fgets(buffer, sizeof(buffer), BlankFile);
        strcpy(b->answer, buffer);
        BList = ListInsert(BList, CreateNode(b));
        Bsize = b->id;
    }
    fclose(BlankFile);
    BList = B;
}
void CStart()
{
    FILE *ChoiceFile = fopen("ChoiceQuestions", "a+");
    if (ChoiceFile == NULL)
    {
        PrintLine("[ERROR]ѡ��������ȡ��������");
        return;
    } // Load
    CList = CreateNode(NULL);
    list *C = CList;
    while (1)
    {
        string buffer;
        ChoiceQuestion *c = malloc(sizeof(ChoiceQuestion));
        if (c == NULL)
            ERRORCRASH("ָ�벻����");
        if (fscanf(ChoiceFile, "%X", &c->id) == EOF)
            break;
        fgetc(ChoiceFile); // ˢ�»���
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
        CList = ListInsert(CList, CreateNode(c));
        Csize = c->id;
    }
    fclose(ChoiceFile);
    CList = C;
}
void IOStart()
{
    BStart();
    CStart();
}
void AddQuestion()
{
    Clear();
    printf("����Ŀ����Ϊ��\n[1]ѡ����\n[2]�����\n[0]����\n");
    switch (GetControl())
    {
    case 1:
        ChoiceQuestion *c = malloc(sizeof(ChoiceQuestion));
        Clear();
        PrintLine("ѡ����");
        printf("��Ŀ���ݣ�");
        strcpy(c->context, GetString());
        printf("A��");
        strcpy(c->A.context, GetString());
        printf("B��");
        strcpy(c->B.context, GetString());
        printf("C��");
        strcpy(c->C.context, GetString());
        printf("D��");
        strcpy(c->D.context, GetString());
    re:
        printf("\r�𰸣�");
        string context;
        scanf("%s", context);
        if (strlen(context) == 1 && ((context[0] < 'D' && context[0] > 'A') || (context[0] < 'd' && context[0] > 'a')))
            c->answer = context[0];
        else
            goto re;
        ListInsert(CList, CreateNode(c));
        Csize++;
        FILE *ChoiceFile = fopen("ChoiceQuestions", "a");
        fprintf(ChoiceFile, "%08X\n%s\n%s\n%s\n%s\n%s\n%c\n", ++Csize, c->context, c->A.context, c->B.context, c->C.context, c->D.context, c->answer);
        fclose(ChoiceFile);
        break;
    case 2:
        BlankQuestion *b = malloc(sizeof(BlankQuestion));
        Clear();
        printf("�����");
        printf("��Ŀ���ݣ�");
        strcpy(b->context, GetString());
        printf("�𰸣�");
        strcpy(b->answer, GetString());
        ListInsert(BList, CreateNode(b));
        Bsize++;
        FILE *BlankFile = fopen("BlankQuestions", "a");
        fprintf(BlankFile, "%08X\n%s\n%s\n", ++Bsize, b->context, b->answer);
        fclose(BlankFile);
        break;
    case 0:
        break;
    default:
        AddQuestion();
        break;
    }
}

list *findB(list *start, unsigned int id)
{
    while (start != NULL)
    {
        if (start->data != NULL && (*(BlankQuestion *)start->data).id == id)
            return start;
        start = start->next;
    }
    return NULL;
}
list *findC(list *start, unsigned int id)
{
    while (start != NULL)
    {
        if (start->data != NULL && (*(ChoiceQuestion *)start->data).id == id)
            return start;
        start = start->next;
    }
    return NULL;
}
void bWrite(list *start, va_list valist)
{
    BlankQuestion *b = start->data;
    if (b != NULL)
        fprintf(va_arg(valist, void *), "%08X\n%s%s", b->id, b->context, b->answer);
}
void cWrite(list *start, va_list valist)
{
    ChoiceQuestion *c = start->data;
    if (c != NULL)
        fprintf(va_arg(valist, void *), "%08X\n%s%s%s%s%s%c\n", c->id, c->context, c->A.context, c->B.context, c->C.context, c->D.context, c->answer);
}

void RemoveQuestion()
{
    Clear();
    PrintLine("����Ŀ����Ϊ��\n[1]ѡ����\n[2]�����\n[0]����");
    unsigned int id;
    switch (GetControl())
    {
    case 1:
        printf("��Ŀid��");
        scanf("%X", &id);
        if (!RemoveNode(findC(CList, id)))
        {
            printf("��ֵ������\n");
            system("pause");
            RemoveQuestion();
        }
        FILE *ChoiceFile = fopen("ChoiceQuestions", "w");
        Iterator(CList, cWrite, 1, ChoiceFile); // ��ʵ֤�����κ���ͼģ��STL�Ĵ��붼������
        fclose(ChoiceFile);
        break;
    case 2:
        printf("��Ŀid��");
        scanf("%X", &id);
        if (!RemoveNode(findB(BList, id)))
        {
            printf("��ֵ������\n");
            system("pause");
            RemoveQuestion();
        }
        FILE *BlankFile = fopen("BlankQuestions", "w");
        Iterator(BList, bWrite, 1, BlankFile);
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
    printf("�������\n");
    system("pause");
}
void Delete()
{
    system("DEL BlankQuestions");
    system("DEL ChoiceQuestions");
    printf("ɾ�����\n");
    system("pause");
}

void Edit()
{
    system("pause");
    // ��ȡbuffer�ַ���
    char buf[] = "Sivn's First Project";
    // cursorλ��
    DWORD cbPos = 0;
    // ��
    HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);

    // д��buffer
    WriteConsole(stdOut, buf, strlen(buf), &cbPos, NULL);
    WriteConsole(stdIn, buf, strlen(buf), &cbPos, NULL);
    
    // ��ȡbuffer����
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(stdOut, &csbi);

    // �����û�cursorλ��
    csbi.dwCursorPosition.X -= strlen(buf);
    SetConsoleCursorPosition(stdOut, csbi.dwCursorPosition);

    // ����
    string input;
    ReadConsole(stdIn, input, sizeof(input), &cbPos, NULL);
    input[cbPos - 2] = '\0';
}

void Detail()
{
    Clear();
    PrintLine("����Ŀ����Ϊ��\n[1]ѡ����\n[2]�����\n[0]����");
    unsigned int id;
    list *t;
    switch (GetControl())
    {
    case 1:
        printf("��Ŀid��");
        scanf("%X", &id);
        t = findC(CList, id);
        if (t == NULL)
        {
            printf("��ֵ������\n");
            system("pause");
            Detail();
        }
        else
        {
            ChoiceQuestion *c = t->data;
            printf("%08X\n%sA:%sB:%sC:%sD:%s��:%c\n", c->id, c->context, c->A.context, c->B.context, c->C.context, c->D.context, c->answer);
            system("pause");
        }
        break;
    case 2:
        printf("��Ŀid��");
        scanf("%X", &id);
        t = findB(BList, id);
        if (t == NULL)
        {
            printf("��ֵ������\n");
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
