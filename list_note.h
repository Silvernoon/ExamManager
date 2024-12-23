#pragma once
#include <stdbool.h>
#define Iterator(List, Func, ...) \
    { /*无返回迭代器*/      \
        list *l = List;           \
        node *n = l->head;        \
        while (n != NULL)         \
        {                         \
            Func(n, __VA_ARGS__); \
            n = n->next;          \
        }                         \
    }
#define IteratorReturn(List, ReturnType, Func, ...) \
    ({ /*有返回迭代器*/                       \
       list *l = List;                              \
       node *n = l->head;                           \
       ReturnType result;                           \
       while (n != NULL)                            \
       {                                            \
           result = Func(n, __VA_ARGS__);           \
           n = n->next;                             \
       }                                            \
       result                                       \
    })
typedef struct Node
{
    struct Node *pre;
    void *data; // 泛型
    struct Node *next;
} node;
typedef struct List
{
    unsigned int size;
    node *head;
    node *tail;
} list;
list *ListInit(list *l);
node *CreateNode(void *input);
node *ListInsert(node *p, node *n);
void *ListPush(list *l, node *n);
bool RemoveNode(node *p);