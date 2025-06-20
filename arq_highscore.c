#include "arq_highscore.h"
#include "arq_game.h"
#include <stdio.h>

#define HIGHSCORE_FILE "highscore.dat"

// !!!! MELHORIA -> CRIAR UMA TELA DE GAMEOVER E COLOCAR ESSA VERIFICACAO NELA

int load_highscore() {
    FILE *file = fopen(HIGHSCORE_FILE, "r"); 
    int highscore = 0;

    if (file == NULL) { // Se o arquivo não existe, o recorde é 0
        return 0;
    }

    fscanf(file, "%d", &highscore); 
    fclose(file);
    return highscore;
}

void save_highscore(int new_highscore) {
    FILE *file = fopen(HIGHSCORE_FILE, "w"); // "w" = write (escrever/sobrescrever)

    if (file == NULL) {
        fprintf(stderr, "Erro ao salvar o highscore!\n");
        return;
    }

    fprintf(file, "%d", new_highscore); // Escreve o novo recorde no arquivo
    fclose(file);
}