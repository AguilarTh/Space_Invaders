#ifndef ARQ_CONFIG_H
#define ARQ_CONFIG_H

// --- DIMENSÕES TELA ---

/*#define SCREEN_W 1920
#define SCREEN_H 1080 */
#define SCREEN_W 1280  // 16:9
#define SCREEN_H 720

#define FLOOR_H  60

// --- CONFIGURAÇÃO ---

#define FPS      100.0f
#define MAX_FRAMES_POR_ANIMAÇÃO 10

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
#define MAX_ENEMIES_SHOTS 50
#define MAX_EXPLOSOES 20
#define ENEMIES_BASE_SPEED 1.0
#define ENEMIES_SPEED_INCREASE 0.30
#define MAX_SHOTS 1

typedef enum{
    NORMAL,
    RARE,
    LEGENDARY
} EnemyType;

// --- DIMENSÕES ENTIDADES ---

#define UI_W 40
#define UI_H 40

#define NAVE_W 80
#define NAVE_H 50

#define SHOT_W 20
#define SHOT_H 45

#define ENEMY_W 40
#define ENEMY_H 30

#define OBJECTS_NUMB 3
#define OBJECT_W 100
#define OBJECT_H 100

#endif 