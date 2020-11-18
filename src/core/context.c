#include "structure.h"
#include <SDL.h>

Node **train_queue1;
Node **train_queue2;
SDL_Renderer *renderer;
Sprite *sprites;

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