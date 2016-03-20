// $Id: scanfbug.c,v 1.9 2013-09-25 14:54:29-07 - - $
//
// NAME
//    scanfbug - illustrate bug in scanf.
//
// DESCRIPTION
//    Uses %lg to read and print numbers or errors out for non-numbers.
//    But fails to recognize a lone + or - on input.


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main (void) {
   int exit_status = EXIT_SUCCESS;
   for (;;) {
      double number;
      int scanrc = scanf ("%lg", &number);
      if (scanrc == EOF) break;
      if (scanrc == 1) {
         printf ("number = %.15g\n", number);
      }else {
         exit_status = EXIT_FAILURE;
         char buffer[1024];
         scanrc = scanf ("%1023s", buffer);
         assert (scanrc == 1);
         printf ("bad input \"%s\"\n", buffer);
      }
   }
   return exit_status;
}

/*
//TEST// (echo 34 92.6 123foob + - 38 - + +3 -33 infinity \
//TEST// +infinity -infinity nan - 43 end \
//TEST// | ./scanfbug; echo status = $?) >scanfbug.lis 2>&1
//TEST// mkpspdf scanfbug.ps scanfbug.c* scanfbug.lis
*/

