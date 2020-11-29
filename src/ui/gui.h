#include <SDL.h>
#include "../core/structure.h"

void show_screen(SDL_Window **screen, SDL_Renderer **renderer);
void load_sprites(Sprite **sprites, SDL_Renderer *renderer);
void draw_map(Sprite **sprites, SDL_Window *window, int matrix[20][60], SDL_Renderer *renderer);
void trigger_train(Train *t, Sprite *sprites, SDL_Renderer *renderer);
void draw_psgnr(Passenger *psngr, Sprite *sprites, SDL_Renderer *renderer);
void refresh_screen(SDL_Renderer *renderer);
void take_train(Passenger *p, Sprite *sprites, SDL_Renderer *renderer);