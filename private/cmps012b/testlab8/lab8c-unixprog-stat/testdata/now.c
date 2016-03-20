// $Id: now.c,v 1.6 2016-03-02 15:07:54-08 - - $

// Command works like date(1).

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (void) {
   time_t now = time (NULL);
   printf ("now = %ld\n", now);
   struct tm tm_now;
   localtime_r (&now, &tm_now);
   char buffer[64];
   strftime (buffer, sizeof buffer, "%a %b %e %T %Z %Y", &tm_now);
   printf ("%s\n", buffer);
   return EXIT_SUCCESS;
}
