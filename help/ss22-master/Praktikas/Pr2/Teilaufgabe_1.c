#include <stdio.h>
#include <stdlib.h>

int main() {
  char inp;
  do {
    printf("Eingabe: ");
    inp = getchar(); // char aus stdin einlesen

    // Falls es kein Q ist, gebe die gewuenschen 
    // Informationen aus.
    if(inp != 'Q') 
      printf("%c %d %x\n", inp, inp, inp); 

    while(getchar() != '\n') { } // Buffer loeschen

  } while(inp != 'Q'); // Beende Schleife, falls Q

  return EXIT_SUCCESS;
}
