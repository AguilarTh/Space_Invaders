#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <time.h>

#include "arq_game.h"
#include "arq_config.h"
#include "arq_nave.h"
#include "arq_enemy.h"
#include "arq_shot.h"
#include "arq_colisoes.h"
#include "arq_enemy_shot.h"
#include "arq_highscore.h"
#include "arq_object.h"
#include "arq_jogo_funcoes_base.h"
#include "arq_menu.h"
#include "arq_display.h"
#include "arq_explosao.h"
#include "arq_powerup.h"
#include "arq_pause.h"
#include "arq_load.h"

int main(){

	srand(time(NULL));
	Game game;

    /*ALLEGRO_DISPLAY *display = NULL;   // STRUCT -> Tela
    ALLEGRO_EVENT_QUEUE *event_queue = NULL; // STRUCT -> Fila de Eventos
    ALLEGRO_TIMER *timer = NULL; // STRUCT -> Timer do jogo */

    // -------- inicializações: ---------

    if(!al_init()) {  
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	// addons
	if(!al_init_primitives_addon()){
		fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }	

	// imagem
	 if(!al_init_image_addon()) {
        fprintf(stderr, "Falha ao inicializar o addon de imagem!\n");
        return -1;
    }
	
	// fonte/arq tff
	al_init_font_addon();

	if(!al_init_ttf_addon()) {
		fprintf(stderr, "failed to load tff font module!\n");
		return -1;
	}
	
    // teclado/mouse
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}
	
	if(!al_install_mouse()) {
		fprintf(stderr, "failed to initialize mouse!\n");
		return -1;
	}

    if (!init_display(&game)) { 
    	return -1;
	}

	// audio
	if (!al_install_audio()) {
        fprintf(stderr, "failed to initialize audio!\n");
        return -1;
    }

	if (!al_init_acodec_addon()) {
        fprintf(stderr, "Falha ao inicializar o addon de codecs de áudio!\n");
        return -1;
    }

	if (!al_reserve_samples(10)) {
        fprintf(stderr, "Falha ao reservar samples de áudio!\n");
        return -1;
    }

    game.timer = al_create_timer(1.0 / FPS);
    if(!game.timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	// ---------------------------

	// ---- ARQUIVOS EXTERNOS --------

	loads(&game);
    // FILA DE EVENTOS:

	game.event_queue = al_create_event_queue();
	if(!game.event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(game.display);
		return -1;
	}

	al_register_event_source(game.event_queue, al_get_display_event_source(game.display)); // TELA
	al_register_event_source(game.event_queue, al_get_timer_event_source(game.timer)); // TEMPO
	al_register_event_source(game.event_queue, al_get_keyboard_event_source()); // TECLA
	al_register_event_source(game.event_queue, al_get_mouse_event_source()); // MOUSE

	int high_score= load_highscore(); // Carregar o Recorde Salvo

	reset_game(&game);
	game.estado_atual = MENU;

    // --------------- loop principal ---------------

	al_start_timer(game.timer); // Inicia o TIMER
    while(game.estado_atual != SAIR){

        ALLEGRO_EVENT ev;
		al_wait_for_event(game.event_queue, &ev); // espera um evento

		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { // Fechar a tale
			game.estado_atual = SAIR;
			break;
		}

		switch (game.estado_atual){

			case MENU:

				gerenciar_musicas(&game);
			    process_menu_events(ev, &game);
				draw_menu(&game);

				if(game.estado_atual == JOGO_ATIVO) {
                    reset_game(&game);
                }

    			al_set_audio_stream_gain(game.audio.musica_menu, 0.3); // Volume da musica = 70%
				break;
			
			case JOGO_ATIVO:
			    processa_eventos_jogo(ev, &game);

		        if(ev.type == ALLEGRO_EVENT_TIMER) { // temporizador / t -> t+1
					
					gerenciar_musicas(&game);
					atualiza_logica_jogo(&game);
			        desenha_cena_jogo(&game);
				}	
				break;

			case PAUSE:
				processa_eventos_pause(ev, &game);
				desenha_cena_jogo(&game);	
				
				if (game.estado_atual == PAUSE){
                	draw_pause_overlay(&game);
           		}
			break;

			default:
				break;
		}
    }

	// Verificação do HighScore

	if (game.score > high_score){
		printf("NOVO RECORDE: %d\n", game.score);
		save_highscore(game.score);
	}

    // ROTINAS DE DESTRUIÇÃO -> boa pratica

	destroys(&game);
    al_destroy_timer(game.timer);
	destroy_display(&game);
	al_destroy_event_queue(game.event_queue);

    return 0;
}