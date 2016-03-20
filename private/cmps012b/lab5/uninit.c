// $Id: uninit.c,v 1.1 2016-02-10 20:25:14-08 - - $

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
   int *pointer;
   printf ("pointer=%p\n", pointer);
   printf ("*pointer=%d\n", *pointer);
   int foo;
   printf ("foo=%d\n", foo);
}
