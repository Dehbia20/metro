#include "structure.h"
#include <SDL.h>

Node **train_queue;
SDL_Renderer *renderer;
Sprite *sprites;

Node **get_trainQueue()
{
    return train_queue;
}

void set_tq(Node **tq)
{
    train_queue = tq;
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