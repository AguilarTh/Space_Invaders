#ifndef ARQ_MENU_H
#define ARQ_MENU_H

typedef struct Game Game;

#include "arq_config.h"
#include "arq_nave.h"
#include "arq_enemy.h"
#include "arq_enemy_shot.h"
#include "arq_shot.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

void draw_menu(const Game *p_game);
void process_menu_events(ALLEGRO_EVENT ev, Game *p_game);
void reset_game(Game *p_game);

#endif 