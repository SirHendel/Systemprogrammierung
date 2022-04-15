#include <stdio.h>
#include <stdlib.h>

/*void zeigeFeld(int *feld, int anzahl){
    printf("Index \t AdresseWert \t Wert \n");
    printf( "================== \n");
    for(int i = 0;i<anzahl;i++){
        printf(i , feld[i], feld[i], "\n");
    }
}*/

int main(int args, char *argc[]){
    /*int length = atoi(argc[1]);
    int *feld;
    feld = (int *) malloc(length);
    int t= 33;
    srand(t);

    for(int i = 0;i<length;i++){
        *feld = i;
    }

    free(feld);
    zeigeFeld(feld,length);*/
    printf("\ncmdline args count=%d", args);
    printf("\nArgument %s", argc[1]);
    printf("\n");
    return 0;
}
/*gcc Aufgabe1.c -o main
 .\main.exe argumente 
*/