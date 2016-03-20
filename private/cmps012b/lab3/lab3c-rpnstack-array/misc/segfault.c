// $Id: segfault.c,v 1.24 2014-04-15 18:40:30-07 - - $

// Illustrate a segfault.

#include <stdio.h>

int main (int argc, char **argv) {
   (void) argc; // warning: unused parameter 'argc' [-Wunused-parameter]
   for (int i = 0;; ++i) {
      printf ("argv[%d]=\"%s\"\n", i, argv[i]);
      fflush (NULL);
   }
}

/*
//TEST// env -i FOO=value1 BAR=value2 \
//TEST//    valgrind --leak-check=full --show-reachable=yes \
//TEST//       ./segfault arg1 arg2 >segfault.out 2>segfault.err
//TEST// for file in segfault.out segfault.err; do
//TEST//    more $file </dev/null; echo ""
//TEST// done >segfault.lis
//TEST// rm segfault.out segfault.err
//TEST// mkpspdf segfault.ps segfault.c* segfault.lis
*/

