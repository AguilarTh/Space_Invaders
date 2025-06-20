#include "arq_menu.h"
#include "arq_game.h"

#include "arq_display.h"

void draw_menu(ALLEGRO_FONT *font, ALLEGRO_BITMAP *background){
    // FUNDO
    al_clear_to_color(al_map_rgb(20, 20, 40));  // Essa colori com uma cor de fundo
    //al_draw_bitmap(background, 0, 0, 0); // Essa coloca uma imagem de fundo

    // TITULO
    al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 4, ALLEGRO_ALIGN_CENTER, "Space Defender");

    // OPÇÃO
    al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "NOVO JOGO");
    al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2 + 40, ALLEGRO_ALIGN_CENTER, "AJUDA");
    al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2 + 80, ALLEGRO_ALIGN_CENTER, "CONFIGURACAO");
    al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2 + 120, ALLEGRO_ALIGN_CENTER, "SAIR");

    al_flip_display();
}

// Funcao Recebe EVENTO + PONT P/ O ESTADO DO JOGO (permite mexer nele)

void process_menu_events(ALLEGRO_EVENT ev, GameStates *estado_atual) {
    if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        
        int mouse_x = ev.mouse.x;
        int mouse_y = ev.mouse.y;

        transform_mouse_coords(&mouse_x, &mouse_y); // Tradução das coordenadas, seja la oq isso quer dizer

        // ---- AREAS CLICAVEIS DOS BOTOES ----

        // A: NOVO JOGO
        if (mouse_x > SCREEN_W / 2 - 100 && mouse_x < SCREEN_W / 2 + 100 &&
            mouse_y > SCREEN_H / 2 - 15 && mouse_y < SCREEN_H / 2 + 15) {
            printf("Botao NOVO JOGO clicado!\n");
            *estado_atual = JOGO_ATIVO; 
        }
        
        // A: AJUDA
        if (mouse_x > SCREEN_W / 2 - 100 && mouse_x < SCREEN_W / 2 + 100 &&
            mouse_y > SCREEN_H / 2 + 25 && mouse_y < SCREEN_H / 2 + 55) {
            printf("Botao AJUDA clicado!\n");
            // *estado_atual = AJUDA; // (Implementaremos no futuro)
        }

        // A: CONFIG
        if (mouse_x > SCREEN_W / 2 - 100 && mouse_x < SCREEN_W / 2 + 100 &&
            mouse_y > SCREEN_H / 2 + 65 && mouse_y < SCREEN_H / 2 + 95) {
            printf("Botao CONFIGURACAO clicado!\n");
            // *estado_atual = CONFIG; // (Implementaremos no futuro)
        }

        // A: SAIR
        if (mouse_x > SCREEN_W / 2 - 100 && mouse_x < SCREEN_W / 2 + 100 &&
            mouse_y > SCREEN_H / 2 + 105 && mouse_y < SCREEN_H / 2 + 135) {
            printf("Botao SAIR clicado!\n");
            *estado_atual = SAIR;
        }
    }
}

void reset_game(Game *p_game){
    printf("Resetando o estado do jogo...\n");
    initNave(&p_game->nave, p_game->sprites.nave);
    initEnemy(p_game->enemies);
    initShot(p_game->shots);
    initEnemyShot(p_game->enemies_shots);
    p_game->score = 0;
}