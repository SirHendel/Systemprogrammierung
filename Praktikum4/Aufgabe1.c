#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void zeigeFeld(int *feld, const int anzahl){
    printf("Index \t AdresseWert \t Wert \n");
    printf( "================================= \n");
    for(int i = 0;i<anzahl;i++){
        printf("%5d \t %7d \t  %7d \n", i , &feld[i], feld[i]);
    }
}

int main(int args, char *argc[]){
    int length = atoi(argc[1]);
    //printf("\n%d", length);
    int *feld = malloc(length * sizeof(int));
    
    //online found rand fuction
    time_t t;
    srand((unsigned) time(&t));


    for(int i = 0;i<length;i++){
        feld[i] = (int)(rand()) % 1000000;
    }


    zeigeFeld(feld,length);
    free(feld);
    feld = NULL;
    
    

    return 0;
}
/*gcc Aufgabe1.c -o main
 .\main.exe argumente 
*/