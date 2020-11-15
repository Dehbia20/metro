#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "../core/constants.h"
#include "../core/structure.h"
#include "../core/map.h"
#include "helper.h"

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
    printf("\n sprites size : %d", size(*sprites));
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
                SDL_Rect rect;
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