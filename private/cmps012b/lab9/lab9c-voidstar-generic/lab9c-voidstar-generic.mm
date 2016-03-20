.so Tmac.mm-etc
.if t .Newcentury-fonts
.INITR* \n[.F]
.SIZE 12 14
.TITLE CMPS-012M Spring\~2016 Lab\~9 \
"Generic code using \f[CB]void*\f[P]"
.RCS \
"$Id: lab9c-voidstar-generic.mm,v 1.39 2016-02-09 13:29:26-08 - - $"
.PWD
.URL
.GETST* insertion_sort Figure_insertion_sort
.H 1 "Overview"
In this lab, you will impement a generic sorting routing using the
.V= void*
parameter declaration.
This is similar to the C library function
.V= qsort (3).
You will also review your knowledge of
.V= Makefile s
and header files.
Begin by studying the example programs in 
.V= wk09a-cqsort/ .
Also study
.V= misc/voidstar.c .
.H 1 "Programs to write"
Write the following programs and files,
each as described here\(::
.de FILENAME
.   V=LI "\\$1"
.   P
..
.BVL \n[VCODENWIDTH]u
.FILENAME Makefile
Write a
.V= Makefile
with the following targets,
and in each case,
provide the appropriate actions.
.nr LINESORTWID \w'\f[CB]linesort:\0\0\fR'
.nr INDENTHERE \n[LINESORTWID]u+\n[VCODENWIDTH]u
.VL \n[INDENTHERE]u \n[VCODENWIDTH]u
.V=LI all:
should build the two binaries
.V= numsort
and
.V= linesort .
.V=LI numsort:
depends on
.V= numsort.o
and
.V= inssort.o .
.V=LI linesort:
depends on
.V= linesort.o
and
.V= inssort.o .
.V=LI %.o:
depends on
.V= %.c .
All C compilations should be done with the command
.VTCODE* 1 "gcc -g -O0 -Wall -Wextra -std=gnu11"
Note specifically the use of the
.V= -c
and
.V= -o
options from previous
.V= Makefile s.
.V=LI ci:
depends on all source files and runs both
.V= ci
and
.V= checksource .
.V=LI submit:
depends on source files and submits them.
.LE
.FILENAME numsort.c
This utility reads in
.V= double
numbers from
.V= stdin ,
sorts them, then prints them.
.ALX i ()
.LI
Write a program which will create an array
.VTCODE* 1  "double array[0x1000];"
and use
.V= scanf (1)
to read numbers into this array.
.LI
It stops reading when the first of the following happens\(::
end of file,
any invalid input not recognized by
.V= scanf ,
or the array is full.
.LI
The numbers are then passed to the function
.V= inssort ,
along with a suitable comparison function.
The numbers are sorted in increasing order.
.LI
The numbers are then printed one per line using the format
.V= \[Dq]%20.15g\[rs]n\[Dq] .
.LE
.FILENAME linesort.c
This utility reads in lines from
.V= stdin
into an array, sorts them, then prints them.
.ALX i ()
.LI
Allocate an array
.VTCODE* 1 "char *array[0x1000];"
of pointers to character strings,
read in each character string from
.V= stdin
using
.V= fgets (3)
and
.V= strdup (3)
each line into the array.
Plug the newline at the end of each line with a
.V= '\[rs]0' ,
but don't error out if there is no newline.
Use
.VTCODE* 1  "char buffer[0x1000];"
as an input buffer.
The program stops at end of file,
or when the array is full.
.LI
It then calls
.V= inssort
to sort the strings using a suitable comparison function.
The lines are sorted into increasing lexicographic order.
.LI
The lines are then printed, one per line of output.
.LE
.FILENAME inssort.h
This file is the header file to be included by both
.V= numsort.c
and
.V= linesort.c
and it is important that both of these programs call the same
function.
Do not write a separate
.V= double
sorter
and a separate
.V= char*
sorter.
Using proper style, provide file guards and necessary
.V= #include s
to prototype the following function\(::
.DS
.VCODE* 1 "void inssort (void* base, size_t nelem, size_t size,"
.VCODE* 1 "              int (*compar) (const void*, const void*));"
.DE
The parameters are as follows\(::
.ALX i ()
.LI
.V= base
is the base address of the array,
.LI
.V= nelem
is the number of elements (length) of the array,
.LI
.V= size
is the number of bytes used by a single array element,
and
.LI
.V= compar
is a comparison function which produces the usual results,
i.e.,
a negative number if the first argument is less than the second,
zero if equal,
and a positive number of greater.
.LE
.FILENAME inssort.c
Before beginning your program,
you may wish to use the library function
.V= qsort (3)
to debug your main programs,
but be sure to delete all references to
.V= qsort
before submitting your program.
.ALX i ()
.LI
Your program should be a direct line-for-line translation of
the Java function
.V= insertion_sort \(::
.DS
.ft CB
   static <elem_t extends Comparable <? super elem_t>>
   void insertion_sort (elem_t[] array, int nelem) {
      for (int sorted = 1; sorted < nelem; ++sorted) {
         int slot = sorted;
         elem_t copy = array[slot];
         for (; slot > 0; --slot) {
            int cmp = copy.compareTo (array[slot - 1]);
            if (cmp > 0) break;
            array[slot] = array[slot - 1];
         }
         array[slot] = copy;
      }
   }
.DE
.LI
Inside the function,
you must use byte offsets from the base of the array in order
to compute data movements.
.LI
Cast addresses from
.V= void*
to
.V= char*
in order to do address arithmetic.
An array element
.V= i
is at location
.V= "base + i * size" .
.LI
Pass the address of each pair of elements to the comparison function.
The comparison function accepts addresses of elements,
not elements themselves.
.LI
Use the function
.V= memcpy (3)
to copy parts of the array from one location in memory to another.
.LI
To allocate space for the temporary
.V= element
variable, use
.V= malloc (3).
Don't forget to
.V= free (3)
this temporary before returning from the function.
.LE
.LE
.H 1 "Eliminate all warnings and submit"
Eliminate all warnings that
.V= gcc
with the 
.V= -Wall
and
.V= -Wextra
options may produce,
ensure
.V= checksource
does not complain,
and eliminate all messages from
.V= valgrind\~--leak-check=full .
.P
Submit
.V= README ,
.V= Makefile ,
.V= numsort.c ,
.V= linesort.c ,
.V= inssort.h ,
.V= inssort.c .
Also, if you are doing pair programming,
submit the required pair programming files.
.FINISH
