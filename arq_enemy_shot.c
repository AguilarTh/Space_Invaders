#include "arq_enemy_shot.h"
#include "arq_game.h"
#include "arq_config.h"
#include <stdlib.h>

#include <allegro5/allegro_primitives.h>


void initEnemyShot(Game *p_game){  // INICIALIZA TODOS COMO FALSE A PRIORI
    
    for(int i=0; i<MAX_ENEMIES_SHOTS; i++){
        p_game->enemies_shots[i].sprite = p_game->sprites.enemy_shot;
        p_game->enemies_shots[i].active = false;
    }
}

void try_enemy_shot(Game *p_game){  // % DE DISPARO

    if(rand() % 150 == 0){  // chance de 1/200

        int shooter_ind = rand() % MAX_ENEMIES;
        if(p_game->enemies[shooter_ind].active){
            for(int i=0; i<MAX_ENEMIES_SHOTS; i++){
                if(!p_game->enemies_shots[i].active){
                    al_play_sample(p_game->audio.tiro_enemy, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    p_game->enemies_shots[i].active = true;
                    p_game->enemies_shots[i].x = p_game->enemies[shooter_ind].x + ENEMY_W/2;
                    p_game->enemies_shots[i].y = p_game->enemies[shooter_ind].y + ENEMY_H;
                    p_game->enemies_shots[i].y_vel = 4; // Velocidade
                    break; // sair apos disparar 1 tiro
                }
            }
        }
    }    
}

void draw_enemy_shot(const Game *p_game){
    for(int i=0; i<MAX_ENEMIES_SHOTS; i++){
        if(p_game->enemies_shots[i].active){
            float sprite_w = al_get_bitmap_width(p_game->sprites.enemy_shot);
   			float sprite_h = al_get_bitmap_height(p_game->sprites.enemy_shot);

			float new_sprite_w = SHOT_W;
			float new_sprite_h = SHOT_H;

			float draw_x = p_game->enemies_shots[i].x - (new_sprite_w/ 2.0);   
    		float draw_y = p_game->enemies_shots[i].y - (new_sprite_h / 2.0);

			al_draw_scaled_bitmap(p_game->sprites.enemy_shot, 0, 0, sprite_w, sprite_h, draw_x, draw_y, new_sprite_w, new_sprite_h, 0);
        }
    }
}

void update_enemy_shot(Game *p_game){
    for(int i=0; i<MAX_ENEMIES_SHOTS; i++){
        if(p_game->enemies_shots[i].active){
            p_game->enemies_shots[i].y += p_game->enemies_shots[i].y_vel;
            if(p_game->enemies_shots[i].y > SCREEN_H){
                p_game->enemies_shots[i].active = false;
            }
        }
    }
}