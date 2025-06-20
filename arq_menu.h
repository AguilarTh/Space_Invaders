#ifndef ARQ_MENU_H
#define ARQ_MENU_H

#include "arq_config.h"
#include "arq_nave.h"
#include "arq_enemy.h"
#include "arq_enemy_shot.h"
#include "arq_shot.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

void draw_menu(ALLEGRO_FONT *font, ALLEGRO_BITMAP *background);
void process_menu_events(ALLEGRO_EVENT ev, GameStates *estado_atual);
void reset_game(Game *p_game);

#endif 