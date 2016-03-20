// $Id: strftime.c,v 1.22 2015-02-27 14:04:31-08 - - $

// Show various strftime(3) formats.

#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define PRINT_TM(TM) printf ("tm." #TM " = %d\n", tm.TM);

int main (int argc, char** argv) {
   (void) argc; // warning: unused parameter 'argc'
   printf ("argv[0] = %s\n", argv[0]);

   char* locale = setlocale (LC_CTYPE, "");
   if (locale) printf ("locale = \"%s\"\n", locale);

   struct timeval timeval;
   gettimeofday (&timeval, NULL);
   printf ("timeofday = %ld.%06ld\n", timeval.tv_sec, timeval.tv_usec);

   struct tm tm;
   localtime_r (&timeval.tv_sec, &tm);
   printf ("tm.tm_sec = %d, ", tm.tm_sec);
   printf ("tm.tm_min = %d, ", tm.tm_min);
   printf ("tm.tm_hour = %d\n", tm.tm_hour);
   printf ("tm.tm_mday = %d, ", tm.tm_mday);
   printf ("tm.tm_mon = %d, ", tm.tm_mon);
   printf ("tm.tm_year = %d\n", tm.tm_year);
   printf ("tm.tm_wday = %d, ", tm.tm_wday);
   printf ("tm.tm_yday = %d, ", tm.tm_yday);
   printf ("tm.tm_isdst = %d\n", tm.tm_isdst);

   for (int ch = 'a'; ch <= 'z'; ++ch) {
      char fmt[256];
      sprintf (fmt, "%%%%%c = \"%%%c\", %%%%%c = \"%%%c\"",
               ch, ch, ch - 32, ch - 32);
      char buffer[1024];
      strftime (buffer, sizeof buffer, fmt, &tm);
      printf ("%s\n", buffer);
   }     

   return EXIT_SUCCESS;
}
