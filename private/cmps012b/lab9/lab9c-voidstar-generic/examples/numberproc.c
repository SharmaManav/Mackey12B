// $Id: numberproc.c,v 1.1 2014-05-15 20:57:59-07 - - $

//
// Example of processing an array of numbers.
//

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <values.h>

#include "genericlib.h"


double numbers[] = {6.02e23, 287, -472, 0, 6e-22, MAXDOUBLE};

void log10ify (void *number) {
   TRACE ("%.15g", *(double*)number);
   double *value = (double*) number; 
   *value = log10 (*value);
}

void printnum (void *number) {
   TRACE ("%.15g", *(double*)number);
}

int main (void) {

   size_t numberdim = sizeof numbers / sizeof *numbers;
   process (numbers, numberdim, sizeof *numbers, printnum);
   (void) printf ("\n");

   process (numbers, numberdim, sizeof *numbers, log10ify);
   (void) printf ("\n");

   process (numbers, numberdim, sizeof *numbers, printnum);
   (void) printf ("\n");

   return 0;
}
