#include "structure.h"

Sprite *find_by_key(Sprite *node, char *searched);
void push(Sprite **node, char *key, SDL_Surface *surface);
void free_sprites(Sprite *node);
int sprite_size(Sprite *node);