#include "structure.h"
void push_last(Node **head, void *data);
void *pop(Node **head);
void free_queue(Node **head);
void *first(Node **head);
int size(Node *head);
Node **get(Node **head, int index);