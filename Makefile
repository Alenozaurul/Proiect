MAIN = main

CC = g++ 

FLAGS = -Wall

all: $(MAIN)
	$(CC) $(MAIN).c $(FLAGS) -lSDL2 -o $(MAIN)
 
clean:
	rm $(MAIN)
