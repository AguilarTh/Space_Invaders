#ifndef ARQ_GAME_H
#define ARQ_GAME_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "arq_config.h"
#include "arq_nave.h"
#include "arq_enemy.h"
#include "arq_shot.h" 
#include "arq_enemy_shot.h"
#include "arq_object.h"
#include "arq_explosao.h"
#include "arq_powerup.h"

typedef struct {

    ALLEGRO_BITMAP *nave;
    ALLEGRO_BITMAP *nave_life;
    ALLEGRO_BITMAP *shot;
    ALLEGRO_BITMAP *enemy;
    ALLEGRO_BITMAP *enemy_shot;
    ALLEGRO_BITMAP *object_A;
    ALLEGRO_BITMAP *object_B;
    ALLEGRO_BITMAP *object_C;
    ALLEGRO_BITMAP *explosao;
    ALLEGRO_BITMAP *powerUp_Life;
    ALLEGRO_BITMAP *powerUp_Tiros;
    ALLEGRO_BITMAP *powerUp_Vel;

    ALLEGRO_BITMAP *background_menu;
    ALLEGRO_BITMAP *background_jogo;
    // ... adicione outros sprites aqui conforme for criando
} GameSprites;

typedef struct {

    ALLEGRO_SAMPLE *tiro_nave;
    ALLEGRO_SAMPLE *tiro_enemy;
    ALLEGRO_SAMPLE *explosao_nave;
    ALLEGRO_SAMPLE *explosao_inimigo;
    ALLEGRO_SAMPLE *explosao_objeto;

    ALLEGRO_AUDIO_STREAM *musica_fundo_jogo;

} GameAudio;

typedef struct Game {

    // --- Componentes Principais do Allegro ---

    ALLEGRO_DISPLAY *display;
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_FONT *font;
    GameSprites sprites;
    GameAudio audio;

    // --- Estado do Jogo ---

    GameStates estado_atual;
    int round_atual;
    int score;
    int high_score;

    // --- Objetos do Jogo ---

    nave nave;
    enemy enemies[MAX_ENEMIES];
    shot shots[MAX_SHOTS];
    enemyshot enemies_shots[MAX_ENEMIES_SHOTS];
    object objects[OBJECTS_NUMB];
    PowerUpDrop powerups[MAX_POWERUPS];

    // --- CONTROLE DE BUFFS ---

    float tempo_buff_velocidade_restante;
    float tempo_buff_tiros_restante;
    int max_shots_atual;

    // --- ANIMAÇÕES ---

    Explosao explosoes[MAX_EXPLOSOES];

    // --- Dados da Tela ---

    float scale;
    float offset_x;
    float offset_y;

} Game;

#endif