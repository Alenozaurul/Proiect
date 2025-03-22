MAIN = main

CC = gcc 

SDL_CFLAGS = $(shell pkg-config --cflags sdl2)
SDL_LIBS = $(shell pkg-config --libs sdl2)

FLAGS = -Wall 

all: $(MAIN)
	$(CC) $(FLAGS) $(MAIN).c $(SDLL_CFLAGS) -o $(MAIN) $(SDL_LIBS) 
 
clean:
	rm $(MAIN)
