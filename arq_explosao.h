#ifndef ARQ_EXPLOSAO_H
#define ARQ_EXPLOSAO_H

#include <allegro5/allegro.h>
#include "arq_config.h"
#define MAX_FRAMES_POR_ANIMAÇÃO 10

typedef struct Game Game;

typedef struct{

    float sx, sy; // Pos SUP/ESQ
    float sw, sh; // Larg/Alt
} AnimationFrame;

typedef struct{

    bool active;
    float x,y;
    ALLEGRO_BITMAP *sprite;

    // ---- ANIMACAO ----

    int frame_atual;
    int total_frames;;
    float frame_time;
    float time_count;
    AnimationFrame frames[MAX_FRAMES_POR_ANIMAÇÃO];
} Explosao;

void init_explosoes(Game *p_game);
void ativar_explosao(Game *p_game, float x, float y);
void update_explosoes(Game *p_game);
void draw_explosoes(const Game *p_game);

#endif