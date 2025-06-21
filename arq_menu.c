#include "arq_menu.h"
#include "arq_game.h"
#include "arq_config.h"
#include "arq_explosao.h"

#include "arq_display.h"

void draw_menu(const Game *p_game){
    // FUNDO
    al_clear_to_color(al_map_rgb(20, 20, 40));  // Essa colori com uma cor de fundo
    //al_draw_bitmap(background, 0, 0, 0); // Essa coloca uma imagem de fundo

    // TITULO
    al_draw_text(p_game->font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 4, ALLEGRO_ALIGN_CENTER, "Space Defender");

    // OPÇÃO
    al_draw_text(p_game->font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "NOVO JOGO");
    al_draw_text(p_game->font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2 + 40, ALLEGRO_ALIGN_CENTER, "AJUDA");
    al_draw_text(p_game->font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2 + 80, ALLEGRO_ALIGN_CENTER, "CONFIGURACAO");
    al_draw_text(p_game->font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2 + 120, ALLEGRO_ALIGN_CENTER, "SAIR");

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
            mouse_y > SCREEN_H / 2 - 15 && mouse_y < SCREEN_H / 2 + 15) {
            printf("Botao NOVO JOGO clicado!\n");
            p_game->estado_atual = JOGO_ATIVO; 
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
            p_game->estado_atual = SAIR;
        }
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

    initEnemy(p_game);

    // AUDIOS DE FUNDO;

    al_set_audio_stream_playmode(p_game->audio.musica_fundo_jogo, ALLEGRO_PLAYMODE_LOOP);
    al_attach_audio_stream_to_mixer(p_game->audio.musica_fundo_jogo, al_get_default_mixer());
    al_set_audio_stream_gain(p_game->audio.musica_fundo_jogo, 0.0); // Volume da musica = 70%

}