// $Id: genericlib.h,v 1.2 2014-05-15 20:35:11-07 - - $

#ifndef __GENERICLIB_H__
#define __GENERICLIB_H__

#include <stdlib.h>
#include <stdio.h>

//
// Swap two chunks of storage using malloc and free for the
// temporary structure.
//
void swapm (void* this, void* that, size_t size);

//
// Swap two chunks of storage using alloca, which is on
// the stack and does not have to be freed.
//
void swapa (void* this, void* that, size_t size);

//
// Process an array by applying a function to each element,
// in place.  The elements may be modified.
//
void process (void* base,                // base address of the array
              size_t nelem,              // number of elements in it
              size_t size,               // sizeof one element
              void (*function) (void*)); // the processing function
//
// TRACE macro for start of functions.
//

#define TRACE(FMT,...) printf ("%s:%d: %s (" FMT ")\n", \
                               __FILE__, __LINE__, __func__, \
                               __VA_ARGS__);

#endif

