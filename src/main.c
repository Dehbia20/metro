#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "core/structure.h"
#include "core/constants.h"
#include "core/simulator.h"
#include "core/matrix.h"

#include "ui/gui.h"

void doInit(Config *cfg);

int main(int argc, char **argv)
{
    Config *cfg = (struct Config *)malloc(sizeof(struct Config));
    doInit(cfg);
    SDL_Window *screen = NULL, *menu = NULL;
    SDL_Renderer *renderer;
    show_screen(&screen, &renderer);
    start(cfg, &screen, renderer);
    quit(cfg, screen, menu);
    return 0;
}

void doInit(Config *cfg)
{
    int i = SDL_Init(SDL_INIT_VIDEO);
    if (i < 0)
        printf("caca");
    cfg->minuteAsSecond = MINUTE;
    cfg->mode = onlyTrain;
}
