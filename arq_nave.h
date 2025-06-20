#ifndef ARQ_NAVE_H
#define ARQ_NAVE_H

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>

typedef Game Game;

typedef struct{

	int life;
	float x;
	float vel;
	int dir, esq;  // saber se ela esta movimentando para algum lado
	ALLEGRO_BITMAP *sprite;
} nave;

void initNave(Game *p_game);
void draw_nave(Game *p_game);
void update_nave(Game *p_game);

#endif 