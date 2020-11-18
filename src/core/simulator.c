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
    Node *train_queue1 = NULL;
    Node *train_queue2 = NULL;
    pthread_t tid1, tid2; // timer + signal propagation handeling

    // read map + load textures
    read_matrix(20, base_matrix, "./assets/map");
    load_sprites(&sprites, renderer);
    draw_map(sprites, window, base_matrix, renderer);

    // saving cotext
    set_tq1(&train_queue1);
    set_tq2(&train_queue2);
    set_sp(sprites);
    set_rd(renderer);

    // start background task
    Bg_data *lt_bgTask = (Bg_data *)malloc(sizeof(Bg_data));
    lt_bgTask->dir = LEFT;
    lt_bgTask->train_q = &train_queue1;
    Bg_data *rt_bgTask = (Bg_data *)malloc(sizeof(Bg_data));
    rt_bgTask->dir = RIGHT;
    rt_bgTask->train_q = &train_queue2;

    pthread_create(&tid1, NULL, start_background, lt_bgTask);
    pthread_create(&tid2, NULL, start_background, rt_bgTask);
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
    pthread_cancel(tid1);
    pthread_cancel(tid2);
}

void quit(Config *cfg, SDL_Surface *screen, SDL_Surface *menu)
{
    free(cfg);
    SDL_free(screen);
    SDL_free(menu);
}