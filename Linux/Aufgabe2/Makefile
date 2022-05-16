APPNAME = out

$(APPNAME): Testaufgabe2.o 
	gcc -g Testaufgabe2.o -o $(APPNAME) -L. libmylib.a

Testaufgabe2.o: Testaufgabe2.c
	gcc -g -Wall -c Testaufgabe2.c -o Testaufgabe2.o
clean:
	rm -f out Testaufgabe2.o