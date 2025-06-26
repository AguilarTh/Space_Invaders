#include "arq_nave.h"
#include "arq_game.h"
#include "arq_config.h"

void initNave(Game *p_game){

	p_game->nave.life = 3;
	p_game->nave.x = SCREEN_W /2;
	p_game->nave.vel = NAVE_BASE_SPEED;
	p_game->nave.dir = 0;
	p_game->nave.esq = 0;

	switch(p_game->type_game){
		case 1:
			p_game->nave.sprite = p_game->sprites.nave_1;
			break;
		case 2:
			p_game->nave.sprite = p_game->sprites.nave_2;
			break;
		case 3:
			p_game->nave.sprite = p_game->sprites.nave_3;
			break;
		case 4:
			p_game->nave.sprite = p_game->sprites.nave_4;
			break;
		case 5:
			p_game->nave.sprite = p_game->sprites.nave_5;
			break;
	}
}

void draw_nave_life(const Game *p_game){

	float new_sprite_w = UI_W;
	float new_sprite_h = UI_H;

	float draw_x = 10;
	float draw_y = SCREEN_H - 50;

	for(int i=0; i<p_game->nave.life; i++){
		al_draw_scaled_bitmap(p_game->sprites.nave_life, 0, 1, 16, 15, draw_x, draw_y, new_sprite_w, new_sprite_h, 0);
		draw_x += 50;
	}
}
void draw_nave(const Game *p_game){
	
	// Dimensoes ORIGINAIS do png:
	float sprite_w = al_get_bitmap_width(p_game->nave.sprite);
    float sprite_h = al_get_bitmap_height(p_game->nave.sprite);

	// Definindo NOVAS DIMENSOES:
	float new_sprite_w = NAVE_W;
	float new_sprite_h = NAVE_H;

	// Posição na tela:
	float draw_x = p_game->nave.x - (new_sprite_w / 2.0);  // largura
    float draw_y = (SCREEN_H - FLOOR_H) - (new_sprite_h / 2.0);  // altura

	al_draw_scaled_bitmap(p_game->nave.sprite, 0, 0, sprite_w, sprite_h, draw_x, draw_y, new_sprite_w, new_sprite_h, 0);
	// DESENHA A IMAGEM TODA -> AL_DRAW_BITMAP_REGION é q desenha so uma parte
}

void update_nave(Game *p_game){  // CONTROLE ESQ/DIR

	if(p_game->nave.dir && ( p_game->nave.x + NAVE_W/2 ) + p_game->nave.vel <= SCREEN_W){
		p_game->nave.x += p_game->nave.vel;
	}
	
	if(p_game->nave.esq && ( p_game->nave.x - NAVE_W/2 ) - p_game->nave.vel >= 0){
		p_game->nave.x -= p_game->nave.vel;
	}
}