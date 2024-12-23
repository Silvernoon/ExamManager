#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "list_note.h"
list *ListInit(list *l)
{
    l->head = l->tail = CreateNode(NULL);
}
node *CreateNode(void *input)
{
    node *p = malloc(sizeof(node));
    if (NULL == p)
    {
        printf("malloc ERROR!\n");
        return NULL;
    }
    memset(p, 0, sizeof(node));
    p->data = input;
    p->next = NULL;
    p->pre = NULL;
    return p;
}
node *ListInsert(node *p, node *n)
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
void *ListPush(list *l, node *n)
{
    ListInsert(l->tail, n);
    l->tail = n;
    l->size++;
}
bool RemoveNode(node *p)
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