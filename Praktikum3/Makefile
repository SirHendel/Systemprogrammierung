APPNAME = kreis
OPTIONS = -g -o 

$(APPNAME): kreis.o flaeche.o
	gcc $(OPTIONS) $(APPNAME) kreis.o flaeche.o 

kreis.o: kreis.c
	gcc -g -Wall -c -o kreis.o kreis.c -lm

flaeche.o: flaeche.c
	gcc -g -Wall -c -o flaeche.o flaeche.c -lm



# -Wall enables all compiler's warning messages
# -c compiles source files without linking.