// $Id: argv.c,v 1.6 2013-09-25 14:08:47-07 - - $

//
// NAME
//    argv - display the argument vector
//
// SYNOPSIS
//    argv [operands...]
//
// DESCRIPTION
//    Whatever arguments are given are printed out.
//

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
   for (int argi = 0; argi < argc; ++argi) {
      printf ("argv[%d]=(%s)\n", argi, argv[argi]);
   }
   return EXIT_SUCCESS;
}

//TEST// ./argv hello world foo bar baz >argv.lis1 2>&1
//TEST// ./argv *.c >argv.lis2 2>&1
//TEST// mkpspdf argv.ps argv.c* argv.lis?

