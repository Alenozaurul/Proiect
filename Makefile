MAIN = side
EXE = side

CC = gcc

HEADERS = sdlhead

FLAGS = -Wall -lSDL2

all: $(MAIN).c  $(HEADERS).c
	$(CC) $(MAIN).c $(FLAGS) $(HEADERS).c -o $(MAIN)

	./$(EXE)

clean:
	rm $(MAIN)
