#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int compareStrings(const void *stackA, const void *stackB)
{
  const char *a=*(const char**)stackA;
  const char *b=*(const char**)stackB;
  return strcmp(a,b);
}

int compareStringslength(const void *stackA, const void *stackB)
{
  const char *a=*(const char**)stackA;
  const char *b=*(const char**)stackB;
  if(strlen(a) == strlen(b)){return 0;}
  else if(strlen(a)<strlen(b)){return 1;}
  else { return -1;}
}

int main(int argv,char* argc[]){
    int length = argv-1;
    printf("Anzahl der Variablen: %d\n",length);
    //sort alp
    char** feld = (char**)malloc(length * sizeof(char*));
    feld = argc;

    qsort((char*) feld, argv, sizeof(*feld), compareStrings);
    printf("Sort \n");
    for(int i = 1;i<argv;i++){
        printf("Variablen %d: %s \n",i, feld[i]);
    }
    //sort length
    qsort((char*) feld, argv, sizeof(*feld), compareStringslength);
    printf("Sort by length \n");
    for(int i = 1;i<argv;i++){
        printf("Variablen %d: %s \n",i, feld[i]);
    }

    free(feld);
    feld = NULL;
}