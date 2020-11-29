#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#include "structure.h"
#include "constants.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <unistd.h>
#include "matrix.h"
#include "sprite_map.h"
#include "tr_process.h"
#include "context.h"
#include "../ui/gui.h"
#include "debug.h"
#include "queue.h"
#include "tv_process.h"

void start(Config *cfg, SDL_Window **window, SDL_Renderer *renderer)
{
    int runningFlag = CONTINUE;
    int base_matrix[20][60];
    Sprite *sprites = NULL;
    Node *train_queue1 = NULL;           // train queue (left to right)
    Node *train_queue2 = NULL;           // train queue (right to left)
    Node *passengers = NULL;             // passenger queue
    Node *filledPos = NULL;              // queue of filled position
    Node *filledPosBuffer = NULL;        // buffer where node to desallocate in next iteration are stored
    pthread_t tid1, tid2;                // background task for train generation and animation
    pthread_t tid3;                      // background task for travelers generation
    pthread_mutex_t rd_mutex, cfg_mutex; // renderer mutex & config mutex
    // read map + load textures
    read_matrix(20, base_matrix, "./assets/map");
    load_sprites(&sprites, renderer);
    draw_map(sprites, window, base_matrix, renderer);

    pthread_mutex_init(&rd_mutex, NULL);
    pthread_mutex_init(&cfg_mutex, NULL);

    // saving cotext
    set_tq1(&train_queue1);
    set_tq2(&train_queue2);
    set_sp(sprites);
    set_rd(renderer);
    set_cfg(cfg);
    set_psngr(&passengers);
    set_rdMutex(&rd_mutex);
    set_fp(&filledPos);
    set_fpb(&filledPosBuffer);

    _dp("context saved...");

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
            else if (e.type == SDL_KEYUP)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    runningFlag = STOP;
                    break;
                case SDLK_t: // disable train with passenger mode (enable train only)
                    pthread_mutex_lock(&cfg_mutex);

                    if (cfg->mode == TRAIN_TRAVELLER)
                    {
                        cfg->mode = ONLY_TRAIN;
                        _dp("Destroying generation process");
                        pthread_cancel(tid3);
                    }
                    pthread_mutex_unlock(&cfg_mutex);

                    break;
                    // enable train with passenger mode
                case SDLK_p:
                    //pthread_mutex_lock(&cfg_mutex);

                    if (cfg->mode == ONLY_TRAIN)
                    {

                        cfg->mode = TRAIN_TRAVELLER;
                        _dp("\nstarting generation process");
                        pthread_create(&tid3, NULL, start_generation, &passengers);
                    }
                    //pthread_mutex_unlock(&cfg_mutex);

                    break;
                    // enable / disable trace
                case SDLK_d:
                    cfg->trace = cfg->trace == NONE ? DEBUG : NONE;
                    break;
                case SDLK_a: // accelerate generation
                    if (cfg->generationPauseTime >= MIN_TV_GEN_PAUSE_TIME + 10)
                    {
                        pthread_mutex_lock(&cfg_mutex);
                        cfg->generationPauseTime -= 10;
                        pthread_mutex_unlock(&cfg_mutex);
                    }
                    break;
                case SDLK_z: //decelerate generation
                    if (cfg->generationPauseTime <= MAX_TV_GEN_PAUSE_TIME - 10)
                    {
                        pthread_mutex_lock(&cfg_mutex);
                        cfg->generationPauseTime += 10;
                        pthread_mutex_unlock(&cfg_mutex);
                    }
                    break;

                default:
                    _dp("Warn - unmapped key - ignoring...");
                }
            }
        }
    } while (runningFlag);
    free_sprites(sprites);
    pthread_cancel(tid1);
    pthread_cancel(tid2);
    pthread_cancel(tid3);
    pthread_mutexattr_destroy(&rd_mutex);
    pthread_mutex_destroy(&cfg_mutex);
    //free_queue(train_queue1);
    //free_queue(train_queue2);
    //free_queue(passengers);
}

void quit(Config *cfg, SDL_Surface *screen, SDL_Surface *menu)
{
    free(cfg);
    SDL_free(screen);
    SDL_free(menu);
}
