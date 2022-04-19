AUFGABE_1 = Aufgabe1
AUFGABE_2 = Aufgabe2
AUFGABE_3 = Aufgabe3

Varibals = -g -o

all: Aufgabe1.c Aufgabe2.c Aufgabe3.c
	gcc $(Varibals) $(AUFGABE_1) Aufgabe1.c
	gcc $(Varibals) $(AUFGABE_2) Aufgabe2.c
	gcc $(Varibals) $(AUFGABE_3) Aufgabe3.c

aufgabe1: Aufgabe1.c
	gcc $(Varibals) $(AUFGABE_1) Aufgabe1.c

Aufgabe2: Aufgabe2.c
	gcc $(Varibals) $(AUFGABE_2) Aufgabe2.c

aufgabe3: Aufgabe3.c
	gcc $(Varibals) $(AUFGABE_3) Aufgabe3.c

clean:
	rm -rf $(AUFGABE_1) $(AUFGABE_2) $(AUFGABE_3)
