all: Server Client

Server: Server.o
	gcc -g -o Server Server.o -lm

Client: Client.o
	gcc -g -o Client Client.o 

Server.o: Server.c msg_struct.h
	gcc -g -c Server.c

Client.o: Client.c msg_struct.h
	gcc -g -c Client.c

clean:
	rm -f *~ *.o Server Client
