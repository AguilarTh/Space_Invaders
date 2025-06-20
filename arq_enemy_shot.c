#include "arq_enemy_shot.h"
#include "arq_game.h"
#include "arq_config.h"
#include <stdlib.h>

#include <allegro5/allegro_primitives.h>


void initEnemyShot(Game *p_game){  // INICIALIZA TODOS COMO FALSE A PRIORI
    
    for(int i=0; i<MAX_ENEMIES_SHOTS; i++){
        p_game->enemies_shots[i].active = false;
    }
}

void try_enemy_shot(Game *p_game){  // % DE DISPARO

    if(rand() % 200 == 0){  // chance de 1/200

        int shooter_ind = rand() % MAX_ENEMIES;
        if(p_game->enemies[shooter_ind].active){
            for(int i=0; i<MAX_ENEMIES_SHOTS; i++){
                if(!p_game->enemies_shots[i].active){
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
            al_draw_filled_rectangle(p_game->enemies_shots[i].x, p_game->enemies_shots[i].y, p_game->enemies_shots[i].x + SHOT_W, p_game->enemies_shots[i].y + SHOT_H, al_map_rgb(255, 0, 0));
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