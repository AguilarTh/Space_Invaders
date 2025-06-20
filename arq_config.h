#ifndef ARQ_CONFIG_H
#define ARQ_CONFIG_H

// --- DIMENSÕES TELA ---

#define SCREEN_W 1920
#define SCREEN_H 1080
//#define SCREEN_W 224
//#define SCREEN_H 256

#define FLOOR_H  60

// --- CONFIGURAÇÃO ---

#define FPS      100.0f

// --- ESTADOS DO JOGO ---

typedef enum{
    MENU,
    JOGO_ATIVO,
    AJUDA,
    CONFIG,
    SAIR
} GameStates;

// --- INIMIGOS/SHOTS ---

#define MAX_ENEMIES 20
#define MAX_ENEMIES_SHOTS 30
#define ENEMIES_BASE_SPEED 3.0
#define ENEMIES_SPEED_INCREASE 0.5
#define MAX_SHOTS 1

typedef enum{
    NORMAL,
    RARE,
    LEGENDARY
} EnemyType;

// --- DIMENSÕES ENTIDADES ---

#define NAVE_W 50
#define NAVE_H 25

#define SHOT_W 10
#define SHOT_H 15

#define ENEMY_W 50
#define ENEMY_H 25

#define OBJECTS_NUMB 3
#define OBJECT_W 75
#define OBJECT_H 75

#endif 