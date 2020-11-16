#include "structure.h"

Node **train_queue;

Node **get_trainQueue()
{
    return train_queue;
}

persist(Node **tq)
{
    train_queue = tq;
}