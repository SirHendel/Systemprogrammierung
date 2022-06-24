#include <stdio.h>
#include <stdlib.h>

/*
  Siehe Kommentierung Teilaufgabe_1.c
  -> Identisch
*/
int main() {
  char inp;
  do {
    printf("Eingabe: ");
    inp = getchar();

    if(inp != 'Q') 
      printf("%c %03d %#04x\n", inp, inp, inp);

    while(getchar() != '\n') { }
  } while(inp != 'Q');

  return EXIT_SUCCESS;
}
