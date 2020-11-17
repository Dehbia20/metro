#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#include "structure.h"
#include "constants.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "matrix.h"
#include "sprite_map.h"
#include "process.h"
#include "context.h"
#include "../ui/gui.h"

void start(Config *cfg, SDL_Window **window, SDL_Renderer *renderer)
{
    int runningFlag = CONTINUE;
    int base_matrix[20][60];
    Sprite *sprites = NULL;
    Node *train_queue = NULL;
    pthread_t tid; // timer + signal propagation handeling

    // read map + load textures
    read_matrix(20, base_matrix, "./assets/map");
    load_sprites(&sprites, renderer);
    draw_map(sprites, window, base_matrix, renderer);

    // saving cotext
    set_tq(&train_queue);
    set_sp(sprites);
    set_rd(renderer);

    // start background task
    pthread_create(&tid, NULL, start_background, &train_queue);

    do
    {
        SDL_Event e;
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                break;
            else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
                break;
        }

    } while (runningFlag);
    free_sprites(sprites);
    pthread_cancel(tid);
}

void quit(Config *cfg, SDL_Surface *screen, SDL_Surface *menu)
{
    free(cfg);
    SDL_free(screen);
    SDL_free(menu);
}