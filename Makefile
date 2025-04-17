MAIN = main.c
EXE = main

LINKS = gamemodes.c sdl.c action.c

CC = gcc

FLAGS = -Wall -lSDL2 -lSDL2_ttf



all: $(MAIN) $(LINKS) 
	$(CC) $(EXE).c $(LINKS) $(FLAGS) -o $(EXE)
	./$(EXE)

main.c: gamemodes.c
	$(CC) -c $(MAIN) $(FLAGS)

gamemodes.c: sdl.c
	$(CC) -c gamemodes.c $(FLAGS)

sdl.c: action.c
	$(CC) -c sdl.c $(FLAGS)

action.c: 
	$(CC) -c action.c $(FLAGS)

clean:
	rm main
