#ifndef ARQ_DISPLAY_H
#define ARQ_DISPLAY_H

#include <allegro5/allegro.h>

ALLEGRO_DISPLAY* init_display();  // CRIACAO DA TELA
void destroy_display(ALLEGRO_DISPLAY *display); // DESTROICAO DA TELA
void transform_mouse_coords(int *mouse_x, int *mouse_y); 

#endif 