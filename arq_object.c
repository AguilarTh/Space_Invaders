#include "arq_object.h"
#include "arq_game.h"
#include "arq_config.h"

#include <allegro5/allegro_primitives.h>

// PRECISO ARRUMAR ELE BEM AINDA

void initObject(Game *p_game){
    
    float y_pos = SCREEN_H - FLOOR_H - OBJECT_H - 50;

    for(int i=0; i<OBJECTS_NUMB; i++){

        p_game->objects[i].active = true;
        p_game->objects[i].life = 3;
        p_game->objects[i].x = (SCREEN_W / 4.0) * (i + 1) - (OBJECT_W / 2.0);
        p_game->objects[i].y = y_pos;
        p_game->objects[i].cor = al_map_rgb( 100, 100, 100);
    }
}

void draw_object(const Game *p_game){

    for(int i=0; i<OBJECTS_NUMB; i++){
        if(p_game->objects[i].active){
                al_draw_filled_rectangle(p_game->objects[i].x, p_game->objects[i].y, p_game->objects[i].x + OBJECT_W, p_game->objects[i].y + OBJECT_H, p_game->objects[i].cor);
        }
    }
}