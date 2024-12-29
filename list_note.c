#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list_note.h"
void ListInit(list **l) // 链表初始化
{
    *l = malloc(sizeof(list));
    (*l)->head = (*l)->tail = CreateNode(NULL);
    (*l)->size = 0;
    (*l)->maxID = -1;
}
node *CreateNode(void *input) // 开节点
{
    node *p = malloc(sizeof(node));
    if (p == NULL)
    {
        printf("malloc ERROR!\n");
        return NULL;
    }
    p->data = input;
    p->next = NULL;
    p->pre = NULL;
    return p;
}
node *ListInsert(node *p, node *n) // 插入
{
    if (p == NULL)
        return NULL;
    // pre p n next
    n->pre = p;
    n->next = p->next;
    if (p->next != NULL)
        p->next->pre = n;
    p->next = n;
    return n;
}
void ListPush(list *l, node *n) // 推入，即尾部添加
{
    ListInsert(l->tail, n);
    l->tail = n;
    l->size++;
}
bool RemoveNode(node *p) // 删除节点
{
    if (p == NULL)
        return false;
    if (p->pre != NULL)
        p->pre->next = p->next;
    if (p->next != NULL)
        p->next->pre = p->pre;
    free(p->data);
    free(p);
    return true;
}