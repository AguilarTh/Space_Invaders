#include "arq_explosao.h"
#include "arq_game.h"
#include "arq_config.h"

void init_explosoes(Game *p_game){
    for (int i = 0; i<MAX_EXPLOSOES; i++) {

        Explosao *exp = &p_game->explosoes[i];

        exp->active = false;
        exp->sprite = p_game->sprites.explosao;
        exp->frame_time = 0.30f; // Duração de cada frame (mais baixo = mais rápido)
        exp->total_frames = 7; 

        // Detalhes da Animação
        
        exp->frames[0] = (AnimationFrame){ .sx=12, .sy=13, .sw=22, .sh=19};
        exp->frames[1] = (AnimationFrame){ .sx=55, .sy=7, .sw=35, .sh=29};
        exp->frames[2] = (AnimationFrame){ .sx=100, .sy=7, .sw=40, .sh=32};
        exp->frames[3] = (AnimationFrame){ .sx=148, .sy=7, .sw=39, .sh=32};
        exp->frames[4] = (AnimationFrame){ .sx=196, .sy=6, .sw=39, .sh=33};
        exp->frames[5] = (AnimationFrame){ .sx=244, .sy=6, .sw=39, .sh=33};
        exp->frames[6] = (AnimationFrame){ .sx=294, .sy=7, .sw=34, .sh=33};

        // -----------------------------------------------------------------
    }
}

void ativar_explosao(Game *p_game, float x, float y){
   
    // Primeira Explosao Inativa
    for (int i = 0; i < MAX_EXPLOSOES; i++) {
        if (!p_game->explosoes[i].active) {
            p_game->explosoes[i].active = true;
            
            // Posição do inimigo morto
            p_game->explosoes[i].x = x; 
            p_game->explosoes[i].y = y;
            p_game->explosoes[i].frame_atual = 0; // start frame 0
            p_game->explosoes[i].frame_time = 0;
            break; // Ativa só uma e sai do loop
        }
    }
}

void update_explosoes(Game *p_game){
    for (int i = 0; i<MAX_EXPLOSOES; i++) {
        if (p_game->explosoes[i].active) {
            p_game->explosoes[i].time_count += 1.0 / FPS; // Adiciona o tempo de um frame

            if (p_game->explosoes[i].time_count >= p_game->explosoes[i].frame_time) {
                p_game->explosoes[i].time_count = 0;
                p_game->explosoes[i].frame_atual++; // Avança para o próximo frame

                if (p_game->explosoes[i].frame_atual >= p_game->explosoes[i].total_frames) {
                    p_game->explosoes[i].active = false; // Animação terminou
                }
            }
        }
    }
}

void draw_explosoes(const Game *p_game){
    for (int i = 0; i<MAX_EXPLOSOES; i++) {
        if (p_game->explosoes[i].active) {

            const Explosao *exp = &p_game->explosoes[i];
            AnimationFrame frame_info = exp->frames[exp->frame_atual];

            // Centraliza o desenho da explosão
            float dx = exp->x - (frame_info.sw / 2.0);
            float dy = exp->y - (frame_info.sh / 2.0);

            al_draw_bitmap_region(exp->sprite,
                                  frame_info.sx, frame_info.sy, // Pega o X,Y do frame
                                  frame_info.sw, frame_info.sh, // Pega a Largura/Altura do frame
                                  dx, dy,
                                  0);
        }
    }
}