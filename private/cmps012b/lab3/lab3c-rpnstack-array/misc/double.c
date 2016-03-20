// $Id: double.c,v 1.31 2016-01-13 22:04:46-08 - - $

//
// NAME
//    double - print out information about double numbers
//

#include <libgen.h>
#include <locale.h>
#include <stdio.h>
#include <values.h>

int main (int argc, char **argv) {
   (void) argc; // avoid: warning: unused parameter 'argc'
   char *locale = setlocale (LC_NUMERIC, "en_US");
   if (locale == NULL) {
      fprintf (stderr, "%s: %s: %s\n", basename (argv[0]),
               "setlocale (LC_NUMERIC, \"en_US\")", "failed\n");
   }else {
      printf ("Locale set to %s\n", locale);
   }
   printf ("DBL_DIG = %d\n", DBL_DIG);
   printf ("DBL_EPSILON = %.15g\n", DBL_EPSILON);
   printf ("DBL_MANT_DIG = %d\n", DBL_MANT_DIG);
   printf ("DBL_MAX_10_EXP = %d\n", DBL_MAX_10_EXP);
   printf ("DBL_MAX = %.15g\n", DBL_MAX);

   printf ("diameter of the universe = %g meters\n", 8.8e26);

   double dollars = 1.00;
   while (dollars + 0.01 > dollars) dollars *= 2;
   printf ("dollars = $%'22.2f = $%g\n", dollars, dollars);

   double us_debt = 18900819907288.77;
   printf ("US debt = $%'22.2f = $%g\n", us_debt, us_debt);
   printf ("          http://www.brillig.com/debt_clock/\n");
   printf ("          14 Jan 2016 at 05:53:18 AM GMT)\n");
   return 0;
}

//TEST// ./double >double.lis 2>&1
//TEST// mkpspdf double.ps double.c* double.lis*

