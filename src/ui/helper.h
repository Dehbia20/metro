#include <SDL.h>
Sprite *calc_surface(Sprite *sprites, int id);
int calc_pos_y(int i);
int calc_pos_x(int j);
int calc_col_idx(int j, int l, enum Train_Direction dir);
int min(int n, int m);