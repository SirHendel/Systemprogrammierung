APPNAME = out

$(APPNAME): Aufgabe1.o 
	gcc -g Aufgabe1.o -o $(APPNAME)  

Aufgabe1.o: Aufgabe1.c
	gcc -g -Wall -c Aufgabe1.c  -o Aufgabe1.o 
clean:
	rm -f out Aufgabe1.o