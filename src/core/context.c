#define HAVE_STRUCT_TIMESPEC

#include "structure.h"
#include <SDL.h>
#include <pthread.h>

Node **train_queue1;
Node **train_queue2;
Node **passengers;
Node **filledPos;
Node **filledPosBuffer;
SDL_Renderer *renderer;
Sprite *sprites;
Config *cfg;
pthread_mutex_t *rd_mutex;
pthread_mutex_t *cfg_mutex;

Node **get_tq1()
{
    return train_queue1;
}

void set_tq1(Node **tq)
{
    train_queue1 = tq;
}
Node **get_tq2()
{
    return train_queue2;
}

void set_tq2(Node **tq)
{
    train_queue2 = tq;
}
void set_rd(SDL_Renderer *rd)
{
    renderer = rd;
}

SDL_Renderer *get_rd()
{
    return renderer;
}

void set_sp(Sprite *sp)
{
    sprites = sp;
}

Sprite *get_sp()
{
    return sprites;
}

void set_cfg(Config *c)
{
    cfg = c;
}
Config *get_cfg()
{
    return cfg;
}
Node **get_psngr()
{
    return passengers;
}

void set_psngr(Node **psgnr)
{
    passengers = psgnr;
}

void set_rdMutex(pthread_mutex_t *mutex)
{
    rd_mutex = mutex;
}

pthread_mutex_t *get_rdMutex()
{
    return rd_mutex;
}

void set_cfgMutex(pthread_mutex_t *mutex)
{
    cfg_mutex = mutex;
}

pthread_mutex_t *get_cfgMutex()
{
    return rd_mutex;
}

Node **get_fp()
{
    return filledPos;
}

void set_fp(Node **fp)
{
    filledPos = fp;
}

Node **get_fpb()
{
    return filledPosBuffer;
}

void set_fpb(Node **fpb)
{
    filledPosBuffer = fpb;
}
