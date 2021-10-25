CC = gcc

# Server
S_DIR = Server
S_SRC = $(S_DIR)/server.c
S_OBJ = $(S_DIR)/server.o
S_OUT = $(S_DIR)/server
S_LIB = -lpthread

server:
	$(MAKE) sv_build
	$(MAKE) sv_clean

sv_build:	
	$(CC) -c $(S_SRC)
	mv *.o $(S_DIR)/
	$(CC) -o $(S_OUT) $(S_OBJ) $(S_LIB)

sv_clean:
	rm $(S_DIR)/*.o

# Engine
E_DIR = Client/Engine
E_OBJ_DIR = $(E_DIR)/obj
E_SRC = $(E_DIR)/*.c


engine:
	$(MAKE) eng_build


eng_build:
	$(CC) -c $(E_SRC)
	mv *.o $(E_OBJ_DIR)/

eng_clean:
	rm $(E_OBJ_DIR)/*.o


# Client
C_DIR = Client
C_OBJ_DIR = $(C_DIR)/obj
C_SRC = $(C_DIR)/*.c
C_OBJ = $(C_OBJ_DIR)/*.o
C_LIB = -lSDL2main -lSDL2 -lSDL2_ttf
C_OUT = $(C_DIR)/client

client:
	$(MAKE) client_build

client_build:
	$(CC) -c $(C_SRC)
	mv *.o $(C_OBJ_DIR)/
	cp $(E_OBJ_DIR)/*.o $(C_OBJ_DIR)/
	$(CC) -o $(C_OUT) $(C_OBJ) $(C_LIB)

client_clean:
	rm $(C_OBJ_DIR)/*.o

