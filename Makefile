MAIN = main.c
EXE = main

LINKS = gamemodes.c sdl.c

CC = gcc

FLAGS = -Wall -lSDL2



all: $(MAIN) $(LINKS) 
	$(CC) $(MAIN) $(LINKS) $(FLAGS) -o $(EXE)
	./$(EXE)

main.c: gamemodes.c
	$(CC) -c $(MAIN) $(FLAGS)

gamemodes.c: sdl.c
	$(CC) -c gamemodes.c $(FLAGS)

sdl.c:
	$(CC) -c sdl.c $(FLAGS)

clean:
	rm main main.o
