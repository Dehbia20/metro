#ifndef Structure
#define Structure

#include "constants.h"
#include <SDL.h>

typedef struct Config
{
    int minuteAsSecond;
    enum Mode mode;
} Config;

typedef struct Sprite
{
    struct SDL_Texture *surface;
    char *key;
    struct Sprite *next;
} Sprite;

#endif