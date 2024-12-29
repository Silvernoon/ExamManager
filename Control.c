typedef char string[256];
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Control.h"
void Clear()
{
    system("cls");
}
void FGetString(FILE *fp, string out)
{
    fgets(out, sizeof(string), fp);
}
void GetString(string out)
{
    gets_s(out, sizeof(string));
    strcat(out, "\n");
}
void ERRORCRASH(char *word)
{
    printf(word);
    system("pause");
    exit(1);
}