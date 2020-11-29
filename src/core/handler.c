#include "structure.h"
#include "context.h"
#include "queue.h"
#include "debug.h"
#include "../ui/gui.h"
#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <pthread.h>

void handle_ShowingTrain(enum Train_Direction *dir)
{
    Node **train_queue = *dir == LEFT ? get_tq1() : *dir == RIGHT ? get_tq2() : NULL;

    Train *t = (Train *)pop(train_queue);

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

void handle_drawPsnger(Passenger *p)
{
    Sprite *sp = get_sp();

    SDL_Renderer *rd = get_rd();
    if (p->prevPos == NULL || p->pos->i != p->prevPos->i || p->pos->j != p->prevPos->j)
    {
        draw_psgnr(p, sp, rd);
    }
}

void handle_refresh()
{
    SDL_Renderer *rd = get_rd();
    _dp("refresh screen");
    refresh_screen(rd);
}

int handle_takeTrain(Passenger *p)
{
    pthread_mutex_t *mutex = get_cfgMutex();
    pthread_mutex_lock(mutex);
    int trainStopped = get_cfg()->trainStopped;
    pthread_mutex_unlock(mutex);
    if (trainStopped)
    {
        take_train(p, get_sp(), get_rd());

        return 1;
    }
    return 0;
}