#ifndef Structure
#define Structure

#include "constants.h"
#include <SDL.h>

typedef struct Config
{
    int minuteAsSecond;
    int generationPauseTime;
    int trainStopped;
    enum Mode mode;
    enum Trace trace;
} Config;

typedef struct Sprite
{
    struct SDL_Texture *surface;
    char *key;
    struct Sprite *next;
} Sprite;

typedef struct Train
{
    char *id;
    int remainingTime;
    int direction;
} Train;

typedef struct Node
{
    void *data;
    struct Node *next;
} Node;

typedef struct Bg_data
{
    struct Node **train_q;
    enum Train_Direction dir;
} Bg_data;

typedef struct Position
{
    int i;
    int j;
} Position;

typedef struct Passenger
{
    Position *prevPos;
    Position *pos;
    Position *destPos;
    enum Train_Direction dir;
    int idRes;
    enum DestStatus destStatus;
} Passenger;
#endif