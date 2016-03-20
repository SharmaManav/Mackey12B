// $Id: swap.c,v 1.9 2014-02-21 15:43:41-08 - - $

//
// Example of a swap function to exchange two
// areas of memory.
//

#include <alloca.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Swap using a malloc'd temp storage, later free'd.
void swapm (void *this, void *that, size_t size) {
   printf ("%s (%p, %p, %ld)\n", __func__, this, that, size);
   void *temp = malloc (size);
   printf ("%s: temp=%p\n", __func__, temp);
   memcpy (temp, this, size);
   memcpy (this, that, size);
   memcpy (that, temp, size);
   free (temp);
}

// Swap using alloca'd storage, which is on the stack,
// auto freed when the function returns.
void swapa (void *this, void *that, size_t size) {
   printf ("%s (%p, %p, %ld)\n", __func__, this, that, size);
   void *temp = alloca (size);
   printf ("%s: temp=%p\n", __func__, temp);
   memcpy (temp, this, size);
   memcpy (this, that, size);
   memcpy (that, temp, size);
}

int main (int argc, char **argv) {
   (void) argc; // warning: unused parameter 'argc'
   printf ("%s\n", *argv);
   double d1 = 3;
   double d2 = 6;
   printf ("d1 = %g, d2 = %g\n", d1, d2);
   swapm (&d1, &d2, sizeof (double));
   printf ("d1 = %g, d2 = %g\n", d1, d2);
   char s1[] = "Hello, World.";
   char s2[] = "This is a test of swapa.";
   printf ("s1 = \"%s\", s2 = \"%s\"\n", s1, s2);
   swapa (s1, s2, strlen (s1));
   printf ("s1 = \"%s\", s2 = \"%s\"\n", s1, s2);
   return 0;
}

//TEST// valgrind --leak-check=full swap </dev/null >swap.out 2>&1
//TEST// mkpspdf swap.ps swap.c* swap.out

