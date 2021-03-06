#include "structure.h"
void push_last(Node **head, void *data);
void *pop(Node **head);
void free_queue(Node **head);
void *first(Node **head);
int size(Node **head);
void *get(Node *head, int index);
Node *q_remove(Node **head, int n);
int _size(Node **head);