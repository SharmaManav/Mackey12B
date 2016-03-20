//$Id: environ.c,v 1.1 2016-02-10 21:46:08-08 - - $
//Manav Sharma msharma7

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

extern char **environ;

void main() {
    for (int i = 0; environ[i] != NULL; i++){
        printf("%s\n", environ[i]);
       }
      return 0;
  }
