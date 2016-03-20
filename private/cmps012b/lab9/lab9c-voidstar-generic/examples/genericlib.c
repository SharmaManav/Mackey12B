// $Id: genericlib.c,v 1.3 2014-05-15 20:57:59-07 - - $

#include <stdlib.h>
#include <string.h>

#include "genericlib.h"

void swapm (void* this, void* that, size_t size) {
   TRACE ("%p, %p, %zd", this, that, size);
   void *temp = malloc (size); 
   printf ("%s: temp=%p\n", __func__, temp);
   memcpy (temp, this, size);
   memcpy (this, that, size);
   memcpy (that, temp, size);
   free (temp); 
}

void swapa (void* this, void* that, size_t size) {
   TRACE ("%p, %p, %zd", this, that, size);
   void *temp = alloca (size); 
   printf ("%s: temp=%p\n", __func__, temp);
   memcpy (temp, this, size);
   memcpy (this, that, size);
   memcpy (that, temp, size);
}

void process (void* base, size_t nelem, size_t size,
              void (*function) (void*)) {
   TRACE ("%p, %zd, %zd, %p", base, nelem, size, function);
   for (size_t index = 0; index < nelem; ++index) {
      void *element = (char*) base + index * size; 
      function (element);
   }
}

