#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "list_note.h"
list *CreateNode(void *input)
{
    list *p = malloc(sizeof(list));
    if (NULL == p)
    {
        printf("malloc ERROR!\n");
        return NULL;
    }
    memset(p, 0, sizeof(list));
    p->data = input;
    p->next = NULL;
    p->pre = NULL;
    return p;
}

list *ListInsert(list *p, list *new)
{
    if (p == NULL)
        return NULL;
    // pre p new next
    new->next = p->next;
    p->next = new;
    new->pre = p;
    return new;
}

_Bool RemoveNode(list *p)
{
    if (p == NULL)
        return 0;
    if (p->pre != NULL)
        p->pre->next = p->next;
    if (p->next != NULL)
        p->next->pre = p->pre;
    free(p->data);
    free(p);
    return 1;
}

list *Iterator(list *start, void (*f)(void *, va_list), int size, ...)
{
    va_list valist;
    va_start(valist, size);
    while (start != NULL)
    {
        f(start, valist);
        start = start->next;
    }
    va_end(valist);
    return NULL;
}