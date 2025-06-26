#ifndef ARQ_DESENHOS_AVULSOS
#define ARQ_DESENHOS_AVULSOS

typedef struct Game Game;

void draw_scenario(const Game *p_game);
void draw_score(const Game *p_game);
void draw_high_score(const Game *p_game);
void draw_round(const Game *p_game);
void draw_buffs(const Game *p_game);

void draw_game_over_screen(const Game *p_game);
void draw_new_record_screen(const Game *p_game);

#endif