#include <stdio.h>
#include <stdlib.h>

struct test {
        char c;
        short s;
        int x;
};

int main(int argv,char *argc[]){
    struct test varstruct;
    varstruct.c = 'z';
    varstruct.s = 0x1000;
    varstruct.x = 1000000;
    printf("Der struct test hat eine variable c mid %c  diese belegt %d Adresse im Speicher \n",varstruct.c,&varstruct.c);
    printf("Der struct test hat eine variable c mid %d  diese belegt %d Adresse im Speicher \n",varstruct.s,&varstruct.s);
    printf("Der struct test hat eine variable c mid %d  diese belegt %d Adresse im Speicher \n",varstruct.x,&varstruct.x);
    printf("Der struct test belegt %d im Speicher", sizeof(varstruct));
    unsigned *varchar[3];


    return 0;
}