#include "arq_shot.h"
#include "arq_game.h"
#include "arq_config.h"

#include <allegro5/allegro_primitives.h>

void initShot(Game *p_game){  // nao definir a loc do shot dentro dessa varialvel pois ele so é chamada 1 vez 

	for(int i=0; i<MAX_SHOTS; i++){

		p_game->shots[i].active = false; // começa inicializando ele como FALSO
	    p_game->shots[i].y_vel = 10;
	    p_game->shots[i].sprite = p_game->sprites.shot;
	}
}

void draw_shots(const Game *p_game){

	for (int i = 0; i<MAX_SHOTS; i++){
		 if (p_game->shots[i].active){
			
			float sprite_w = al_get_bitmap_width(p_game->sprites.shot);
   			float sprite_h = al_get_bitmap_height(p_game->sprites.shot);

			float new_sprite_w = SHOT_W;
			float new_sprite_h = SHOT_H;

			float draw_x = p_game->shots[i].x - (new_sprite_w/ 2.0);   
    		float draw_y = p_game->shots[i].y - (new_sprite_h / 2.0);

			al_draw_scaled_bitmap(p_game->sprites.shot, 0, 0, sprite_w, sprite_h, draw_x, draw_y, new_sprite_w, new_sprite_h, 0);
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