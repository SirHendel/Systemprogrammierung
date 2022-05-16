APPNAME = out

$(APPNAME): Aufgabe3.o 
	gcc -g Aufgabe3.o -o $(APPNAME) -L. libmylib.a

Aufgabe3.o: Aufgabe3.c
	gcc -g -Wall -c Aufgabe3.c -o Aufgabe3.o
clean:
	rm -f out Aufgabe3.o