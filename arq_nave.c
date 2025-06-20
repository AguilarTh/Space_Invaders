#include "arq_nave.h"
#include "arq_game.h"
#include "arq_config.h"

void initNave(Game *p_game){

	p_game->nave.life = 3;
	p_game->nave.x = SCREEN_W /2;
	p_game->nave.vel = 5;
	p_game->nave.dir = 0;
	p_game->nave.esq = 0;
	p_game->nave.sprite = p_game->sprites.nave;
}

void draw_nave(const Game *p_game){
	
	int sprite_w = al_get_bitmap_width(p_game->sprites.nave);
    int sprite_h = al_get_bitmap_height(p_game->sprites.nave);

	float y_base= SCREEN_H - FLOOR_H;
	float draw_x = p_game->nave.x - (sprite_w / 2.0);
    float draw_y = y_base - (sprite_h / 2.0);

	al_draw_bitmap(p_game->nave.sprite, draw_x, draw_y, 0); // DESENHA A IMAGEM TODA -> AL_DRAW_BITMAP_REGION é q desenha so uma parte
}

void update_nave(Game *p_game){  // CONTROLE ESQ/DIR

	if(p_game->nave.dir && ( p_game->nave.x + NAVE_W/2 ) + p_game->nave.vel <= SCREEN_W){
		p_game->nave.x += p_game->nave.vel;
	}
	
	if(p_game->nave.esq && ( p_game->nave.x - NAVE_W/2 ) - p_game->nave.vel >= 0){
		p_game->nave.x -= p_game->nave.vel;
	}
}