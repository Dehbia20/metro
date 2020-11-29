#include "../core/structure.h"
#include "../core/sprite_map.h"
#include <stdio.h>
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
    case 6:
        return "t_l1";
    case 7:
        return "t_b";
    case 8:
        return "t_r1";
    case 9:
        return "ghost_1";
    case 10:
        return "ghost_2";
    case 11:
        return "ghost_3";
    case 12:
        return "ghost_4";
    default:
        return NULL;
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

int calc_col_idx(int j, int l, enum Train_Direction dir)
{
    if (dir == LEFT)
    {
        return j - l;
    }
    else
    {
        return j + l;
    }
}

int min(int n, int m)
{
    return n <= m ? n : m;
}