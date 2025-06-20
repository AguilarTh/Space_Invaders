#include "arq_shot.h"
#include "arq_game.h"
#include "arq_config.h"

#include <allegro5/allegro_primitives.h>

void initShot(Game *p_game){  // nao definir a loc do shot dentro dessa varialvel pois ele so é chamada 1 vez 

	for(int i=0; i<MAX_SHOTS; i++){

		p_game->shots[i].active = false; // começa inicializando ele como FALSO
	    p_game->shots[i].y_vel = 10;
	    p_game->shots[i].cor = al_map_rgb(255, 255, 0);
	}
}

void draw_shot(const Game *p_game){

	for(int i=0; i<MAX_SHOTS; i++){
		if(p_game->shots[i].active){
			al_draw_filled_rectangle(p_game->shots[i].x, p_game->shots[i].y, p_game->shots[i].x + SHOT_W, p_game->shots[i].y + SHOT_H, p_game->shots[i].cor);
		}
	}
}

void update_shot(Game *p_game){  // MOVIMENTAÇÃO/ULTRAPASSAGEM DA TELA

	for(int i=0; i<MAX_SHOTS; i++){

		if(p_game->shots[i].active){
			p_game->shots[i].y -= p_game->shots[i].y_vel;
		}

		if(p_game->shots[i].y < 0){
			p_game->shots[i].active = false;
		}
	}	
}