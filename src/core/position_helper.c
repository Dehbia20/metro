#include "structure.h"
#include "queue.h"
#include "context.h"
#include <stdio.h>
#include <stdlib.h>
#include "debug.h"

int search_idx(Node **head, Position *pos)
{
    int sz = size(head);
    for (int i = 0; i < sz; i++)
    {
        void *d = get(*head, i);
        if (d != NULL)
        {
            Position *p = (Position *)d;

            if (p->i == pos->i && p->j == pos->j)
            {
                return i;
            }
        }
    }
    return -1;
}
int is_free(Position *pos)
{
    int fp_search = search_idx(get_fp(), pos) >= 0 ? 0 : 1;
    return fp_search;
}

void mark_asFilled(Position *pos)
{
    Node **head = get_fp();
    int idx = search_idx(head, pos);
    if (idx < 0)
    {

        Position *p = (Position *)malloc(sizeof(Position));
        p->i = pos->i;
        p->j = pos->j;
        push_last(head, p);
    }
}

void mark_asFree(Position *pos)
{
    Node **head = get_fp();
    int idx = search_idx(head, pos);

    if (idx >= 0) // element exists in queue => remove it
    {
        q_remove(head, idx);
    }
}
void print(Node **head)
{
    _dp("\n pos : ");
    int sz = size(head);
    for (int i = 0; i < sz; i++)
    {

        Position *p = (Position *)get(*head, i);
        char txt[10];
        sprintf(txt, " [%d, %d]", p->i, p->j);
        _dp(txt);
    }
}
void pretty_print()
{
    print(get_fp());
}