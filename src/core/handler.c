#include "structure.h"
#include "context.h"
#include "queue.h"
#include "debug.h"
#include "../ui/gui.h"
#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>

void handle_ShowingTrain(enum Train_Direction *dir)
{
    Node **train_queue = *dir == LEFT ? get_tq1() : *dir == RIGHT ? get_tq2() : NULL;
    printf("\n______pointeur %p", train_queue);

    Train *t = (Train *)pop(train_queue);
    printf("\n queue new size %d", size(train_queue));
    printf("\n_______pointeur %p", train_queue);
    // if nil pointer - ignore signal

    if (t != NULL)
    {
        SDL_Renderer *renderer = get_rd();
        Sprite *sp = get_sp();
        trigger_train(t, sp, renderer);
        free(t);
    }
    else
    {
        _dp("WARN ! - catched 'show train' signal with empty queue");
    }
}