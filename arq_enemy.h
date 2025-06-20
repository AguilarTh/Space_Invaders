#ifndef ARQ_ENEMY_H
#define ARQ_ENEMY_H

#include <allegro5/allegro.h>

typedef struct Game Game;  // entender melhor sobre essa declaracao antecipada -> DECLARACAO VS DEFINICAO

typedef struct{

	bool active;
	int type;
	int score;
	int life;
	float x, y;
	float x_vel, y_vel;
	ALLEGRO_COLOR cor;
} enemy;

void initEnemy(Game *p_game);
void draw_enemy(const Game *p_game);
void update_enemy(Game *p_game);
int contar_inimigos_vivos(Game *p_game);
void enemy_dmg_visuals_update(enemy *p_enemy);

#endif