CC = gcc
LIB = -lpthread

# Server
S_SRC = server.c
S_OBJ = server.o
S_OUT = server

all:
	$(MAKE) build
	$(MAKE) clean

build:
	$(CC) -c $(S_SRC)
	$(CC) -o $(S_OUT) $(S_OBJ) $(LIB)

clean:
	rm *.o
