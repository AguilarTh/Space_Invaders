#include "arq_jogo_funcoes_base.h"
#include "arq_game.h"
#include "arq_config.h"
#include "arq_colisoes.h"
#include <stdio.h>

// EVENTOS MOUSE/TECLADO:

void processa_eventos_jogo(ALLEGRO_EVENT ev, Game *p_game){
   
    // EVENTO = tecla pressionada ( DOWN ) / soltada ( UP )

    if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        
        printf("\ncodigo tecla: %d", ev.keyboard.keycode);
        switch(ev.keyboard.keycode){  

            case ALLEGRO_KEY_A:
            case ALLEGRO_KEY_LEFT: 
                p_game->nave.esq = 1;
                break;   // quando quero colocar 2 teclas para a msm ação fzr 2 case diferente
    
            case ALLEGRO_KEY_D:
            case ALLEGRO_KEY_RIGHT:
                p_game->nave.dir = 1;
                break;
            
            case ALLEGRO_KEY_SPACE:
                for(int i=0; i<MAX_SHOTS; i++){
                    if(!p_game->shots[i].active){
                        p_game->shots[i].active = true;
                        p_game->shots[i].x = p_game->nave.x - SHOT_W /2;
                        p_game->shots[i].y = SCREEN_H - FLOOR_H/2 - NAVE_H;
                        break; // atirar apenas 1 vez 
                    }
                }
                break;

            case ALLEGRO_KEY_ESCAPE:
               p_game->estado_atual = MENU;
               break;
        }
    }

    if(ev.type == ALLEGRO_EVENT_KEY_UP) {
        switch(ev.keyboard.keycode){  

            case ALLEGRO_KEY_A:
            case ALLEGRO_KEY_LEFT:
                p_game->nave.esq = 0;
                break;   
            
            case ALLEGRO_KEY_D:
            case ALLEGRO_KEY_RIGHT:
                p_game->nave.dir = 0;
                break;
        }
    }

    /* EVENTO = clique de mouse
    else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        printf("\nmouse clicado em: %d, %d", ev.mouse.x, ev.mouse.y);
    }  */
}

// LOGICA DO GAME: Colisões, Updates...

void atualiza_logica_jogo(Game *p_game){
    
    update_nave(p_game);  // !!!!! enderer direito pq nao usar o & !!!!!!
    update_enemy(p_game); // Nao usamos o FOR aq pois ele agora ja está presente dentre da função
    // Main + limpo ( tipo um sumarios ) e ajuda na centralizacao de logica, inimigos movem como um bloco
    update_shot(p_game);
    
    try_enemy_shot(p_game);
    update_enemy_shot(p_game);

    // Verificações de Colisao

    if(colisao_enemy_solo(p_game)){ // Detecção de Colisão 
        p_game->estado_atual = MENU;
    }

    if(contar_inimigos_vivos(p_game) == 0){
        p_game->estado_atual = MENU;
    }

    colisao_shot_enemy(p_game);
    colisao_enemy_shot_nave(p_game);

    if(p_game->nave.life <=0){
        p_game->estado_atual = MENU;
    }		

    if(al_get_timer_count(p_game->timer)%(int)FPS == 0){ // PASSOU 1 SEC 
		printf("\n%d segundos se passaram...", (int)(al_get_timer_count(p_game->timer)/FPS));
	}
}

// DESENHO DAS ENTIDADES:

void desenha_cena_jogo(const Game *p_game){
    
    draw_scenario();
    draw_nave(p_game);
    draw_enemy(p_game);
    draw_object(p_game);

    draw_score(p_game);
    draw_high_score(p_game);
    draw_shot(p_game);
    draw_enemy_shot(p_game);

    al_flip_display();
}

// FUNÇÕES DE DESENHO AVULSO: ( Talvez fazer um arquivo separado depois )

void draw_scenario(){

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_filled_rectangle(0, SCREEN_H - FLOOR_H, 
		                     SCREEN_W, SCREEN_H, 
							 al_map_rgb(0, 245, 0));
}

void draw_score(const Game *p_game){
	
	al_draw_textf(p_game->font, al_map_rgb(255, 255, 255), 10, 10, ALLEGRO_ALIGN_LEFT, "Score: %d", p_game->score);
}

void draw_high_score(const Game *p_game){

	al_draw_textf(p_game->font, al_map_rgb(255, 255, 255), SCREEN_W - 10, 10, ALLEGRO_ALIGN_RIGHT, "Recorde: %d", p_game->high_score);
}