#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "core/structure.h"
#include "core/constants.h"
#include "core/simulator.h"
#include "core/matrix.h"

#include "ui/gui.h"

void doInit(Config *cfg);

void read()
{
    int matrix[20][60];
    printf("Salut ! ");
    int c = read_matrix(20, matrix, "./assets/map");
    printf("code retour %1d", c);
}

int main(int argc, char **argv)
{
    Config *cfg = (struct Config *)malloc(sizeof(struct Config));
    doInit(cfg);
    read();
    SDL_Surface *screen = NULL, *menu = NULL;
    show_screen(screen);
    start(cfg);
    quit(cfg, screen, menu);
    return 0;
}

void doInit(Config *cfg)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    cfg->minuteAsSecond = MINUTE;
    cfg->mode = onlyTrain;
}
