#ifndef ARQ_COLISOES_H
#define ARQ_COLISOES_H

#include <stdbool.h>

typedef struct Game Game;

int colisao_enemy_solo(Game *p_game);
void colisao_shot_enemy(Game *p_game);
void colisao_enemy_shot_nave(Game *p_game);
void colisao_shot_object(Game *p_game);
void colisao_enemy_shot_object(Game *p_game);
void colisao_enemy_object(Game *p_game);
void colisao_nave_powerup(Game *p_game);
bool check_collision_retangulo(float x1, float y1, float w1, float h1,
                                float x2, float y2, float w2, float h2);
#endif