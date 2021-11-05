CC = gcc
INC = ../../global/
LIB = -lSDL2main -lSDL2 -lSDL2_ttf

SRC = *.c $(INC)*.c
OBJ = *.o
OUT = test

all:
	$(MAKE) build
	$(MAKE) clean
	$(MAKE) run

build:
	$(CC) -I$(INC) -c $(SRC)
	$(CC) -o $(OUT) $(OBJ) $(LIB)

clean:
	rm *.o

run:
	./$(OUT)
