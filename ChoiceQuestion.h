#pragma once
typedef char string[256];

typedef struct
{
    unsigned int id;
    string context;
    string A,B,C,D;
    char answer;
}ChoiceQuestion;