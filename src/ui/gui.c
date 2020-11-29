#define HAVE_STRUCT_TIMESPEC
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "../core/constants.h"
#include "../core/structure.h"
#include "../core/sprite_map.h"
#include "helper.h"
#include "../core/debug.h"
#include "../core/context.h"
#include "../core/position_helper.h"
void animate(int size, int j, signed int sign, enum Train_Direction dir, Sprite *lead, Sprite *body_1, Sprite *b_txtr, SDL_Rect *rect, SDL_Renderer *renderer, enum T_animation animation);
void go_beyondScreenLimits(enum Train_Direction dir, Sprite *body_1, Sprite *b_txtr, SDL_Rect *rect, SDL_Renderer *renderer);

void show_screen(SDL_Window **screen, SDL_Renderer **renderer)
{

    *screen = SDL_CreateWindow("Underground subway simulation !",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               WINDOW_W,
                               WINDOW_H,
                               SDL_WINDOW_SHOWN);
    *renderer = SDL_CreateRenderer(*screen, -1, 0);
}

void load_sprites(Sprite **sprites, SDL_Renderer *renderer)
{
    push(sprites, "tile", IMG_LoadTexture(renderer, "./assets/tile.png"));
    push(sprites, "rail", IMG_LoadTexture(renderer, "./assets/rail.png"));
    push(sprites, "ground", IMG_LoadTexture(renderer, "./assets/ground.png"));
    push(sprites, "floor", IMG_LoadTexture(renderer, "./assets/floor.png"));
    push(sprites, "bench", IMG_LoadTexture(renderer, "./assets/bench.png"));
    push(sprites, "t_l1", IMG_LoadTexture(renderer, "./assets/train_lead_l1.png"));
    push(sprites, "t_r1", IMG_LoadTexture(renderer, "./assets/train_lead_r1.png"));
    push(sprites, "t_b", IMG_LoadTexture(renderer, "./assets/train_body_l2.png"));
    push(sprites, "ghost_1", IMG_LoadTexture(renderer, "./assets/ghost1.png"));
    push(sprites, "ghost_2", IMG_LoadTexture(renderer, "./assets/ghost2.png"));
    push(sprites, "ghost_3", IMG_LoadTexture(renderer, "./assets/ghost3.png"));
    push(sprites, "ghost_4", IMG_LoadTexture(renderer, "./assets/ghost4.png"));
}

