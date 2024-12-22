#pragma once
typedef char string[256];

typedef struct
{
    string context;
}Choice;

typedef struct
{
    unsigned int id;
    string context;
    Choice A,B,C,D;
    char answer;
}ChoiceQuestion;