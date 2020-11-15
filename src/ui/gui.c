#include <SDL.h>
#include "../core/constants.h"

void show_screen(SDL_Surface *screen)
{
    screen = SDL_CreateWindow("Underground subway simulation !",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WINDOW_W,
                              WINDOW_H,
                              SDL_WINDOW_SHOWN);
    return;
}