#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "BlankQuestion.h"
#include "ChoiceQuestion.h"
#include "Control.h"
#include "list_note.h"
#include "windows.h"
#define IsNULL(p, Func)             \
    {                               \
        void *_p = p;               \
        if (_p == NULL)             \
        {                           \
            printf("��ֵ������\n"); \
            system("pause");        \
            Func();                 \
            return;                 \
        }                           \
    }
typedef char string[256];
list *BList;
list *CList;
void BStart() // ���� ������
{
    FILE *BlankFile = fopen("BlankQuestions", "a+");
    if (BlankFile == NULL)
    {
        ERRORCRASH("[ERROR]���������ȡ��������\n");
        return;
    }
    ListInit(&BList);
    while (true)
    {
        BlankQuestion *b = malloc(sizeof(BlankQuestion));
        if (b == NULL)
            ERRORCRASH("ָ�벻����");
        if (fscanf(BlankFile, "%X\n", &b->id) == EOF)
            break;
        BList->maxID = b->id;
        FGetString(BlankFile, b->context);
        FGetString(BlankFile, b->answer);
        ListPush(BList, CreateNode(b));
    }
    fclose(BlankFile);
}
void CStart() // ���� ѡ�����
{
    FILE *ChoiceFile = fopen("ChoiceQuestions", "a+");
    if (ChoiceFile == NULL)
    {
        ERRORCRASH("[ERROR]ѡ��������ȡ��������");
        return;
    }
    ListInit(&CList);
    while (true)
    {
        ChoiceQuestion *c = malloc(sizeof(ChoiceQuestion));
        if (c == NULL)
            ERRORCRASH("ָ�벻����");
        if (fscanf(ChoiceFile, "%X\n", &c->id) == EOF)
            break;
        CList->maxID = c->id;
        FGetString(ChoiceFile, c->context);
        FGetString(ChoiceFile, c->A);
        FGetString(ChoiceFile, c->B);
        FGetString(ChoiceFile, c->C);
        FGetString(ChoiceFile, c->D);
        c->answer = fgetc(ChoiceFile);
        fgetc(ChoiceFile); // ����\n
        ListPush(CList, CreateNode(c));
    }
    fclose(ChoiceFile);
}
void IOStart()
{
    BStart();
    CStart();
}
node *findB(unsigned int id)
{
    node *start = BList->head;
    while (start != NULL)
    {
        if (start->data != NULL && ((BlankQuestion *)start->data)->id == id)
            return start;
        start = start->next;
    }
    return NULL;
}
node *findC(unsigned int id)
{
    node *start = CList->head;
    while (start != NULL)
    {
        if (start->data != NULL && ((ChoiceQuestion *)start->data)->id == id)
            return start;
        start = start->next;
    }
    return NULL;
}
node *findBStr(char *key)
{
    node *start = BList->head;
    while (start != NULL)
    {
        if (start->data != NULL && strstr(((BlankQuestion *)start->data)->context, key) != NULL)
            return start;
        start = start->next;
    }
    return NULL;
}
node *findCStr(char *key)
{
    node *start = CList->head;
    while (start != NULL)
    {
        if (start->data != NULL && strstr(((ChoiceQuestion *)start->data)->context, key) != NULL)
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
        fprintf(file, "%08X\n%s%s%s%s%s%c\n", c->id, c->context, c->A, c->B, c->C, c->D, c->answer);
}
void **randGet(list *source, unsigned int size) // ˮ�������㷨 O(N)
{                                               // https://zhuanlan.zhihu.com/p/29178293 | https://www.coonote.com/algorithm-note/reservoir-algorithm.html
    srand((unsigned)time(NULL));
    unsigned k = size;
    void **results = malloc(sizeof(void *) * size);
    node *p = source->head->next;
    for (unsigned i = 0; i < k; ++i)
    {
        results[i] = p->data;
        p = p->next;
    }
    for (unsigned i = k; i < source->size; ++i)
    {
        unsigned random = rand() % i;
        if (random < k)
        {
            results[random] = p->data;
            p = p->next;
        }
    }
    return results;
}
unsigned GetID()
{
    unsigned id;
    printf("��Ŀid��");
    scanf("%X", &id);
    return id;
}