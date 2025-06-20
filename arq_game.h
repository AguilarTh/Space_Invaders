#ifndef ARQ_GAME_H
#define ARQ_GAME_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "arq_config.h"
#include "arq_nave.h"
#include "arq_enemy.h"
#include "arq_shot.h"
#include "arq_enemy_shot.h"
#include "arq_object.h"

typedef struct {

    ALLEGRO_BITMAP *nave;
    ALLEGRO_BITMAP *background_menu;
    // ... adicione outros sprites aqui conforme for criando
} GameSprites;

typedef struct Game {

    // --- Componentes Principais do Allegro ---

    ALLEGRO_DISPLAY *display;
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_FONT *font;
    GameSprites sprites;

    // --- Estado do Jogo ---

    GameStates estado_atual;
    int score;
    int high_score;

    // --- Objetos do Jogo ---

    nave nave;
    enemy enemies[MAX_ENEMIES];
    shot shots[MAX_SHOTS];
    enemyshot enemies_shots[MAX_ENEMIES_SHOTS];
    object objects[OBJECTS_NUMB];

    // --- Dados da Tela ---

    float scale;
    float offset_x;
    float offset_y;

} Game;

#endif