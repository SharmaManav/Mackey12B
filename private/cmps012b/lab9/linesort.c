//Manav Sharma msharma7
//Christian Lam ctlam

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inssort.h"
#define ARRAY_SIZE 1000

int check(const void *l, const void *r){
    return strcmp(*(char**)l, *(char**)r);
}

int main() {
    char **array = calloc(ARRAY_SIZE, sizeof(char));
    int num = 0;

    for (int i = 0; i < ARRAY_SIZE; i++){
        char *buffer = calloc(1000, sizeof(char));
        if (scanf("%s", buffer)!=1) {
        free(buffer);
        break;
    }
    num++;

    if (buffer[strlen(buffer) -1] == '\n'){
        buffer[strlen(buffer) -1] == '\0';
    }
    array[i] = strdup(buffer);
    free(buffer);
  }
  printf("\n");

  inssort(array, num, sizeof(char*),check);
  for (int i = 0; i<num; i++){
      printf("%s\n", array[i]);
      free(array[i]);
    }
    free(array);
}
