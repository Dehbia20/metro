#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "core/structure.h"
#include "core/constants.h"
#include "core/simulator.h"
#include "core/matrix.h"

#include "ui/gui.h"

void doInit(Config *cfg);

int main(int argc, char **argv)
{
    Config *cfg = (struct Config *)malloc(sizeof(struct Config));
    time_t *t;
    srand(time(t));

    SDL_Window *screen = NULL, *menu = NULL;
    SDL_Renderer *renderer;
    doInit(cfg);

    show_screen(&screen, &renderer);
    start(cfg, &screen, renderer);
    quit(cfg, screen, menu);
    return 0;
}

void doInit(Config *cfg)
{
    int i = SDL_Init(SDL_INIT_VIDEO);
    cfg->minuteAsSecond = MINUTE_AS_SEC;          // 1 min (in game) = 5 s
    cfg->mode = ONLY_TRAIN;                       // start in mode only train
    cfg->generationPauseTime = TV_GEN_PAUSE_TIME; // a passenger is generated initially each 50 ms
    cfg->trace = NONE;                            // disable trace at starting
    cfg->trainStopped = 0;
}
