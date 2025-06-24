#ifndef ARQ_PAUSE_H
#define ARQ_PAUSE_H     

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

typedef struct Game Game;

void processa_eventos_pause(ALLEGRO_EVENT ev, Game *p_game);
void draw_pause_overlay(const Game *p_game);

#endif 