MAIN = main.c
EXE = main

LINKS = gamemodes.c sdl.c

CC = gcc

FLAGS = -Wall -lSDL2 -lSDL2_ttf



all: $(MAIN) $(LINKS) 
	$(CC) $(EXE).c $(LINKS) $(FLAGS) -o $(EXE)
	./$(EXE)

main.c: gamemodes.o
	$(CC) -c $(MAIN) $(FLAGS)

gamemodes.c: sdl.o
	$(CC) -c gamemodes.c $(FLAGS)

sdl.c:
	$(CC) -c sdl.c $(FLAGS)

clean:
	rm main
