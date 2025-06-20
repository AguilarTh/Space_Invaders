#ifndef ARQ_DISPLAY_H
#define ARQ_DISPLAY_H

#include <allegro5/allegro.h>

typedef struct Game Game;

bool init_display(Game *p_game);
void destroy_display(Game *p_game);
void transform_mouse_coords(const Game *p_game, int *mouse_x, int *mouse_y);

#endif 