void draw_map(Sprite *sprites, SDL_Window **window, int matrix[20][60], SDL_Renderer *renderer)
{
    if (*window != NULL && renderer != NULL)
    {
    }
    for (int i = 0; i < 20; ++i)
    {
        for (int j = 0; j < 60; ++j)
        {
            Sprite *sprite = calc_surface(sprites, matrix[i][j]);
            if (sprite != NULL && sprite->surface != NULL)
            {
                int w, h;
                SDL_Rect texr;
                texr.x = calc_pos_x(j);
                texr.y = calc_pos_y(i);
                texr.w = CELL_W;
                texr.h = CELL_H;
                SDL_RenderCopy(renderer, sprite->surface, NULL, &texr);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

void trigger_train(Train *t, Sprite *sprites, SDL_Renderer *renderer)
{
    char seq[30];
    sprintf(seq, "Showing train %s - dir : %s", t->id, t->direction == LEFT ? "left" : "right");
    _dp(seq);

    int i, j, k;

    if (t->direction == LEFT)
    {
        i = TRAIN_LEFT_ROW_IDX;    // row 11
        j = TRAIN_LEFT_START_CELL; // last case (first case from the right)
        k = TRAIN_LEFT_STOP_CELL;  // stop at column 26
    }
    else
    {
        i = TRAIN_RIGHT_ROW_IDX;    // row 8
        j = TRAIN_RIGHT_START_CELL; // start at begining
        k = TRAIN_RIGHT_STOP_CELL;  // stops at column 33
    }

    SDL_Rect rect;
    Sprite *lead, *body_1;

    rect.w = CELL_W;
    rect.h = CELL_H;
    rect.y = calc_pos_y(i); // translate index to pixel position

    int size = t->direction == LEFT ? j - k : k - j;
    signed int sign = t->direction == LEFT ? 1 : -1;

    Sprite *b_txtr = calc_surface(sprites, 2);                                         // rail txtr
    lead = t->direction == LEFT ? calc_surface(sprites, 6) : calc_surface(sprites, 8); // train leading texture
    body_1 = calc_surface(sprites, 7);                                                 // body train
    animate(size, j, sign, t->direction, lead, body_1, b_txtr, &rect, renderer, ARRIVAL);
    _dp("Handle there traveler generation");
    Config *mutex = get_cfgMutex();
    pthread_mutex_lock(mutex);
    get_cfg()->trainStopped = 1;
    pthread_mutex_unlock(mutex);
    sleep(4);
    pthread_mutex_lock(mutex);
    get_cfg()->trainStopped = 0;
    pthread_mutex_unlock(mutex);
    size = t->direction == LEFT ? k : TRAIN_LEFT_START_CELL - k;
    animate(size, j, sign, t->direction, lead, body_1, b_txtr, &rect, renderer, DEPARTURE);
    go_beyondScreenLimits(t->direction, body_1, b_txtr, &rect, renderer);
}
/**
 * \brief animate a train and move from col[j] to col[j - size] (left to right) or from col[j] to col[j + size] (right to left)
 * @param size size of external loop (each iteration is a moving step from col[l - 1] to col[l] while l <= size)
 * @param j initial column index (59 when train goes from left to right and 0 when  train goes from right to left)
 * @param sign signed integer needed when computing previous position
 * @param dir : train direction (left / right)
 * @param lead : train lead texture
 * @param body_1: train body texture
 * @param b_txtr: reset texture (rails)
 * @param rect: texture wrapper
 * @param renderer : pointer to screen renderer
 * */
void animate(int size, int j, signed int sign, enum Train_Direction dir, Sprite *lead, Sprite *body_1, Sprite *b_txtr, SDL_Rect *rect, SDL_Renderer *renderer, enum T_animation animation)
{
    pthread_mutex_t *mutex = get_rdMutex(); // get renderer mutex
    Sprite *to_render = NULL;
    int locked = 0;
    for (int l = 0; l <= size; l++)
    {
        int col = calc_col_idx(j, l, dir);
        // need to start from external loop index + n train cell when departure to redraw rails
        int idx_subLoop = animation == DEPARTURE ? l + N_TRAIN_CELL : l;
        if (animation == DEPARTURE)
        {
            /*
             adjust indexes
            */
            int adjust = dir == LEFT ? -(j - size) : TRAIN_LEFT_START_CELL - size;
            col += adjust;
        }
        for (int m = 0; m <= min(idx_subLoop, N_TRAIN_CELL); m++)
        {
            if (!locked)
            {
                pthread_mutex_lock(mutex);
                locked = 1;
            }
            to_render = m == 0 ? lead : body_1;
            rect->x = calc_pos_x(col + (sign * m));
            SDL_RenderCopy(renderer, to_render->surface, NULL, rect);
        }
        SDL_RenderPresent(renderer);
        pthread_mutex_unlock(mutex);
        locked = 0;
        usleep(FRAME_U_SLEEP * 1000);
        if ((l >= N_TRAIN_CELL && l < size) || (animation == DEPARTURE))
        {
            pthread_mutex_lock(mutex);
            locked = 1;
            SDL_RenderCopy(renderer, b_txtr->surface, NULL, rect);
        }
    }
    pthread_mutex_unlock(mutex);
}

void go_beyondScreenLimits(enum Train_Direction dir, Sprite *body_1, Sprite *b_txtr, SDL_Rect *rect, SDL_Renderer *renderer)
{
    Sprite *to_render = NULL;
    pthread_mutex_t *mutex = get_rdMutex();
    for (int l = 0; l <= N_TRAIN_CELL; l++)
    {
        pthread_mutex_lock(mutex);
        int j = dir == LEFT ? (N_TRAIN_CELL - l) : TRAIN_LEFT_START_CELL - (N_TRAIN_CELL - l);
        rect->x = calc_pos_x(j);
        to_render = b_txtr;
        SDL_RenderCopy(renderer, to_render->surface, NULL, rect);
        if (l == 0)
        {
            rect->x = calc_pos_x(dir == LEFT ? 0 : 59);
            to_render = body_1;
            SDL_RenderCopy(renderer, to_render->surface, NULL, rect);
        }
        SDL_RenderPresent(renderer);
        pthread_mutex_unlock(mutex);
        usleep(FRAME_U_SLEEP * 1000);
    }
}

void draw_psgnr(Passenger *psngr, Sprite *sprites, SDL_Renderer *renderer)
{

    Sprite *sprite_psngr = calc_surface(sprites, psngr->idRes);
    SDL_Rect rect;
    rect.x = psngr->pos->i;
    rect.y = psngr->pos->j;
    rect.w = CELL_W;
    rect.h = CELL_H;
    pthread_mutex_t *mutex = get_rdMutex();
    pthread_mutex_lock(mutex);
    SDL_RenderCopy(renderer, sprite_psngr->surface, NULL, &rect);
    if (psngr->prevPos != NULL && is_free(psngr->prevPos))
    {
        Sprite *sprite_rst = calc_surface(sprites, 3);
        SDL_Rect rect_rst;
        rect_rst.x = psngr->prevPos->i;
        rect_rst.y = psngr->prevPos->j;
        rect_rst.h = CELL_H;
        rect_rst.w = CELL_W;
        SDL_RenderCopy(renderer, sprite_rst->surface, NULL, &rect_rst);
    }
    pthread_mutex_unlock(mutex);
}
/**
 * \brief expose a method to redraw screen from renderer
 */
void refresh_screen(SDL_Renderer *renderer)
{
    pthread_mutex_t *mutex = get_rdMutex();
    pthread_mutex_lock(mutex);
    SDL_RenderPresent(renderer);
    pthread_mutex_unlock(mutex);
}

void take_train(Passenger *p, Sprite *sprites, SDL_Renderer *renderer)
{
    Sprite *sprite_rst = calc_surface(sprites, 3);
    SDL_Rect rect_rst;
    rect_rst.x = p->pos->i;
    rect_rst.y = p->pos->j;
    rect_rst.h = CELL_H;
    rect_rst.w = CELL_W;
    SDL_RenderCopy(renderer, sprite_rst->surface, NULL, &rect_rst);
}