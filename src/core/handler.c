#include "structure.h"
#include "context.h"
#include "queue.h"
#include "debug.h"
#include "../ui/gui.h"
#include <stdio.h>
#include <SDL.h>

void handle_ShowingTrain()
{
    Node **train_queue = get_trainQueue();
    Train *t = (Train *)pop(train_queue);

    // if nil pointer - ignore signal

    if (*train_queue != NULL)
    {
        SDL_Renderer *renderer = get_rd();
        Sprite *sp = get_sp();
        trigger_train(t, sp, renderer);
    }
    else
    {
        printf("Merde !!");
    }
}