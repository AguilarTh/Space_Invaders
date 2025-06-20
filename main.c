#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
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

    game.timer = al_create_timer(1.0 / FPS);
    if(!game.timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	// ---------------------------

	// ---- ARQUIVOS EXTERNOS --------

	// -- FONTE --
    game.font = al_load_ttf_font("font_space.ttf", 35, 0);   
	if(game.font == NULL) {
		fprintf(stderr, "font file does not exist or cannot be accessed!\n");
		return -1;
	} 

	// -- PNG ---
	game.sprites.background_menu = al_load_bitmap("background_menu.png");
	if (!game.sprites.background_menu) {
		fprintf(stderr, "Falha ao carregar a imagem 'background_menu.png'!\n");
		al_destroy_font(game.font);
		al_destroy_display(game.display);
		return -1;
	}

	game.sprites.nave = al_load_bitmap("nave_sprite.png");
	game.sprites.nave_life = al_load_bitmap("hearts.png");
	game.sprites.shot = al_load_bitmap("shot_sprite.png");
	game.sprites.enemy = al_load_bitmap("enemy_sprite.png");
	game.sprites.enemy_shot = al_load_bitmap("enemy_shot_sprite.png");
	game.sprites.background_jogo = al_load_bitmap("background_jogo.png");
	game.sprites.explosao = al_load_bitmap("explosao.png");

	// ------------------------

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

	// VARIAVEIS DO JOGO:
	/*
	nave nave;
	initNave(&nave, nave_sprite);

	enemy enemies[MAX_ENEMIES];
	initEnemy(enemies);

	shot shots[MAX_SHOTS];
	initShot(shots);

	enemyshot enemies_shots[MAX_ENEMIES_SHOTS];
	initEnemyShot(enemies_shots);

	object objects[OBJECTS_NUMB];
	initObject(objects);
	
	int score = 0; 
	
	*/

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
			    process_menu_events(ev, &game);
				draw_menu(&game);

				if(game.estado_atual == JOGO_ATIVO) {
                    reset_game(&game);
                }
				break;
			
			case JOGO_ATIVO:
			    
			    processa_eventos_jogo(ev, &game);

		        if(ev.type == ALLEGRO_EVENT_TIMER) { // temporizador / t -> t+1
					
					atualiza_logica_jogo(&game);
			        desenha_cena_jogo(&game);
				}	
				break;
			
			case AJUDA:
			    // loga
				break;
			
			case CONFIG:
			    // loga
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

	al_destroy_bitmap(game.sprites.background_jogo);
	al_destroy_bitmap(game.sprites.nave);
	al_destroy_bitmap(game.sprites.shot);
	al_destroy_bitmap(game.sprites.enemy);
	al_destroy_bitmap(game.sprites.enemy_shot);
	al_destroy_bitmap(game.sprites.nave_life);
	al_destroy_bitmap(game.sprites.explosao);
	al_destroy_bitmap(game.sprites.background_menu);
	al_destroy_font(game.font);
    al_destroy_timer(game.timer);
	destroy_display(&game);
	al_destroy_event_queue(game.event_queue);

    return 0;
}