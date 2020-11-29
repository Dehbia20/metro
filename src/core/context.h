#define HAVE_STRUCT_TIMESPEC

#include <SDL.h>
#include <pthread.h>
#include "structure.h"
Node **get_tq1();
void set_tq1(Node **tq);
Node **get_tq2();
void set_tq2(Node **tq);
SDL_Renderer *get_rd();
void set_rd(SDL_Renderer *rd);
void set_sp(Sprite *sp);
Sprite *get_sp();
void set_cfg(Config *c);
Config *get_cfg();
Node **get_psngr();
void set_psngr(Node **psgnr);
pthread_mutex_t *get_rdMutex();
void set_rdMutex(pthread_mutex_t *mutex);
pthread_mutex_t *get_cfgMutex();
void set_cfgMutex(pthread_mutex_t *mutex);
void set_fp(Node **fp);
Node **get_fp();
void set_fpb(Node **fpb);
Node **get_fpb();