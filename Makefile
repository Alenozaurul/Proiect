COMPILER = gcc

FLAGS = -Wall 

TARGET = main

all: $TARGET 

$TARGET:
	$(COMPILER) $(FLAGS) -o $(TARGET).x $(TARGET).c

clean:
	$(RM) $(TARGET).x
