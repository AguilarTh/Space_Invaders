#include "arq_enemy.h"
#include "arq_game.h"
#include "arq_config.h"

#include <stdlib.h>

void initEnemy(Game *p_game){
	
	for(int i=0; i<MAX_ENEMIES; i++){
		
		// CARACTERISTICAS PADRAO

		p_game->enemies[i].active= true;
		p_game->enemies[i].x_vel = 1;
	    p_game->enemies[i].y_vel = ENEMY_H + 5; 

		// ----- TIPOS DE INIMIGOS -----

		int roll = rand() % 10;

		if(roll < 6){
			p_game->enemies[i].type = NORMAL;
		}
		else if(roll < 9){
			p_game->enemies[i].type = RARE;
		}
		else{
			p_game->enemies[i].type = LEGENDARY;
		}
		
		switch(p_game->enemies[i].type){
			case NORMAL:
			  p_game->enemies[i].score = 1;
	          p_game->enemies[i].life = 1;
	          p_game->enemies[i].sprite = p_game->sprites.enemy;
			  break;
			
			case RARE:
			  p_game->enemies[i].score = 5;
	          p_game->enemies[i].life = 1;
	          p_game->enemies[i].sprite = p_game->sprites.enemy;
			  break;
			
			case LEGENDARY:
			  p_game->enemies[i].score = 15;
	          p_game->enemies[i].life = 1;
	          p_game->enemies[i].sprite = p_game->sprites.enemy;
			  break;
		}
		
		// DISPERSAR O INIMIGOS:

		p_game->enemies[i].x = (i % 5) * (ENEMY_W + 30) + 50; // o %5 cria um padrao q distribui os inimigos em 5 colunas
	    p_game->enemies[i].y = ( i / 5) * (ENEMY_H + 30) + 80; // o /5 tambem cria um padrao q dividi em 2 linhas ( 0 e 1)
		// o +20 é para o espaçamento entre inimigos e o +50/20 é para distanciar da margem
		// se quiser q divida em "X" colunas -> %X
	}
}

void verifica_vida(Game *p_game){  // DESATIVA O INIMIGO IF LIFE == 0

	if(p_game->enemies->life == 0){
		p_game->enemies->active = false;
	}
}

void draw_enemy(const Game *p_game){

	for(int i=0; i<MAX_ENEMIES; i++){
		if(p_game->enemies[i].active){

			float sprite_w = al_get_bitmap_width(p_game->sprites.enemy);
   			float sprite_h = al_get_bitmap_height(p_game->sprites.enemy);

			float new_sprite_w = ENEMY_W;
			float new_sprite_h = ENEMY_H;

			float draw_x = p_game->enemies[i].x - (new_sprite_w/ 2.0);   
    		float draw_y = p_game->enemies[i].y - (new_sprite_h / 2.0);

			al_draw_scaled_bitmap(p_game->sprites.enemy, 0, 0, sprite_w, sprite_h, draw_x, draw_y, new_sprite_w, new_sprite_h, 0);
		}
	}
}

void update_enemy(Game *p_game){  // MOVIMENTAÇÃO/COLISAO/SPEED INCREASE

	bool wall_tracker = false; // colisao enemy-wall
	int enemies_dead = MAX_ENEMIES - contar_inimigos_vivos(p_game);
	float veloc_atual = ENEMIES_BASE_SPEED + ( enemies_dead * ENEMIES_SPEED_INCREASE );

	for(int i=0; i<MAX_ENEMIES; i++){

		if(!p_game->enemies[i].active){
			continue;  // qual a diferença dos dois mesmo?
		}  

		if((p_game->enemies[i].x + ENEMY_W + p_game->enemies[i].x_vel > SCREEN_W) || (p_game->enemies[i].x + p_game->enemies[i].x_vel < 0)){
			wall_tracker = true;
			break; // uso do break apenas por EFICIENCIA, se 1 ja bateu nn precisa verificar os outros
		}
	}
		
    if(wall_tracker){
		for(int i=0; i<MAX_ENEMIES; i++){
			if(p_game->enemies[i].active){
				p_game->enemies[i].x_vel *= -1;
				p_game->enemies[i].y += p_game->enemies[i].y_vel;
			}
		}
	}

	for(int i=0; i<MAX_ENEMIES; i++){
		if(p_game->enemies[i].active){
			p_game->enemies[i].x += p_game->enemies[i].x_vel * veloc_atual;
		}
	}	
}

int contar_inimigos_vivos(Game *p_game){  // RETORNA O NUM DE INIMIGOS VIVOS

	int enemies_alive=0;
	for(int i=0; i<MAX_ENEMIES; i++){
		if(p_game->enemies[i].active){
			enemies_alive++;
		}
	}
	return enemies_alive;
}

void enemy_dmg_visuals_update(enemy *p_enemy){ // RETORNO VISUAL DO DANO -> VAI SER PASSADA DENTRO DA COLISSAO, ENT NN USAR A STRUCT GLOBAL
	
	switch(p_enemy->type){
		case RARE:
		  if(p_enemy->life == 1){
			//p_enemy->cor = al_map_rgb(196, 194, 210);
		  }
		  break;

		case LEGENDARY:
		  switch(p_enemy->life){
			case 2:
			   	//p_enemy->cor = al_map_rgb(181, 153, 96);
                break;
			case 1:
			    //p_enemy->cor = al_map_rgb(195, 181, 154);
                break;
		  }
		  break;
	}
}