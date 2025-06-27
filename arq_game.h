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

    ALLEGRO_BITMAP *nave_1;
    ALLEGRO_BITMAP *nave_2;
    ALLEGRO_BITMAP *nave_3;
    ALLEGRO_BITMAP *nave_4;
    ALLEGRO_BITMAP *nave_5;

    ALLEGRO_BITMAP *nave_life;
    ALLEGRO_BITMAP *shot;
    ALLEGRO_BITMAP *enemy;
    ALLEGRO_BITMAP *enemy_shot;
    ALLEGRO_BITMAP *object;
    ALLEGRO_BITMAP *explosao;
    ALLEGRO_BITMAP *powerUp_Life;
    ALLEGRO_BITMAP *powerUp_Imunidade;
    ALLEGRO_BITMAP *powerUp_Vel;
    ALLEGRO_BITMAP *shield;
    
    ALLEGRO_BITMAP *icone_janela;
    ALLEGRO_BITMAP *background_menu;

    ALLEGRO_BITMAP *background_jogo_1;
    ALLEGRO_BITMAP *background_jogo_2;
    ALLEGRO_BITMAP *background_jogo_3;
    ALLEGRO_BITMAP *background_jogo_4;
    ALLEGRO_BITMAP *background_jogo_atual;
    ALLEGRO_BITMAP *background_final;
} GameSprites;

typedef struct {

    ALLEGRO_SAMPLE *tiro_nave;
    ALLEGRO_SAMPLE *tiro_enemy;
    ALLEGRO_SAMPLE *explosao_nave;
    ALLEGRO_SAMPLE *explosao_inimigo;
    ALLEGRO_SAMPLE *explosao_objeto;
    ALLEGRO_SAMPLE *dmg_nave;
    ALLEGRO_SAMPLE *powerup_life;
    ALLEGRO_SAMPLE *powerup_imm;
    ALLEGRO_SAMPLE *powerup_vel;
    ALLEGRO_SAMPLE *game_over;
    ALLEGRO_SAMPLE *victory;

    ALLEGRO_AUDIO_STREAM *musica_jogo;
    ALLEGRO_AUDIO_STREAM *musica_menu;

} GameAudio;

typedef struct Game {

    // --- Componentes Principais do Allegro ---

    ALLEGRO_DISPLAY *display;
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_FONT *font_grande;
    ALLEGRO_FONT *font;
    ALLEGRO_FONT *font_pequena;
    ALLEGRO_FONT *font_pequena_2;
    GameSprites sprites;
    GameAudio audio;

    // --- Estado do Jogo ---

    GameStates estado_atual;
    GameStates musica_ativa;
    int type_game;
    int round_atual;
    int score;
    int high_score;

    // --- Objetos do Jogo ---

    nave nave;
    enemy enemies[MAX_ENEMIES];
    shot shots[10];
    enemyshot enemies_shots[MAX_ENEMIES_SHOTS];
    object objects[OBJECTS_NUMB];
    PowerUpDrop powerups[MAX_POWERUPS];

    // --- CONTROLE DE BUFFS ---

    float tempo_buff_velocidade_restante;
    float tempo_buff_imunidade_restante;
    bool immunity;

    // --- ANIMAÇÕES ---

    Explosao explosoes[MAX_EXPLOSOES];

    // --- Dados da Tela ---

    float scale;
    float offset_x;
    float offset_y;

} Game;

#endif