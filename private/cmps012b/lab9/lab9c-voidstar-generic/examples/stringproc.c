// $Id: stringproc.c,v 1.2 2015-02-26 18:24:46-08 - - $

//
// Example of using genericlib to process strings.
// Array of strings with two processing functions.
//

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "genericlib.h"

static char *strings[] = {"hello", "world", "foo", "bar", "baz", "qux"};

void strdupthem (void *string) {
   TRACE ("%p->\"%s\"", string, *(char**)string);
   char **chars = (char**) string; 
   *chars = strdup (*chars);
}

void capitalize (void *string) {
   TRACE ("%p->\"%s\"", string, *(char**)string);
   for (char *chars = *(char**) string; *chars != '\0'; ++chars) {
      *chars = toupper (*chars);
   }
}

void printstr (void *string) {
   TRACE ("%p->\"%s\"", string, *(char**)string);
}

void freestr (void *string) {
   TRACE ("%p->\"%s\"", string, *(char**)string);
   char *str = *(char**) string; 
   free (str);
   str = NULL; 
}

int main (void) {

   size_t stringdim = sizeof strings / sizeof *strings;
   process (strings, stringdim, sizeof *strings, printstr);
   (void) printf ("\n");
   process (strings, stringdim, sizeof *strings, strdupthem);
   (void) printf ("\n");
   process (strings, stringdim, sizeof *strings, capitalize);
   (void) printf ("\n");
   process (strings, stringdim, sizeof *strings, printstr);
   (void) printf ("\n");
   process (strings, stringdim, sizeof *strings, freestr);
   (void) printf ("\n");

   return 0;
}

