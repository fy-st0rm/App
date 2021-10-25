CC = gcc
LIB = -lSDL2main -lSDL2 -lSDL2_ttf

SRC = *.c
OBJ = *.o
OUT = test

all:
	$(MAKE) build
	$(MAKE) clean
	$(MAKE) run

build:
	$(CC) -c $(SRC)
	$(CC) -o $(OUT) $(OBJ) $(LIB)

clean:
	rm *.o

run:
	./$(OUT)
