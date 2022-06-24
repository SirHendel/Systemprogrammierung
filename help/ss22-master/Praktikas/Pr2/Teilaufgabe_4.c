#include <stdio.h>

struct test {
  char c;
  short s;
  int x;
};

int main() {
  struct test einTest;

  einTest.c = 'z';
  einTest.s = 0x1000;
  einTest.x = 1000000;

  printf("c: %c s: %d x: %d\n", einTest.c, einTest.s, einTest.x);


  printf("Adresse von c: %p\n", &einTest.c);
  printf("Adresse von s: %p\n", &einTest.s);
  printf("Adresse von x: %p\n", &einTest.x);
  printf("Groesse von einTest: %ld", sizeof(einTest));

  return 0;
}
