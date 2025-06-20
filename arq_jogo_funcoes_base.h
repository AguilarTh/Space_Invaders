#ifndef ARQ_JOGO_FUNCOES_BASE_H
#define ARQ_JOGO_FUNCOES_BASE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

typedef struct Game Game;

void processa_eventos_jogo(ALLEGRO_EVENT ev, Game *p_game);
void atualiza_logica_jogo(Game *p_game);
void desenha_cena_jogo(const Game *p_game);

void draw_scenario();
void draw_score(const Game *p_game);
void draw_high_score(const Game *p_game);

#endif 