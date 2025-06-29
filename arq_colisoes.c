#include "arq_colisoes.h"
#include "arq_game.h"
#include "arq_config.h"

#include <stdio.h>

bool check_collision_retangulo(float x1, float y1, float w1, float h1,
                                float x2, float y2, float w2, float h2){   // VERIFICADOR DE COLISÃO
	if(x1 + w1 > x2 &&
	   x1 < x2 + w2 &&
	   y1 + h1 > y2 &&
	   y1 < y2 + h2){
		
		return true; // HOUVE COLISAO
	}
	return false; // NAO HOUVE COLISAO
}

int colisao_enemy_solo(Game *p_game){

	for(int i=0; i<MAX_ENEMIES; i++){
		if(p_game->enemies[i].active){
			if(p_game->enemies[i].y + ENEMY_H >= SCREEN_H - FLOOR_H){  
				return 1;
			}
		}
	}
	return 0;
}

int colisao_enemy_nave(Game *p_game){
      
    for (int i = 0; i < MAX_ENEMIES; i++) {
		if (p_game->enemies[i].active) {
           
        	float enemy_hitbox_x = p_game->enemies[i].x - (ENEMY_W / 2.0);
        	float enemy_hitbox_y = p_game->enemies[i].y - (ENEMY_H / 2.0);

        	// HITBOX DA NAVE:
			float nave_hitbox_x = p_game->nave.x - NAVE_W / 2;
        	float nave_hitbox_y = SCREEN_H - FLOOR_H / 2 - NAVE_H;

        	if (check_collision_retangulo(
            	enemy_hitbox_x, enemy_hitbox_y, ENEMY_W, ENEMY_H,
            	nave_hitbox_x, nave_hitbox_y, NAVE_W, NAVE_H
            	))
        	{
				return 1;
        	}
    	}		
	}
	return 0;
}

void colisao_shot_enemy(Game *p_game){  

	for(int i=0; i<MAX_SHOTS; i++){

		if(!p_game->shots[i].active){
			continue;
		}

		for(int j=0; j<MAX_ENEMIES; j++){

			if(!p_game->enemies[j].active){
				continue;
			}

			if(check_collision_retangulo( 
				p_game->shots[i].x, p_game->shots[i].y, SHOT_W, SHOT_H,          // Ret 1: Tiro Jogador
                p_game->enemies[j].x, p_game->enemies[j].y, ENEMY_W, ENEMY_H)    // Ret 2: Enemy
			){

					p_game->shots[i].active = false; // "desativa o tiro"
					p_game->enemies[j].life--;
					enemy_dmg_visuals_update(&p_game->enemies[j]);

					if(p_game->enemies[j].life <= 0){
						p_game->enemies[j].active = false;
						(p_game->score) += p_game->enemies[j].score; 
						tentar_dropar_buff(p_game, &p_game->enemies[j]);
						ativar_explosao(p_game, p_game->enemies[j].x, p_game->enemies[j].y);
					}

					break; // se o tiro ja pegou 1 inimigo nn precisa olhar os outros

			}
		}
	}
}

void colisao_enemy_shot_nave(Game *p_game){
	for(int i=0; i<MAX_ENEMIES_SHOTS; i++){
		if(p_game->enemies_shots[i].active){

			// HITBOX DA NAVE:
			float nave_hitbox_x = p_game->nave.x - NAVE_W / 2;
            float nave_hitbox_y = SCREEN_H - FLOOR_H / 2 - NAVE_H;

			if (check_collision_retangulo(   // Fica mais "clean" c/ uma funcao auxiliar
				    p_game->enemies_shots[i].x, p_game->enemies_shots[i].y, SHOT_W, SHOT_H,  // Ret 1: Tiro
                    nave_hitbox_x, nave_hitbox_y, NAVE_W, NAVE_H)  // Ret 2: Nave
			){

				p_game->enemies_shots[i].active = false;
				if(p_game->immunity == false){
					p_game->nave.life--;
					al_play_sample(p_game->audio.dmg_nave, 0.4, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					printf("Nave atingida. Vidas restantes: %d", p_game->nave.life);
				}
		    }
	    }
    }
}

void colisao_shot_object(Game *p_game){

	for(int i=0; i<MAX_SHOTS; i++){
		if(p_game->shots[i].active){
			for(int j=0; j<OBJECTS_NUMB; j++){
				if(p_game->objects[j].active){
					if(check_collision_retangulo(
						p_game->shots[i].x, p_game->shots[i].y, SHOT_W, SHOT_H,
						p_game->objects[j].x - (OBJECT_W/2), p_game->objects[j].y - (OBJECT_H/2), OBJECT_W, OBJECT_H)
					){
						p_game->shots[i].active = false;
					}
				}	
			}
		}
	}
}

void colisao_enemy_shot_object(Game *p_game){

	for(int i=0; i<MAX_ENEMIES_SHOTS; i++){
		if(p_game->enemies_shots[i].active){
			
			for(int j=0; j<OBJECTS_NUMB; j++){
				if(p_game->objects[j].active){

					if(check_collision_retangulo(
						p_game->enemies_shots[i].x, p_game->enemies_shots[i].y, SHOT_W, SHOT_H,
						p_game->objects[j].x - (OBJECT_W/2), p_game->objects[j].y - (OBJECT_H/2), OBJECT_W, OBJECT_H)
					){
					
						p_game->enemies_shots[i].active = false;
						p_game->objects[j].active = false;
						al_play_sample(p_game->audio.explosao_objeto, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					}
				}
			}
		}
	}
}

void colisao_enemy_object(Game *p_game){
	for(int i=0; i<MAX_ENEMIES; i++){
		if(p_game->enemies[i].active){
			for(int j=0; j<OBJECTS_NUMB; j++){
				if(p_game->objects[j].active){
					if(check_collision_retangulo(
						p_game->enemies[i].x, p_game->enemies[i].y, ENEMY_W, ENEMY_H,       // ENEMY
						p_game->objects[j].x, p_game->objects[j].y, OBJECT_W, OBJECT_H)     // OBJECT
					){
						p_game->enemies[i].active = false;
						ativar_explosao(p_game, p_game->enemies[j].x, p_game->enemies[j].y);
						p_game->objects[j].active = false;
						al_play_sample(p_game->audio.explosao_objeto, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					}
				}
			}
		}
	}
}

void colisao_nave_powerup(Game *p_game){

	for(int i=0; i<MAX_POWERUPS; i++){
		if(p_game->powerups[i].active){
			
			float nave_hitbox_x = p_game->nave.x - NAVE_W / 2;
            float nave_hitbox_y = SCREEN_H - FLOOR_H / 2 - NAVE_H;

			if (check_collision_retangulo(   
				    p_game->powerups[i].x, p_game->powerups[i].y, POWERUP_W, POWERUP_H,  // Ret 1: PowerUp
                    nave_hitbox_x, nave_hitbox_y, NAVE_W, NAVE_H)                        // Ret 2: Nave
			){

				p_game->powerups[i].active = false; 
        		aplicar_buff(p_game, p_game->powerups[i].tipo);
		    }
		}

	}
}