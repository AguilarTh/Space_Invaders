#include "arq_display.h"
#include "arq_config.h"

#include <stdio.h>

static float g_scale; 
static float g_offset_x;
static float g_offset_y;

ALLEGRO_DISPLAY* init_display() {
    
    // DEFINE O MODO DE TELA CHEIA EM JANELA 
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW); 

    // CRIACAO DA TELA COM BASE NA CONFIG DO GAME
    ALLEGRO_DISPLAY *display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display) {
        fprintf(stderr, "Falha ao criar o display!\n");
        return NULL; 
    }

    // --- ESCALA AUTOMATICA ---
    float display_w = al_get_display_width(display);
    float display_h = al_get_display_height(display);

    float scale_w = display_w / SCREEN_W;
    float scale_h = display_h / SCREEN_H;
    g_scale = (scale_w < scale_h) ? scale_w : scale_h;

    g_offset_x = (display_w - (SCREEN_W * g_scale)) / 2;
    g_offset_y = (display_h - (SCREEN_H * g_scale)) / 2;

    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_translate_transform(&transform, g_offset_x, g_offset_y);
    al_scale_transform(&transform, g_scale, g_scale);
    al_use_transform(&transform);
    // --- Fim do Bloco  ---

    return display; 
}

void destroy_display(ALLEGRO_DISPLAY *display) {
    al_destroy_display(display);
}

void transform_mouse_coords(int *mouse_x, int *mouse_y) {
    
    *mouse_x = (*mouse_x - g_offset_x) / g_scale;
    *mouse_y = (*mouse_y - g_offset_y) / g_scale;
}