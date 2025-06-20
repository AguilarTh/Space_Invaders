#ifndef ARQ_ENEMY_H
#define ARQ_ENEMY_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "arq_config.h"

typedef struct Game Game;  // entender melhor sobre essa declaracao antecipada -> DECLARACAO VS DEFINICAO

typedef struct{

    float sx, sy; // Pos SUP/ESQ
    float sw, sh; // Larg/Alt
} AnimationFrameEnemy; 

typedef struct enemy{

	bool active;
	int type;
	int score;
	int life;
	float x, y;
	float x_vel, y_vel;
	ALLEGRO_BITMAP *sprite;

	int frame_atual;
    int total_frames;;
    float frame_time;
    float time_count;
	AnimationFrameEnemy frames[MAX_FRAMES_POR_ANIMAÇÃO];
} enemy;

void initEnemy(Game *p_game);
void draw_enemy(const Game *p_game);
void update_enemy(Game *p_game);
int contar_inimigos_vivos(Game *p_game);
//void enemy_dmg_visuals_update(enemy *p_enemy);

#endif