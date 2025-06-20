#ifndef ARQ_COLISOES_H
#define ARQ_COLISOES_H

#include "arq_enemy.h"
#include "arq_shot.h"
#include "arq_enemy_shot.h"
#include "arq_nave.h"

int colisao_enemy_solo(Game *p_game);
void colisao_shot_enemy(Game *p_game);
void colisao_enemy_shot_nave(Game *p_game);
bool check_collision_retangulo(float x1, float y1, float w1, float h1,
                                float x2, float y2, float w2, float h2);
#endif