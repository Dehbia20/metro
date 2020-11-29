#include "structure.h"
#include <stdlib.h>
#include <stdio.h>
Node *q_remove(Node **head, int n);
void push_last(Node **head, void *data)
{
    if (*head == NULL)
    {

        *head = (Node *)malloc(sizeof(Node));

        (*head)->data = data;
        (*head)->next = NULL;
    }
    else
    {
        Node **actual = head;
        while ((*actual)->next != NULL)
        {
            actual = &(*actual)->next;
        }
        (*actual)->next = (Node *)malloc(sizeof(Node));
        (*actual)->next->data = data;
        (*actual)->next->next = NULL;
    }
}
/*
  return a pointer on data and break the queue in order 
  to change it's head. after this method call
  head = head->next if exist 
*/
void *pop(Node **head)
{
    if (head == NULL || head == NULL)
    {
        return NULL;
    }
    void *data = (*head)->data;
    *head = (*head)->next;
    return data;
}

void *first(Node **head)
{
    if (*head == NULL)
    {
        return NULL;
    }
    void *data = (*head)->data;
}

/*
  free allocated memory to a queue, when it should be collected
*/
void free_queue(Node **head)
{
    if (head == NULL || *head == NULL)
    {
        // nil pointer, no need to free
        return;
    }
    int sz = size(head);
    for (int i = 0; i < sz; i++)
    {
        q_remove(head, i);
    }
}

int size(Node **head)
{
    if (head == NULL || *head == NULL)
    {
        return 0;
    }

    int i = 0;
    Node *actual = *head;
    while (actual != NULL)
    {
        i++;
        actual = actual->next;
    }
    return i;
}

void *get(Node *head, int index)
{
    if (head == NULL)
    {
        return NULL;
    }

    int i = 0;

    Node *actual = head;
    while (actual != NULL && i != index)
    {
        actual = actual->next;

        ++i;
    }
    if (actual != NULL)
    {
        return actual->data;
    }
    return NULL;
}

Node *q_remove(Node **head, int n)
{
    int retval = -1;
    Node *current = *head;
    Node *temp_node = NULL;

    if (n == 0)
    {
        return pop(head);
    }

    for (int i = 0; i < n - 1; i++)
    {
        if (current->next == NULL)
        {
            return -1;
        }
        current = current->next;
    }

    temp_node = current->next;
    current->next = temp_node->next;
    free(temp_node);
}