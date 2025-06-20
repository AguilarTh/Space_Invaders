#include "arq_display.h"
#include "arq_game.h"
#include "arq_config.h"

#include <stdio.h>

//static float g_scale; 
//static float g_offset_x;
//static float g_offset_y;

bool init_display(Game *p_game){
    
    // DEFINE O MODO DE TELA CHEIA EM JANELA 
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW); 

    // CRIACAO DA TELA COM BASE NA CONFIG DO GAME
    p_game->display = al_create_display(SCREEN_W, SCREEN_H);
    if (!p_game->display) {
        fprintf(stderr, "Falha ao criar o display!\n");
        return false; 
    }

    // --- ESCALA AUTOMATICA ---
    float display_w = al_get_display_width(p_game->display);
    float display_h = al_get_display_height(p_game->display);

    float scale_w = display_w / SCREEN_W;
    float scale_h = display_h / SCREEN_H;
    p_game->scale = (scale_w < scale_h) ? scale_w : scale_h;
    p_game->offset_x = (display_w - (SCREEN_W * p_game->scale)) / 2;
    p_game->offset_y = (display_h - (SCREEN_H * p_game->scale)) / 2;

    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_translate_transform(&transform, p_game->offset_x, p_game->offset_y);
    al_scale_transform(&transform, p_game->scale, p_game->scale);
    al_use_transform(&transform);
    // --- Fim do Bloco  ---

    return true; 
}

void destroy_display(Game *p_game) {
    al_destroy_display(p_game->display);
}

void transform_mouse_coords(const Game *p_game, int *mouse_x, int *mouse_y) {
    
    *mouse_x = (*mouse_x - p_game->offset_x) / p_game->scale;
    *mouse_y = (*mouse_y - p_game->offset_y) / p_game->scale;
}