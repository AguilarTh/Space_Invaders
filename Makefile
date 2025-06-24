# Makefile para compilar main.c

CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = test

# SRC = Lista de todos os arquivos fontes (.c) = Sempre colocar um modulo novo aq:

SRC = main.c arq_nave.c arq_enemy.c arq_shot.c arq_colisoes.c arq_enemy_shot.c arq_highscore.c arq_object.c \
	  arq_jogo_funcoes_base.c arq_menu.c arq_display.c arq_explosao.c arq_powerup.c arq_pause.c arq_load.c
INCLUDE = -IC:/msys64/mingw64/include
LIBDIR = -LC:/msys64/mingw64/lib
LIBS = -lallegro -lallegro_main -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_image -lallegro_audio -lallegro_acodec -lallegro_color -lallegro_memfile -lallegro_physfs -lallegro_video

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(TARGET).exe $(SRC) $(LIBDIR) $(LIBS)

clean:
	del $(TARGET).exe 2>nul || true

.PHONY: all clean
