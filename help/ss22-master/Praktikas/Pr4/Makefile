TEIL_1_NAME = teil1
TEIL_2_NAME = teil2
TEIL_3_NAME = teil3

FLAGS = -Wall -g

all: Teilaufgabe_1.c Teilaufgabe_2.c Teilaufgabe_3.c
	gcc $(FLAGS) -o $(TEIL_1_NAME) Teilaufgabe_1.c
	gcc $(FLAGS) -o $(TEIL_2_NAME) Teilaufgabe_2.c
	gcc $(FLAGS) -o $(TEIL_3_NAME) Teilaufgabe_3.c

teil1: Teilaufgabe_1.c
	gcc $(FLAGS) -o $(TEIL_1_NAME) Teilaufgabe_1.c

teil2: Teilaufgabe_2.c
	gcc $(FLAGS) -o $(TEIL_2_NAME) Teilaufgabe_2.c

teil3: Teilaufgabe_3.c
	gcc $(FLAGS) -o $(TEIL_3_NAME) Teilaufgabe_3.c

clean:
	rm -rf $(TEIL_1_NAME) $(TEIL_2_NAME) $(TEIL_3_NAME)
