#ifndef ARQ_OBJECT_H
#define ARQ_OBJECT_H

#include <allegro5/allegro.h>

typedef struct Game Game;

typedef struct{
    
    bool active; 
    int life;
    float x,y;
    ALLEGRO_COLOR cor;
} object;

void initObject(Game *p_game);
void draw_object(const Game *p_game);

#endif 