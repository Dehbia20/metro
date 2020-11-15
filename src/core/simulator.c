
#include "structure.h"
#include "constants.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "matrix.h"
#include "map.h"
#include "../ui/gui.h"
void start(Config *cfg, SDL_Window **window, SDL_Renderer *renderer)
{
    int runningFlag = CONTINUE;
    int base_matrix[20][60];
    Sprite *sprites = NULL;
    read_matrix(20, base_matrix, "./assets/map");
    load_sprites(&sprites, renderer);
    draw_map(sprites, window, base_matrix, renderer);
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
}

void quit(Config *cfg, SDL_Surface *screen, SDL_Surface *menu)
{
    free(cfg);
    SDL_free(screen);
    SDL_free(menu);
}