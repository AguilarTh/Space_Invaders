#ifndef ARQ_POWERUP_H
#define ARQ_POWERUP_H

#include <allegro5/allegro.h>
#include "arq_config.h"
#include "arq_enemy.h"

typedef struct Game Game;

typedef struct {

    bool active;
    float x, y;
    float y_vel;
    BuffTypes tipo; // Para saber qual buff este item concede
    ALLEGRO_BITMAP *sprite; 
} PowerUpDrop;

void init_powerups(Game *p_game);
void tentar_dropar_buff(Game *p_game, enemy *inimigo_morto);
void update_powerups(Game *p_game);
void draw_powerups(Game *p_game);
void aplicar_buff(Game *p_game, BuffTypes tipo);
void shield_buff(Game *p_game);

#endif