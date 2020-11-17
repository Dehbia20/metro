#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <unistd.h>
#include "../core/constants.h"
#include "../core/structure.h"
#include "../core/sprite_map.h"
#include "helper.h"
#include "../core/debug.h"

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
    push(sprites, "train_l", IMG_LoadTexture(renderer, "./assets/train_lead_l.png"));
    push(sprites, "train_r", IMG_LoadTexture(renderer, "./assets/train_lead_r.png"));
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
        k = 20; // stop at column 20
    }
    else
    {
        i = 8;  // row 8
        j = 0;  // start at begining
        k = 39; // stops at column 39
    }

    SDL_Rect rect, b_rect;

    rect.w = 50;
    rect.h = CELL_W;
    rect.y = calc_pos_y(i);

    b_rect.w = CELL_W;
    b_rect.h = CELL_H;
    b_rect.y = calc_pos_y(i);

    int size = t->direction == LEFT ? j - k : k - j;
    signed int to_add = t->direction == LEFT ? 1 : -1;
    Sprite *to_render = calc_surface(sprites, t->direction == LEFT ? 6 : 7);
    Sprite *b_txtr = calc_surface(sprites, 2); // rail txtr

    printf("\nsize %d, to_add %d\n", size, to_add);
    for (int l = 0; l <= size; l++)
    {
        int col = calc_col_idx(j, l, t->direction);
        if (l != 0)
        {
            b_rect.x = calc_pos_x(col + to_add);
            printf("\nreset col : %d", col + to_add);
            SDL_RenderCopy(renderer, b_txtr->surface, NULL, &b_rect);
        }
        rect.x = calc_pos_x(col);
        SDL_RenderCopy(renderer, to_render->surface, NULL, &rect);
        SDL_RenderPresent(renderer);
        usleep(FRAME_U_SLEEP * 1000);
    }
}