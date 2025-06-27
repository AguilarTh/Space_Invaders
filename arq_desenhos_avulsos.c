#include "arq_desenhos_avulsos.h"
#include "arq_game.h"

void draw_scenario(const Game *p_game){

    al_clear_to_color(al_map_rgb(0, 0, 0)); // LIMPA A TELA

    float bg_w = al_get_bitmap_width(p_game->sprites.background_jogo_atual);
    float bg_h = al_get_bitmap_height(p_game->sprites.background_jogo_atual);

    al_draw_scaled_bitmap(p_game->sprites.background_jogo_atual, 0, 0, bg_w, bg_h, 0, 0, SCREEN_W, SCREEN_H, 0);
}

void draw_score(const Game *p_game){
	
	al_draw_textf(p_game->font_pequena, al_map_rgb(255, 255, 255), 10, 10, ALLEGRO_ALIGN_LEFT, "Score: %d", p_game->score);
}

void draw_round(const Game *p_game){

    al_draw_textf(p_game->font, al_map_rgb(255, 255, 255), SCREEN_W / 2, 10, ALLEGRO_ALIGN_CENTRE, "%dº Round", p_game->round_atual);
}

void draw_high_score(const Game *p_game){

	al_draw_textf(p_game->font_pequena, al_map_rgb(255, 255, 255), SCREEN_W - 10, 10, ALLEGRO_ALIGN_RIGHT, "Recorde: %d", p_game->high_score);
}

void draw_buffs(const Game *p_game){

    float sprite_shield_w = al_get_bitmap_width(p_game->sprites.shield);
    float sprite_shield_h = al_get_bitmap_height(p_game->sprites.shield);

    float new_sprite_w = POWERUP_TIMER_W;
	float new_sprite_h = POWERUP_TIMER_H;

    float new_sprite_shield_w = NAVE_W;
	float new_sprite_shield_h = NAVE_W * 0.55;

	float draw_x = SCREEN_W - ( POWERUP_TIMER_W + 10);
	float draw_y = SCREEN_H - 50;

    float draw_shield_x = p_game->nave.x - NAVE_W / 2;
    float draw_shield_y = (SCREEN_H - FLOOR_H) - ( new_sprite_shield_h + 25 );

    if(p_game->tempo_buff_imunidade_restante > 0){
        al_draw_scaled_bitmap(p_game->sprites.powerUp_Imunidade, 0, 0, 86, 86, draw_x, draw_y, new_sprite_w, new_sprite_h, 0);
        al_draw_scaled_bitmap(p_game->sprites.shield, 0, 0, sprite_shield_w, sprite_shield_h, draw_shield_x, draw_shield_y, new_sprite_shield_w, new_sprite_shield_h, 0);
    }

     if (p_game->tempo_buff_velocidade_restante > 0) {
        al_draw_scaled_bitmap(p_game->sprites.powerUp_Vel, 0, 0, 86, 86, draw_x - ( POWERUP_TIMER_W + 10), draw_y, new_sprite_w, new_sprite_h, 0);
    }
}

void draw_game_over_screen(const Game *p_game){
    
    al_clear_to_color(al_map_rgb(0, 0, 0)); 

    float bg_w = al_get_bitmap_width(p_game->sprites.background_final);
    float bg_h = al_get_bitmap_height(p_game->sprites.background_final);

    al_draw_scaled_bitmap(p_game->sprites.background_final, 0, 0, bg_w, bg_h, 0, 0, SCREEN_W, SCREEN_H, 0);

    al_draw_text(p_game->font_grande, al_map_rgb(255, 0, 0),
                 SCREEN_W / 2, SCREEN_H / 2 - 150, ALLEGRO_ALIGN_CENTER, "FIM DE JOGO!");
    al_draw_textf(p_game->font, al_map_rgb(255, 255, 255),
                  SCREEN_W / 2, SCREEN_H / 2 + 20, ALLEGRO_ALIGN_CENTER, "Pontuação Final: %d", p_game->score);
    al_draw_textf(p_game->font_pequena, al_map_rgb(200, 200, 200),
                  SCREEN_W / 2, SCREEN_H / 2 + 70, ALLEGRO_ALIGN_CENTER, "Recorde Atual: %d", p_game->high_score);
    al_draw_text(p_game->font_pequena, al_map_rgb(200, 200, 200),
                 SCREEN_W / 2, SCREEN_H / 2 + 190, ALLEGRO_ALIGN_CENTER, "Pressione 'R' para Jogar Novamente");
    al_draw_text(p_game->font_pequena, al_map_rgb(200, 200, 200),
                 SCREEN_W / 2, SCREEN_H / 2 + 220, ALLEGRO_ALIGN_CENTER, "Pressione 'ESC' para Voltar ao Menu");

    al_flip_display();
}

void draw_new_record_screen(const Game *p_game){
    al_clear_to_color(al_map_rgb(0, 0, 0)); 

    float bg_w = al_get_bitmap_width(p_game->sprites.background_final);
    float bg_h = al_get_bitmap_height(p_game->sprites.background_final);

    al_draw_scaled_bitmap(p_game->sprites.background_final, 0, 0, bg_w, bg_h, 0, 0, SCREEN_W, SCREEN_H, 0);

    al_draw_text(p_game->font_grande, al_map_rgb(0, 255, 0),
                 SCREEN_W / 2, SCREEN_H / 2 - 100, ALLEGRO_ALIGN_CENTER, "NOVO RECORDE!");
    al_draw_textf(p_game->font, al_map_rgb(255, 255, 255),
                  SCREEN_W / 2, SCREEN_H / 2 + 20, ALLEGRO_ALIGN_CENTER, "Pontuação Final: %d", p_game->high_score);
    al_draw_text(p_game->font_pequena, al_map_rgb(200, 200, 200),
                 SCREEN_W / 2, SCREEN_H / 2 + 160, ALLEGRO_ALIGN_CENTER, "Pressione 'R' para Jogar Novamente");
    al_draw_text(p_game->font_pequena, al_map_rgb(200, 200, 200),
                 SCREEN_W / 2, SCREEN_H / 2 + 190, ALLEGRO_ALIGN_CENTER, "Pressione 'ESC' para Voltar ao Menu");
    
    al_flip_display();
}