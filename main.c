#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Actions.c"
void Start()
{
    Clear();
    printf("��ӭ�����Ծ����ϵͳ\n���������ִ�в���\n");
    PrintLine("-------------------------------------");
    printf("[1]�����Ŀ\n[2]ɾ����Ŀ\n[3]����ȫ������\n[4]ɾ��ȫ������\n[5]�޸�����\n[6]�����ѯ\n[7]ͳ��\n[8]����\n[9]�����Ծ�\n[0]�˳�����\n");
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
