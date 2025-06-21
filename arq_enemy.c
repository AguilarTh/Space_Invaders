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
		p_game->enemies[i].frame_atual = 0;
		p_game->enemies[i].time_count = 0.0;
		p_game->enemies[i].sprite = p_game->sprites.enemy;
		p_game->enemies[i].dmg_count_timer = 0.0f;

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
			 	p_game->enemies[i].score = 5 *p_game->round_atual;
	          	p_game->enemies[i].life = 1 + (p_game->round_atual / 4);
			  	p_game->enemies[i].total_frames = 2;
			  	p_game->enemies[i].frame_time = 0.5f;
			 	p_game->enemies[i].frames[0] = (AnimationFrameEnemy){ .sx=2, .sy=203, .sw=14, .sh=16};
        		p_game->enemies[i].frames[1] = (AnimationFrameEnemy){ .sx=22, .sy=203, .sw=14, .sh=16};
			  	break;
			
			case RARE:
			  	p_game->enemies[i].score = 25 *p_game->round_atual;
	          	p_game->enemies[i].life = 2 + (p_game->round_atual / 5);
			 	p_game->enemies[i].total_frames = 2;
			  	p_game->enemies[i].frame_time = 0.5f;
			 	p_game->enemies[i].frames[0] = (AnimationFrameEnemy){ .sx=2, .sy=183, .sw=14, .sh=16};
        		p_game->enemies[i].frames[1] = (AnimationFrameEnemy){ .sx=22, .sy=183, .sw=14, .sh=16};
			 	break;
			
			case LEGENDARY:
			  	p_game->enemies[i].score = 50 *p_game->round_atual;
	        	p_game->enemies[i].life = 3 + (p_game->round_atual / 6);
			  	p_game->enemies[i].total_frames = 2;
			  	p_game->enemies[i].frame_time = 0.5f;
			 	p_game->enemies[i].frames[0] = (AnimationFrameEnemy){ .sx=2, .sy=223, .sw=14, .sh=16};
        		p_game->enemies[i].frames[1] = (AnimationFrameEnemy){ .sx=22, .sy=223, .sw=14, .sh=16};
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

			const enemy *e = &p_game->enemies[i];
			AnimationFrameEnemy frame_info = e->frames[e->frame_atual];

			// Dados Recorte

			float sx = frame_info.sx;
            float sy = frame_info.sy;
            float sw = frame_info.sw; // Largura original do frame 
            float sh = frame_info.sh; // Altura original do frame 

			// Tamanho Dimensionado

			float proporcao = sh / sw;
			float dw = ENEMY_W; 
            float dh = dw * proporcao;

			// Centralizar o Desenho

			float dx = e->x - (dw / 2.0);
            float dy = e->y - (dh / 2.0);

			al_draw_scaled_bitmap(e->sprite,      // A spritesheet correta para este inimigo
                                  sx, sy, sw, sh, // A região a ser recortada da imagem
                                  dx, dy, dw, dh, // A posição e o NOVO tamanho na tela
                                  0);						
		}
	}
}

// OLHAR SE ESSE CODIGO ESTÁ OTIMIZADO -> ACHO Q NAO
void update_enemy(Game *p_game){  // MOVIMENTAÇÃO/COLISAO/SPEED INCREASE

	bool wall_tracker = false; // colisao enemy-wall

	float bonus_velocidade_onda = (p_game->round_atual - 1) * 0.1f;
	int enemies_dead = MAX_ENEMIES - contar_inimigos_vivos(p_game);
	float veloc_atual = ENEMIES_BASE_SPEED + bonus_velocidade_onda + (enemies_dead * ENEMIES_SPEED_INCREASE);

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

	// LOGICA ANIMAÇÃO/MOV:

	for(int i=0; i<MAX_ENEMIES; i++){
		if(p_game->enemies[i].active){
			p_game->enemies[i].x += p_game->enemies[i].x_vel * veloc_atual;
			p_game->enemies[i].time_count += 1.0 / FPS;

			if(p_game->enemies[i].time_count >= p_game->enemies[i].frame_time){
				p_game->enemies[i].time_count = 0; 	// Reseta o contador
				p_game->enemies[i].frame_atual++;	// Avança para o próximo frame

				if(p_game->enemies[i].frame_atual >= p_game->enemies[i].total_frames){
					p_game->enemies[i].frame_atual = 0;
				}
			}
		}
		if (p_game->enemies[i].dmg_count_timer > 0) {

            // Se o cronômetro estiver ativo, diminui o tempo
            p_game->enemies[i].dmg_count_timer -= 1.0 / FPS; 

            // Se o tempo acabou...
            if (p_game->enemies[i].dmg_count_timer <= 0) {
                restaurar_animacao_padrao(&p_game->enemies[i]); 
            }
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

// VER SE ESSE RETORNO VISUAL MEU FOI FEITO DA MELHOR FORMA:

void enemy_dmg_visuals_update(enemy *p_enemy){ // RETORNO VISUAL DO DANO 
	p_enemy->dmg_count_timer = 0.10f;
	p_enemy->total_frames = 2;
    p_enemy->frame_atual = 0; // Reinicia a animação para o novo estado
	p_enemy->time_count = 0.0f;

    p_enemy->frames[0] = (AnimationFrameEnemy){.sx=2, .sy=163, .sw=14, .sh=16};
    p_enemy->frames[1] = (AnimationFrameEnemy){.sx=22, .sy=163, .sw=14, .sh=16};
} 

void restaurar_animacao_padrao(enemy *p_enemy){
	
	p_enemy->frame_atual = 0;
	p_enemy->time_count = 0.0f;

	switch(p_enemy->type){
		case NORMAL:
			p_enemy->total_frames = 2;
			p_enemy->frame_time = 0.5f;
			p_enemy->frames[0] = (AnimationFrameEnemy){ .sx=2, .sy=203, .sw=14, .sh=16};
        	p_enemy->frames[1] = (AnimationFrameEnemy){ .sx=22, .sy=203, .sw=14, .sh=16};
			break;
			
		case RARE:
			p_enemy->total_frames = 2;
			p_enemy->frame_time = 0.5f;
			p_enemy->frames[0] = (AnimationFrameEnemy){ .sx=2, .sy=183, .sw=14, .sh=16};
        	p_enemy->frames[1] = (AnimationFrameEnemy){ .sx=22, .sy=183, .sw=14, .sh=16};
			break;
			
		case LEGENDARY:
			p_enemy->total_frames = 2;
			p_enemy->frame_time = 0.5f;
			p_enemy->frames[0] = (AnimationFrameEnemy){ .sx=2, .sy=223, .sw=14, .sh=16};
        	p_enemy->frames[1] = (AnimationFrameEnemy){ .sx=22, .sy=223, .sw=14, .sh=16};
			break;
	}

}