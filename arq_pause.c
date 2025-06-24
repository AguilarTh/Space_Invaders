#include "arq_pause.h"
#include "arq_game.h"
#include "arq_config.h"

void processa_eventos_pause(ALLEGRO_EVENT ev, Game *p_game){
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch (ev.keyboard.keycode) {

            case ALLEGRO_KEY_P:
                p_game->estado_atual = JOGO_ATIVO;
                break;
        
            case ALLEGRO_KEY_ESCAPE:
                p_game->estado_atual = MENU;
                break;
        }
    }
}

void draw_pause_overlay(const Game *p_game) {
   
    // RETANGULO SEMI_TRANSPARENTE:
    // A função al_map_rgba_f usa valores de 0.0 a 1.0 para a transparência (alpha).
    al_draw_filled_rectangle(0, 0, SCREEN_W, SCREEN_H, al_map_rgba_f(0, 0, 0, 0.5));

    // TEXTOS:
    al_draw_text(p_game->font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2 - 80, ALLEGRO_ALIGN_CENTER, "PAUSADO");
    al_draw_text(p_game->font, al_map_rgb(200, 200, 200), SCREEN_W / 2, SCREEN_H / 2 + 20, ALLEGRO_ALIGN_CENTER, "Pressione 'P' para continuar");
    al_draw_text(p_game->font, al_map_rgb(200, 200, 200), SCREEN_W / 2, SCREEN_H / 2 + 50, ALLEGRO_ALIGN_CENTER, "Pressione 'ESC' para voltar ao Menu");
}
