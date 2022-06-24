CC = /usr/bin/gcc
SRC = Server.c Client.c
BIN = $(SRC:%.c=%.out)

all: Server Client
		
Server: Server.c
	gcc -Wall -g Server.c -o Server.out

Client: Client.c
	gcc -Wall -g Client.c -o Client.out

clean:
	rm -rf $(BIN)