#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <unistd.h>
#include "../core/constants.h"
#include "../core/structure.h"
#include "../core/sprite_map.h"
#include "helper.h"
#include "../core/debug.h"
void animate(int size, int j, signed int sign, enum Train_Direction dir, Sprite *lead, Sprite *body_1, Sprite *b_txtr, SDL_Rect *rect, SDL_Renderer *renderer, enum T_animation animation);
void go_beyondScreenLimits(enum Train_Direction dir, Sprite *body_1, Sprite *b_txtr, SDL_Rect *rect, SDL_Renderer *renderer);
void show_screen(SDL_Surface **screen, SDL_Renderer **renderer)
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
}

void draw_map(Sprite *sprites, SDL_Window **window, int matrix[20][60], SDL_Renderer *renderer)
{
    if (*window != NULL && renderer != NULL)
    {
        printf("ecran bien present");
    }
    for (int i = 0; i < 20; ++i)
    {
        for (int j = 0; j < 60; ++j)
        {
            Sprite *sprite = calc_surface(sprites, matrix[i][j]);
            if (sprite != NULL && sprite->surface != NULL)
            {
                int w, h;
                SDL_QueryTexture(sprite->surface, NULL, NULL, &w, &h); // get the width and height of the texture
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
        i = 11; // row 11
        j = 59; // last case (first case from the left)
        k = 26; // stop at column 26
    }
    else
    {
        i = 8;  // row 8
        j = 0;  // start at begining
        k = 33; // stops at column 33
    }

    SDL_Rect rect;
    Sprite *lead, *body_1;

    rect.w = CELL_W;
    rect.h = CELL_H;
    rect.y = calc_pos_y(i);

    int size = t->direction == LEFT ? j - k : k - j;
    signed int sign = t->direction == LEFT ? 1 : -1;

    Sprite *to_render = NULL;
    Sprite *b_txtr = calc_surface(sprites, 2); // rail txtr
    lead = t->direction == LEFT ? calc_surface(sprites, 6) : calc_surface(sprites, 8);
    body_1 = calc_surface(sprites, 7);
    animate(size, j, sign, t->direction, lead, body_1, b_txtr, &rect, renderer, ARRIVAL);
    _dp("Handle there traveler generation");
    sleep(2);
    size = t->direction == LEFT ? k : 59 - k;
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
    Sprite *to_render = NULL;
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
            int adjust = dir == LEFT ? -(j - size) : 59 - size;
            col += adjust;
        }

        for (int m = 0; m <= min(idx_subLoop, N_TRAIN_CELL); m++)
        {
            to_render = m == 0 ? lead : body_1;
            rect->x = calc_pos_x(col + (sign * m));
            SDL_RenderCopy(renderer, to_render->surface, NULL, rect);
        }
        SDL_RenderPresent(renderer);
        usleep(FRAME_U_SLEEP * 1000);
        if ((l >= N_TRAIN_CELL && l < size) || (animation == DEPARTURE))
        {
            SDL_RenderCopy(renderer, b_txtr->surface, NULL, rect);
        }
    }
}

void go_beyondScreenLimits(enum Train_Direction dir, Sprite *body_1, Sprite *b_txtr, SDL_Rect *rect, SDL_Renderer *renderer)
{
    Sprite *to_render = NULL;

    for (int l = 0; l <= N_TRAIN_CELL; l++)
    {
        int j = dir == LEFT ? (N_TRAIN_CELL - l) : 59 - (N_TRAIN_CELL - l);
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
        usleep(FRAME_U_SLEEP * 1000);
    }
}