#include "arq_menu.h"
#include "arq_game.h"
#include "arq_config.h"
#include "arq_explosao.h"

#include "arq_display.h"

void draw_menu(const Game *p_game){

    al_clear_to_color(al_map_rgb(0, 0, 0)); // LIMPA A TELA

    float bg_w = al_get_bitmap_width(p_game->sprites.background_menu);
    float bg_h = al_get_bitmap_height(p_game->sprites.background_menu);

    al_draw_scaled_bitmap(p_game->sprites.background_menu, 0, 0, bg_w, bg_h, 0, 0, SCREEN_W, SCREEN_H, 0);

    // TITULO
    al_draw_text(p_game->font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 4, ALLEGRO_ALIGN_CENTER, "Space Invaders");

    // OPÇÃO
    al_draw_text(p_game->font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2 + 150, ALLEGRO_ALIGN_CENTER, "NOVO JOGO");
    al_draw_text(p_game->font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2 + 190, ALLEGRO_ALIGN_CENTER, "SAIR");

    al_flip_display();
}

// Funcao Recebe EVENTO + PONT P/ O ESTADO DO JOGO (permite mexer nele)

void process_menu_events(ALLEGRO_EVENT ev, Game *p_game){
    if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        
        int mouse_x = ev.mouse.x;
        int mouse_y = ev.mouse.y;

        // transform_mouse_coords(p_game, &mouse_x, &mouse_y); // Tradução das coordenadas, seja la oq isso quer dizer

        // ---- AREAS CLICAVEIS DOS BOTOES ----

        // A: NOVO JOGO
        if (mouse_x > SCREEN_W / 2 - 100 && mouse_x < SCREEN_W / 2 + 100 &&
            mouse_y > SCREEN_H / 2 + 150 && mouse_y < SCREEN_H / 2 + 180) {
            printf("Botao NOVO JOGO clicado!\n");
            p_game->estado_atual = JOGO_ATIVO; 
        }
        
        // A: SAIR
        if (mouse_x > SCREEN_W / 2 - 100 && mouse_x < SCREEN_W / 2 + 100 &&
            mouse_y > SCREEN_H / 2 + 190 && mouse_y < SCREEN_H / 2 + 210) {
            printf("Botao SAIR clicado!\n");
            p_game->estado_atual = SAIR;
        }

        /* A: CONFIG
        if (mouse_x > SCREEN_W / 2 - 100 && mouse_x < SCREEN_W / 2 + 100 &&
            mouse_y > SCREEN_H / 2 + 65 && mouse_y < SCREEN_H / 2 + 95) {
            printf("Botao CONFIGURACAO clicado!\n");
            // *estado_atual = CONFIG; // (Implementaremos no futuro)
        } */
    }
}

void reset_game(Game *p_game){
    printf("Resetando o estado do jogo...\n");
    initNave(p_game);
    initShot(p_game);
    initObject(p_game);
    initEnemyShot(p_game);
    init_explosoes(p_game);
    init_powerups(p_game);

    p_game->score = 0;
    p_game->round_atual = 1;
    
    p_game->immunity = false;
    p_game->tempo_buff_velocidade_restante = 0;
    p_game->tempo_buff_imunidade_restante = 0;

    initEnemy(p_game);

    // AUDIOS DE FUNDO;
}