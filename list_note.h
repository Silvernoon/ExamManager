#pragma once
#include <stdbool.h>
// 事实证明，任何试图模仿STL的代码都很弱智
#define Iterator(List, Func, ...) \
    {                             \
        list *l = (List);         \
        node *n = l->head;        \
        while (n != NULL)         \
        {                         \
            Func(n, __VA_ARGS__); \
            n = n->next;          \
        }                         \
    }

typedef struct Node
{
    struct Node *pre;
    void *data; // 泛型
    struct Node *next;
} node;
typedef struct List
{
    unsigned int size;
    unsigned int maxID;
    node *head;
    node *tail;
} list;
void ListInit(list **l);
node *CreateNode(void *input);
node *ListInsert(node *p, node *n);
void ListPush(list *l, node *n);
bool RemoveNode(node *p);