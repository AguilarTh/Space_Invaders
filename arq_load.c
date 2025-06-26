#include "arq_load.h"
#include "arq_game.h"

void loads(Game *p_game){

    // -- FONTE -- 1

	p_game->font_grande = al_load_ttf_font("assets/fonts/font_space.ttf", 50, 0);  
    p_game->font = al_load_ttf_font("assets/fonts/font_space.ttf", 35, 0);   
	p_game->font_pequena = al_load_ttf_font("assets/fonts/font_space.ttf", 20, 0);  
	
	// -- PNG -- 14

	p_game->sprites.icone_janela = al_load_bitmap("assets/sprites/icone_janela.png");
	p_game->sprites.background_menu = al_load_bitmap("assets/sprites/background_menu.png");
	p_game->sprites.background_jogo_1 = al_load_bitmap("assets/sprites/background_jogo_1.png");
	p_game->sprites.background_jogo_2 = al_load_bitmap("assets/sprites/background_jogo_2.png");
	p_game->sprites.background_jogo_3 = al_load_bitmap("assets/sprites/background_jogo_3.png");
	p_game->sprites.background_jogo_4 = al_load_bitmap("assets/sprites/background_jogo_4.png");

    p_game->sprites.nave_1 = al_load_bitmap("assets/sprites/ship_1.png");
	p_game->sprites.nave_2 = al_load_bitmap("assets/sprites/ship_2.png");
	p_game->sprites.nave_3 = al_load_bitmap("assets/sprites/ship_3.png");
	p_game->sprites.nave_4 = al_load_bitmap("assets/sprites/ship_4.png");
	p_game->sprites.nave_5 = al_load_bitmap("assets/sprites/ship_5.png");

	p_game->sprites.nave_life = al_load_bitmap("assets/sprites/hearts.png");
	p_game->sprites.shot = al_load_bitmap("assets/sprites/shot_sprite.png");
	p_game->sprites.enemy = al_load_bitmap("assets/sprites/enemy_sprite_new.png");
	p_game->sprites.enemy_shot = al_load_bitmap("assets/sprites/enemy_shot_sprite.png");
	p_game->sprites.explosao = al_load_bitmap("assets/sprites/explosao.png");
	p_game->sprites.object_A = al_load_bitmap("assets/sprites/object_um_A.png");
	p_game->sprites.object_B = al_load_bitmap("assets/sprites/object_um_B.png");
	p_game->sprites.object_C = al_load_bitmap("assets/sprites/object_um_C.png");
	p_game->sprites.powerUp_Life = al_load_bitmap("assets/sprites/powerUp_Life.png");
	p_game->sprites.powerUp_Imunidade = al_load_bitmap("assets/sprites/powerUp_Tiros.png");
	p_game->sprites.powerUp_Vel = al_load_bitmap("assets/sprites/powerUp_Vel.png");
	p_game->sprites.shield = al_load_bitmap("assets/sprites/shield.png");

    // -- AUDIO -- 8

	// al_play_sample(p_game->audio.tiro_nave, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	p_game->audio.tiro_nave = al_load_sample("assets/audios/tiro_nave.wav");
	p_game->audio.tiro_enemy = al_load_sample("assets/audios/tiro_enemy.wav");
	p_game->audio.explosao_nave = al_load_sample("assets/audioss/explosao_nave.wav");
	p_game->audio.explosao_inimigo = al_load_sample("assets/audios/explosao.wav");
	p_game->audio.explosao_objeto =al_load_sample("assets/audios/explosao_objeto.wav");
    p_game->audio.powerup_life =al_load_sample("assets/audios/powerup_life.wav");
    p_game->audio.powerup_imm =al_load_sample("assets/audios/powerup_immunity.wav");
    p_game->audio.powerup_vel =al_load_sample("assets/audios/powerup_vel.wav");
	p_game->audio.dmg_nave =al_load_sample("assets/audios/dmg_nave.wav");

	// -- MUSICA -- 2

	p_game->audio.musica_jogo = al_load_audio_stream("assets/audios/musica_jogo.ogg", 4, 2048);
	p_game->audio.musica_menu = al_load_audio_stream("assets/audios/musica_menu.ogg", 4, 2048);

	// ---- configuracao de som ----
	al_set_audio_stream_gain(p_game->audio.musica_menu, 0.1);
	al_set_audio_stream_gain(p_game->audio.musica_jogo, 0.025);

	al_attach_audio_stream_to_mixer(p_game->audio.musica_menu, al_get_default_mixer());
	al_attach_audio_stream_to_mixer(p_game->audio.musica_jogo, al_get_default_mixer());

	al_set_audio_stream_playmode(p_game->audio.musica_menu, ALLEGRO_PLAYMODE_LOOP);
	al_set_audio_stream_playmode(p_game->audio.musica_jogo, ALLEGRO_PLAYMODE_LOOP);
	
}

void destroys(Game *p_game){

    // -- FONT --

    al_destroy_font(p_game->font);

    // -- PNG --

	al_destroy_bitmap(p_game->sprites.icone_janela);
    al_destroy_bitmap(p_game->sprites.background_jogo_1);
	al_destroy_bitmap(p_game->sprites.background_jogo_2);
	al_destroy_bitmap(p_game->sprites.background_jogo_3);
	al_destroy_bitmap(p_game->sprites.background_jogo_4);
	al_destroy_bitmap(p_game->sprites.nave_1);
	al_destroy_bitmap(p_game->sprites.nave_2);
	al_destroy_bitmap(p_game->sprites.nave_3);
	al_destroy_bitmap(p_game->sprites.nave_4);
	al_destroy_bitmap(p_game->sprites.nave_5);
	al_destroy_bitmap(p_game->sprites.shot);
	al_destroy_bitmap(p_game->sprites.enemy);
	al_destroy_bitmap(p_game->sprites.enemy_shot);
	al_destroy_bitmap(p_game->sprites.nave_life);
	al_destroy_bitmap(p_game->sprites.explosao);
	al_destroy_bitmap(p_game->sprites.background_menu);
	al_destroy_bitmap(p_game->sprites.object_A);
	al_destroy_bitmap(p_game->sprites.object_B);
	al_destroy_bitmap(p_game->sprites.object_C);
	al_destroy_bitmap(p_game->sprites.powerUp_Life);
	al_destroy_bitmap(p_game->sprites.powerUp_Imunidade);
	al_destroy_bitmap(p_game->sprites.powerUp_Vel);
	al_destroy_bitmap(p_game->sprites.shield);

	// -- AUDIO --

	al_destroy_sample(p_game->audio.tiro_nave);
	al_destroy_sample(p_game->audio.tiro_enemy);
	al_destroy_sample(p_game->audio.explosao_inimigo);
	al_destroy_sample(p_game->audio.explosao_objeto);
	al_destroy_sample(p_game->audio.explosao_nave);
    al_destroy_sample(p_game->audio.powerup_life);
    al_destroy_sample(p_game->audio.powerup_imm);
    al_destroy_sample(p_game->audio.powerup_vel);
	al_destroy_sample(p_game->audio.dmg_nave);

    al_destroy_audio_stream(p_game->audio.musica_jogo);
	al_destroy_audio_stream(p_game->audio.musica_menu);
}