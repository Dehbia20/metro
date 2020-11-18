#include "structure.h"
#include <stdlib.h>
#include <stdio.h>

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
    if (head == NULL)
    {
        return NULL;
    }
    void *data = (*head)->data;
    printf("\n ancienne adresse %p", *head);
    *head = (*head)->next;
    printf("\n new adresse %p", *head);
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
  free allocated memory to a queue, when it should collected
*/
void free_queue(Node **head)
{
    if (*head == NULL)
    {
        // nil pointer, no need to free
        return;
    }

    while (*head != NULL)
    {
        Node **old = head;
        head = &(*head)->next;
        free(*old);
    }
}

int size(Node **head)
{
    if (*head == NULL)
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
    printf("\nbordel_1 !! %p", head);
    if (head == NULL)
    {
        printf("\nbordel_2 !! %d");

        return NULL;
    }

    int i = 0;

    Node *actual = head;
    while (actual != NULL && i != index)
    {
        actual = actual->next;

        ++i;
    }
    printf("\n####-----%d", i);
    return actual->data;
}