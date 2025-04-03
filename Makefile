MAIN = main
EXE = main

CC = gcc

FLAGS = -Wall -lSDL2

all: $(MAIN).c 
	$(CC) $(MAIN).c $(FLAGS) -o $(EXE)
	./$(EXE)

clean:
	rm $(EXE)
