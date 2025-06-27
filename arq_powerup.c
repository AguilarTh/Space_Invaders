#include "arq_powerup.h"
#include "arq_game.h"
#include <stdlib.h>

void tentar_dropar_buff(Game *p_game, enemy *inimigo_morto) {
    
    int chance_drop = 0;

    // Drop Rate:

    switch (inimigo_morto->type) {
        case NORMAL: 
            chance_drop = 15; 
            break;
        case RARE: 
            chance_drop = 30; 
            break;
        case LEGENDARY: 
            chance_drop = 50; 
            break;
    }

    // RNG 1: Drop do item:

    if (rand() % 100 < chance_drop) {
        
        // RNG 2: Qual item:

        int chance_tipo = rand() % 100;
        BuffTypes tipo_dropado;

        if (chance_tipo < 20) {        // 20% de chance
            tipo_dropado = BUFF_VIDA;

        } else if (chance_tipo < 50) { // 30% de chance
            tipo_dropado = BUFF_IMUNIDADE;
        } else {                       // 50% de chance
            tipo_dropado = BUFF_VEL;
        }

        // Procura uma vaga de PowerUp vazia:

        for (int i = 0; i < MAX_POWERUPS; i++) {
            if (!p_game->powerups[i].active) {
                p_game->powerups[i].active = true;
                p_game->powerups[i].x = inimigo_morto->x;
                p_game->powerups[i].y = inimigo_morto->y;
                p_game->powerups[i].y_vel = 1.5f; // Cai lentamente
                p_game->powerups[i].tipo = tipo_dropado;
                break;
            }
        }
    }
}

void init_powerups(Game *p_game) {
    
    for (int i = 0; i < MAX_POWERUPS; i++){
        p_game->powerups[i].active = false;
    }
}

void update_powerups(Game *p_game) {
    
    for (int i = 0; i < MAX_POWERUPS; i++) {
        if (p_game->powerups[i].active) {
            p_game->powerups[i].y += p_game->powerups[i].y_vel;
            
            // Desativa se sair da tela
            if (p_game->powerups[i].y > SCREEN_H) p_game->powerups[i].active = false;
        }
    }
}

void draw_powerups(Game *p_game) {
    
    for (int i = 0; i < MAX_POWERUPS; i++) {
        if (p_game->powerups[i].active) {
            
            switch(p_game->powerups[i].tipo) {
                case BUFF_VIDA: 
                    p_game->powerups[i].sprite = p_game->sprites.powerUp_Life;
                    break;
                case BUFF_IMUNIDADE: 
                    p_game->powerups[i].sprite = p_game->sprites.powerUp_Imunidade;
                    break; 
                case BUFF_VEL: 
                    p_game->powerups[i].sprite = p_game->sprites.powerUp_Vel;
                    break; 
            }
            
            float sprite_w = al_get_bitmap_width(p_game->powerups[i].sprite);
            float sprite_h = al_get_bitmap_height(p_game->powerups[i].sprite);
            
            float new_sprite_w = POWERUP_W;
	        float new_sprite_h = POWERUP_H;

            float draw_x = p_game->powerups[i].x - (new_sprite_w / 2.0);  
            float draw_y = p_game->powerups[i].y - (new_sprite_h / 2.0);

            al_draw_scaled_bitmap(p_game->powerups[i].sprite, 
                                  0, 0, 
                                  sprite_w, sprite_h, 
                                  draw_x, draw_y, 
                                  new_sprite_w, new_sprite_h, 
                                  0);
        }
    }
}

void aplicar_buff(Game *p_game, BuffTypes tipo) {
    switch (tipo) {
        case BUFF_VIDA:
            if(p_game->nave.life <= 2){
                p_game->nave.life++;
                al_play_sample(p_game->audio.powerup_life, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            }
            break;

        case BUFF_IMUNIDADE:
            p_game->tempo_buff_imunidade_restante = 10.0f; // TIMER
            al_play_sample(p_game->audio.powerup_imm, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            break;

        case BUFF_VEL:
            p_game->tempo_buff_velocidade_restante = 5.0f; // TIMER
            al_play_sample(p_game->audio.powerup_vel, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            break;
    }
}