APPNAME=starter

$(APPNAME): main.o
	gcc -g -o $(APPNAME) main.o

main.o: main.c
	gcc -Wall -g -c main.c

clean:
	rm -f $(APPNAME) *.o
	rm -f *~
