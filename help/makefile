#Autor: Alex Leidwein
CC = /usr/bin/gcc
SRC = server.c client.c
BIN = $(SRC:%.c=%.out)

all: server client
		
server: server.c
	gcc server.c -o server.out

client: client.c
	gcc client.c -o client.out

.PHONY: clean
clean:
	rm -rf $(BIN)