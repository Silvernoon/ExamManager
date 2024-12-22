#pragma once
typedef struct List
{
    struct List *pre;
    void *data; // 泛型
    struct List *next;
} list;

list *CreateNode(void *input);
list *ListInsert(list *p, list *new);
_Bool RemoveNode(list *p);
list *Iterator(list *start, void (*f)(void *, va_list), int size, ...);