#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include "Actions.c"
void AddQuestion()
{
    Clear();
    printf("����Ŀ����Ϊ��\n[1]ѡ����\n[2]�����\n[0]����\n");
    switch (_getch())
    {
    case 1:
        Clear();
        ChoiceQuestion *c = malloc(sizeof(ChoiceQuestion));
        PrintLine("ѡ����");
        c->id = CList->size++;
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
        ListPush(CList, CreateNode(c));
        FILE *ChoiceFile = fopen("ChoiceQuestions", "a");
        fprintf(ChoiceFile, "%08X\n%s\n%s\n%s\n%s\n%s\n%c\n", c->id, c->context, c->A.context, c->B.context, c->C.context, c->D.context, c->answer);
        fclose(ChoiceFile);
        break;
    case 2:
        Clear();
        BlankQuestion *b = malloc(sizeof(BlankQuestion));
        printf("�����");
        b->id = BList->size++;
        printf("��Ŀ���ݣ�");
        strcpy(b->context, GetString());
        printf("�𰸣�");
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
    printf("��ӭ�����Ծ����ϵͳ\n���������ִ�в���\n");
    PrintLine("-------------------------------------");
    printf("[1]�����Ŀ\n[2]ɾ����Ŀ\n[3]����ȫ������\n[4]ɾ��ȫ������\n[5]�޸�����\n[6]�����ѯ\n[7]ͳ��\n[8]����\n[9]�����Ծ�\n[0]�˳�����\n");
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
