#include "arq_object.h"
#include "arq_game.h"
#include "arq_config.h"

#include <allegro5/allegro_primitives.h>

// PRECISO ARRUMAR ELE BEM AINDA

void initObject(Game *p_game){
    
    float y_pos = SCREEN_H - FLOOR_H - OBJECT_H;

    for(int i=0; i<OBJECTS_NUMB; i++){

        p_game->objects[i].active = true;
        p_game->objects[i].life = 3;
        p_game->objects[i].x = (SCREEN_W / 4.0) * (i + 1) - (OBJECT_W / 2);
        p_game->objects[i].y = y_pos;
        p_game->objects[i].sprite = p_game->sprites.object_A;
    }  
}

void draw_object(const Game *p_game){

    for(int i=0; i<OBJECTS_NUMB; i++){
		if(p_game->objects[i].active){

		    float sprite_w = al_get_bitmap_width(p_game->sprites.object_A);
            float sprite_h = al_get_bitmap_height(p_game->sprites.object_A);
            
            float new_sprite_w = OBJECT_W;
	        float new_sprite_h = OBJECT_H;

            float draw_x = p_game->objects[i].x - (new_sprite_w / 2.0);  
            float draw_y = p_game->objects[i].y - (new_sprite_h / 2.0);  

            al_draw_scaled_bitmap(p_game->objects[i].sprite, 0, 0, sprite_w, sprite_h, draw_x, draw_y, new_sprite_w, new_sprite_h, 0);
		}
	}
}             

void update_objects(Game *p_game){

    for(int i=0; i<OBJECTS_NUMB; i++){

        switch(p_game->objects[i].life){
            case 3:
                p_game->objects[i].sprite = p_game->sprites.object_A;
                break;

            case 2:
                p_game->objects[i].sprite = p_game->sprites.object_B;
                break;

            case 1:
                p_game->objects[i].sprite = p_game->sprites.object_C;
                break;
        }
    }
}

void new_round_object(Game *p_game){
    int exp = rand() % (OBJECTS_NUMB - 1);
    for(int i= 0; i<OBJECTS_NUMB; i++){
        if(i == exp){
            if(p_game->objects[i].active){
                p_game->objects[i].life++;
            }else{
                p_game->objects[i].active = true;
                p_game->objects[i].life = 1;
            }
        }
    }
}