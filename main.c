#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <sys/stat.h>
#include "Actions.c"
void AddQuestion()
{
    Clear();
    printf("����Ŀ����Ϊ��\n[1]ѡ����\n[2]�����\n[0]����\n");
    switch (_getch())
    {
    case '1':
        Clear();
        ChoiceQuestion *c = malloc(sizeof(ChoiceQuestion));

        printf("ѡ����\n");
        c->id = ++CList->maxID;
        printf("��Ŀ���ݣ�");
        GetString(c->context);
        printf("A��");
        GetString(c->A);
        printf("B��");
        GetString(c->B);
        printf("C��");
        GetString(c->C);
        printf("D��");
        GetString(c->D);
    re:
        printf("\r�𰸣�");
        string context;
        GetString(context);
        if (strlen(context) == 2 && ((context[0] <= 'D' && context[0] >= 'A') || (context[0] <= 'd' && context[0] >= 'a')))
            c->answer = context[0];
        else
            goto re;

        ListPush(CList, CreateNode(c));
        FILE *ChoiceFile = fopen("ChoiceQuestions", "a");
        fprintf(ChoiceFile, "%08X\n%s%s%s%s%s%c\n", c->id, c->context, c->A, c->B, c->C, c->D, c->answer);
        fclose(ChoiceFile);
        break;
    case '2':
        Clear();
        BlankQuestion *b = malloc(sizeof(BlankQuestion));

        printf("�����");
        b->id = ++BList->maxID;
        printf("��Ŀ���ݣ�");
        GetString(b->context);
        printf("�𰸣�");
        GetString(b->answer);

        ListPush(BList, CreateNode(b));
        FILE *BlankFile = fopen("BlankQuestions", "a");
        fprintf(BlankFile, "%08X\n%s%s", b->id, b->context, b->answer);
        fclose(BlankFile);
        break;
    case '0':
        break;
    default:
        AddQuestion();
        break;
    }
}
void RemoveQuestion()
{
    Clear();
    printf("����Ŀ����Ϊ��\n[1]ѡ����\n[2]�����\n[0]����\n");
    unsigned int id;
    switch (_getch())
    {
    case '1':
        id = GetID();
        if (!RemoveNode(findC(id)))
        {
            printf("��ֵ������\n");
            system("pause");
            RemoveQuestion();
            return;
        }
        FILE *ChoiceFile = fopen("ChoiceQuestions", "w");
        Iterator(CList, cWrite, ChoiceFile);
        fclose(ChoiceFile);
        break;
    case '2':
        id = GetID();
        if (!RemoveNode(findB(id)))
        {
            printf("��ֵ������\n");
            system("pause");
            RemoveQuestion();
            return;
        }
        FILE *BlankFile = fopen("BlankQuestions", "w");
        Iterator(BList, bWrite, BlankFile);
        fclose(BlankFile);
        break;
    case '0':
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
    Clear();
    printf("����Ŀ����Ϊ��\n[1]ѡ����\n[2]�����\n[0]����\n");
    char *text;
    node *p;
    char choice = _getch();
    unsigned int id;
    switch (choice)
    {
    case '1':
        id = GetID();
        p = findC(id);
        IsNULL(p, Edit);
        ChoiceQuestion *c = p->data;
        printf("[1]��Ŀ:%s[2]A:%s[3]B:%s[4]C:%s[5]D:%s[6]��:%c\n", c->context, c->A, c->B, c->C, c->D, c->answer);
        switch (_getch())
        {
        case '1':
            text = c->context;
            break;
        case '2':
            text = c->A;
            break;
        case '3':
            text = c->B;
            break;
        case '4':
            text = c->C;
            break;
        case '5':
            text = c->D;
            break;
        case '6':
        rr:
            printf("\r�𰸣�");
            string context;
            GetString(context);
            if (strlen(context) == 1 && ((context[0] <= 'D' && context[0] >= 'A') || (context[0] <= 'd' && context[0] >= 'a')))
                c->answer = context[0];
            else
                goto rr;
            return;
        default:
            Edit();
            return;
        }
        break;
    case '2':
        id = GetID();
        p = findB(id);
        IsNULL(p, Edit);
        BlankQuestion *b = p->data;
        printf("[1]��Ŀ:%s[2]��:%s", b->context, b->answer);
        switch (_getch())
        {
        case '1':
            text = b->context;
            break;
        case '2':
            text = b->answer;
            return;
        default:
            Edit();
            return;
        }
        break;
    case '0':
        return;
    default:
        Edit();
        return;
    }
    // ��ʱ�ļ�
    FILE *fp = fopen("temp.txt", "w");
    fputs(text, fp);
    fclose(fp);
#pragma region ����޸ı���
    struct stat t, tt;
    stat("temp.txt", &t);
    system("explorer temp.txt");
    do
        stat("temp.txt", &tt);
    while (t.st_atime == tt.st_atime);
#pragma endregion
    printf("���޸�\n");
    system("pause");
    // ��ȡ��ʱ�ļ�
    fp = fopen("temp.txt", "r");
    fgets(text, sizeof(string), fp);
    fclose(fp);
    system("DEL temp.txt");
    switch (choice)
    {
    case '1':
        fp = fopen("ChoiceQuestions", "w");
        Iterator(CList, cWrite, fp);
        fclose(fp);
        break;
    case '2':
        fp = fopen("BlankQuestions", "w");
        Iterator(BList, bWrite, fp);
        fclose(fp);
        break;
    }
}
void Detail()
{
    Clear();
    printf("����Ŀ����Ϊ��\n[1]ѡ����\n[2]�����\n[0]����\n");
    unsigned int id;
    node *t;
    switch (_getch())
    {
    case '1':
        printf("��Ŀid��");
        scanf("%X", &id);
        t = findC(id);
        if (t == NULL)
        {
            printf("��ֵ������\n");
            system("pause");
            Detail();
        }
        else
        {
            ChoiceQuestion *c = t->data;
            printf("%08X\n%sA:%sB:%sC:%sD:%s��:%c\n", c->id, c->context, c->A, c->B, c->C, c->D, c->answer);
            system("pause");
        }
        break;
    case '2':
        printf("��Ŀid��");
        scanf("%X", &id);
        t = findB(id);
        if (t == NULL)
        {
            printf("��ֵ������\n");
            system("pause");
            Detail();
        }
        else
        {
            BlankQuestion *b = t->data;
            printf("%08X\n%s��:%s", b->id, b->context, b->answer);
            system("pause");
        }
        break;
    case '0':
        break;
    default:
        Detail();
        break;
    }
}
void Stat()
{
    Clear();
    printf("ѡ�����ܼƣ�%d\n", CList->size);
    printf("������ܼƣ�%d\n", BList->size);
    system("pause");
}
void Search()
{
    Clear();
    printf("����Ŀ����Ϊ��\n[1]ѡ����\n[2]�����\n[0]����\n");
    char choice = _getch();
    string key;
    node *p;
    switch (choice)
    {
    case '1':
        printf("��������Ŀ�ؼ���\n");
        GetString(key);
        p = findCStr(key);
        IsNULL(p, Search);
        ChoiceQuestion *c = p->data;
        printf("%08X\n%sA:%sB:%sC:%sD:%s��:%c\n", c->id, c->context, c->A, c->B, c->C, c->D, c->answer);
        break;
    case '2':
        printf("��������Ŀ�ؼ���\n");
        GetString(key);
        p = findBStr(key);
        IsNULL(p, Search);
        BlankQuestion *b = p->data;
        printf("%08X\n%s%s", b->id, b->context, b->answer);
        break;
    case '0':
        return;
    }
    system("pause");
}
void Generate()
{
    Clear();
    unsigned cNum, bNum;
    void **t;
    printf("ѡ����������");
    scanf("%d", &cNum);
    printf("�����������");
    scanf("%d", &bNum);
    if (cNum > CList->size || bNum > BList->size)
    {
        printf("��Ŀ�������࣬���������");
        system("pause");
        return;
    }
    // �����ļ�
    FILE *exam = fopen("exam.txt", "w");
    FILE *answer = fopen("answer.txt", "w");
    if (exam == NULL)
        ERRORCRASH("�޷������ļ�");
    // ѡ��
    t = randGet(CList, cNum);
    if (cNum > 0)
    {
        fputs("һ��ѡ����\n", exam);
        fputs("һ��ѡ����\n", answer);
    }
    for (unsigned i = 0; i < cNum; i++)
    {
        ChoiceQuestion *tt = t[i];
        fprintf(exam, "%u. %sA��%sB��%sC��%sD��%s", i + 1, tt->context, tt->A, tt->B, tt->C, tt->D);
        fprintf(answer, "%u. %c\n", i + 1, tt->answer);
    }
    // ���
    t = randGet(BList, bNum);
    if (bNum > 0)
    {
        fputs("���������\n", exam);
        fputs("���������\n", answer);
    }
    for (unsigned i = 0; i < bNum; i++)
    {
        BlankQuestion *tt = t[i];
        fprintf(exam, "%u. %s", i + 1, tt->context);
        fprintf(answer, "%u. %s", i + 1, tt->answer);
    }
    free(t);
    fclose(exam);
    fclose(answer);
    // system("explorer exam.txt");
}
void Start()
{
    rewind(stdin);
    Clear();
    printf("��ӭ�����Ծ����ϵͳ\n���������ִ�в���\n");
    printf("-------------------------------------\n");
    printf("[1]�����Ŀ\n[2]ɾ����Ŀ\n[3]����ȫ������\n[4]ɾ��ȫ������\n[5]�޸�����\n[6]�����ѯ\n[7]ͳ��\n[8]����\n[9]�����Ծ�\n[0]�˳�����\n");
    switch (_getch())
    {
    case '1':
        AddQuestion();
        break;
    case '2':
        RemoveQuestion();
        break;
    case '3':
        Backup();
        break;
    case '4':
        Delete();
        break;
    case '5':
        Edit();
        break;
    case '6':
        Detail();
        break;
    case '7':
        Stat();
        break;
    case '8':
        Search();
        break;
    case '9':
        Generate();
        break;
    case '0':
        exit(0);
    default:
        Start();
        break;
    }
    Start();
}
int main()
{
    // SetConsoleOutputCP(65001);
    Clear();
    IOStart();
    Start();
}
