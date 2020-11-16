#include "structure.h"
#include "context.h"
#include "queue.h"
#include <stdio.h>

void handle_ShowingTrain()
{
    Node **train_queue = get_trainQueue();
    // if nil pointer - ignore signal
    if (*train_queue != NULL)
    {
        Train *t = (Train *)pop(train_queue);
        printf("\n tchou tchouuuuuuuuuuuuuuuuuuu \n");
    }
}