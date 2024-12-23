typedef char string[256];
#include "Control.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void PrintLine(string a)
{
    printf(a);
    printf("\n");
}
void Clear()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
char *GetString()
{
    string out;
    scanf("%s", out);
    return out;
}
void ERRORCRASH(char *word)
{
    printf(word);
    system("pause");
    exit(1);
}