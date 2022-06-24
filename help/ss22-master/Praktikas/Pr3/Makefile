APPNAME = out

$(APPNAME): kreis.o flaeche.o
	gcc -g -o $(APPNAME) kreis.o flaeche.o

flaeche.o: flaeche.c
	gcc -g -Wall -c -o flaeche.o flaeche.c -lm
