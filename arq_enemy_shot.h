#ifndef ARQ_ENEMY_SHOT_H
#define ARQ_ENEMY_SHOT_H

#include <allegro5/allegro.h>

typedef Game Game;

typedef struct{
    
    bool active;
    float x,y;
    float y_vel;
    ALLEGRO_COLOR cor;
} enemyshot;

void initEnemyShot(Game *p_game);
void try_enemy_shot(Game *p_game);
void draw_enemy_shot(Game *p_game);
void update_enemy_shot(Game *p_game);

#endif