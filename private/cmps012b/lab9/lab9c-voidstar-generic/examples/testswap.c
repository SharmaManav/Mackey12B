// $Id: testswap.c,v 1.2 2014-05-15 20:37:32-07 - - $

//
// Example program showing testing of genericlib.
//

#include <stdio.h>
#include <string.h>

#include "genericlib.h"

int main (int argc, char** argv) {
   (void) argc;
   printf ("%s:\n\n", argv[0]);

   double d1 = 3;
   double d2 = 6;
   printf ("d1 = %g, d2 = %g\n", d1, d2);
   swapm (&d1, &d2, sizeof (double));
   printf ("d1 = %g, d2 = %g\n\n", d1, d2);

   char s1[] = "Hello, World.";
   char s2[] = "This is a test of swapa.";
   printf ("s1 = \"%s\", s2 = \"%s\"\n", s1, s2);
   swapa (s1, s2, strlen (s1));
   printf ("s1 = \"%s\", s2 = \"%s\"\n\n", s1, s2);

   return 0;
}
