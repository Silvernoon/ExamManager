#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <sys/stat.h>
#include "Actions.c"
void AddQuestion()
{
    Clear();
    printf("该题目类型为：\n[1]选择题\n[2]填空题\n[0]返回\n");
    switch (_getch())
    {
    case '1':
        Clear();
        ChoiceQuestion *c = malloc(sizeof(ChoiceQuestion));

        printf("选择题\n");
        c->id = ++CList->maxID;
        printf("题目内容：");
        GetString(c->context);
        printf("A：");
        GetString(c->A);
        printf("B：");
        GetString(c->B);
        printf("C：");
        GetString(c->C);
        printf("D：");
        GetString(c->D);
    re:
        printf("\r答案：");
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

        printf("填空题");
        b->id = ++BList->maxID;
        printf("题目内容：");
        GetString(b->context);
        printf("答案：");
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
    printf("该题目类型为：\n[1]选择题\n[2]填空题\n[0]返回\n");
    unsigned int id;
    switch (_getch())
    {
    case '1':
        id = GetID();
        if (!RemoveNode(findC(id)))
        {
            printf("该值不存在\n");
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
            printf("该值不存在\n");
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
    Clear();
    printf("该题目类型为：\n[1]选择题\n[2]填空题\n[0]返回\n");
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
        printf("[1]题目:%s[2]A:%s[3]B:%s[4]C:%s[5]D:%s[6]答案:%c\n", c->context, c->A, c->B, c->C, c->D, c->answer);
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
            printf("\r答案：");
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
        printf("[1]题目:%s[2]答案:%s", b->context, b->answer);
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
    // 临时文件
    FILE *fp = fopen("temp.txt", "w");
    fputs(text, fp);
    fclose(fp);
#pragma region 检测修改保存
    struct stat t, tt;
    stat("temp.txt", &t);
    system("explorer temp.txt");
    do
        stat("temp.txt", &tt);
    while (t.st_atime == tt.st_atime);
#pragma endregion
    printf("已修改\n");
    system("pause");
    // 读取临时文件
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
    printf("该题目类型为：\n[1]选择题\n[2]填空题\n[0]返回\n");
    unsigned int id;
    node *t;
    switch (_getch())
    {
    case '1':
        printf("题目id：");
        scanf("%X", &id);
        t = findC(id);
        if (t == NULL)
        {
            printf("该值不存在\n");
            system("pause");
            Detail();
        }
        else
        {
            ChoiceQuestion *c = t->data;
            printf("%08X\n%sA:%sB:%sC:%sD:%s答案:%c\n", c->id, c->context, c->A, c->B, c->C, c->D, c->answer);
            system("pause");
        }
        break;
    case '2':
        printf("题目id：");
        scanf("%X", &id);
        t = findB(id);
        if (t == NULL)
        {
            printf("该值不存在\n");
            system("pause");
            Detail();
        }
        else
        {
            BlankQuestion *b = t->data;
            printf("%08X\n%s答案:%s", b->id, b->context, b->answer);
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
    printf("选择题总计：%d\n", CList->size);
    printf("填空题总计：%d\n", BList->size);
    system("pause");
}
void Search()
{
    Clear();
    printf("该题目类型为：\n[1]选择题\n[2]填空题\n[0]返回\n");
    char choice = _getch();
    string key;
    node *p;
    switch (choice)
    {
    case '1':
        printf("请输入题目关键词\n");
        GetString(key);
        p = findCStr(key);
        IsNULL(p, Search);
        ChoiceQuestion *c = p->data;
        printf("%08X\n%sA:%sB:%sC:%sD:%s答案:%c\n", c->id, c->context, c->A, c->B, c->C, c->D, c->answer);
        break;
    case '2':
        printf("请输入题目关键词\n");
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
    printf("选择题数量：");
    scanf("%d", &cNum);
    printf("填空题数量：");
    scanf("%d", &bNum);
    if (cNum > CList->size || bNum > BList->size)
    {
        printf("题目数量过多，请扩充题库");
        system("pause");
        return;
    }
    // 创建文件
    FILE *exam = fopen("exam.txt", "w");
    FILE *answer = fopen("answer.txt", "w");
    if (exam == NULL)
        ERRORCRASH("无法生成文件");
    // 选择
    t = randGet(CList, cNum);
    if (cNum > 0)
    {
        fputs("一、选择题\n", exam);
        fputs("一、选择题\n", answer);
    }
    for (unsigned i = 0; i < cNum; i++)
    {
        ChoiceQuestion *tt = t[i];
        fprintf(exam, "%u. %sA：%sB：%sC：%sD：%s", i + 1, tt->context, tt->A, tt->B, tt->C, tt->D);
        fprintf(answer, "%u. %c\n", i + 1, tt->answer);
    }
    // 填空
    t = randGet(BList, bNum);
    if (bNum > 0)
    {
        fputs("二、填空题\n", exam);
        fputs("二、填空题\n", answer);
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
    printf("欢迎来到试卷管理系统\n请输入序号执行操作\n");
    printf("-------------------------------------\n");
    printf("[1]添加题目\n[2]删除题目\n[3]备份全部试题\n[4]删除全部试题\n[5]修改试题\n[6]试题查询\n[7]统计\n[8]搜索\n[9]生成试卷\n[0]退出程序\n");
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
