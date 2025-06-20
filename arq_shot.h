#ifndef ARQ_SHOT_H
#define ARQ_SHOT_H

#include <allegro5/allegro.h>

typedef struct Game Game;

typedef struct{
	
	bool active;
	float x, y;
	float y_vel;
	ALLEGRO_COLOR cor;
	// int type_shot;
} shot;

void initShot(Game *p_game);
void draw_shot(const Game *p_game);
void update_shot(Game *p_game);

#endif