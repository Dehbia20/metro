#include "../core/structure.h"
#include "../core/map.h"
#include "../core/constants.h"

char *convert(int id)
{
    switch (id)
    {
    case 1:
        return "tile";
    case 2:
        return "rail";
    case 3:
        return "floor";
    case 4:
        return "bench";
    case 5:
        return "ground";
    default:
        return NULL;
        ;
    }
}

Sprite *calc_surface(Sprite *sprites, int id)
{
    char *key = convert(id);
    if (key == NULL)
    {
        return NULL;
    }
    Sprite *s = find_by_key(sprites, key);
    if (s != NULL)
    {
        printf("\n%s, %p", s->key, s->surface);
    }
    return s;
}

int calc_pos_y(int i)
{
    return CELL_H * i;
}

int calc_pos_x(int j)
{
    return CELL_W * j;
}