
#include "structure.h"
#include "constants.h"
#include <stdlib.h>
#include <SDL.h>
void start(Config *cfg)
{
    int runningFlag = CONTINUE;
    do
    {

    } while (runningFlag);
}

void quit(Config *cfg, SDL_Surface *screen, SDL_Surface *menu)
{
    free(cfg);
    SDL_free(screen);
    SDL_free(menu);
}