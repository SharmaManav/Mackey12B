.so Tmac.mm-etc
.if t .Newcentury-fonts
.INITR* \n[.F]
.SIZE 12 14
.TITLE CMPS-012M Winter\~2016 Lab\~6 "malloc(3) and free(3)"
.RCS "$Id: lab6c-malloc-free.mm,v 1.23 2016-01-28 16:01:09-08 - - $"
.PWD
.URL
.H 1 "Overview"
This lab introduces you to
.V= malloc (3),
.V= free (3),
and
.V= strdup (3),
linked lists in C,
dangling pointers, and memory leak.
There are two programs in this assignment,
each of which will read in data,
insert the data into a linked list in sorted order,
and print out the data.
One program will use
.V= double
and the other will use character strings represented as
.V= char* .
See the
.V= code/
subdirectory.
Also, read the man page\(::
.V= "man -s 3 malloc" .
.H 1 "Program \f[CB]nsort\f[B] specification"
As usual, the program is presented in the form of a Unix
.V= man
page specification.
.SH=BVL
.MANPAGE=LI "NAME"
nsort \- sort numbers read from stdin
.MANPAGE=LI "SYNOPSIS"
\f[CB]nsort\f[R]
\|[\f[CB]\-d\f[R]]
.MANPAGE=LI "DESCRIPTION"
Reads in numbers from
.V= stdin ,
and stops at end of file.
Error messages are printed for any word that is not recognized by
.V= scanf (3)
as a number.
The numbers are printed sorted in ascending order, one per line, to
.V= stdout
using the
.V= printf (3)
format
.V= \[Dq]%24.15g\[rs]n\[Dq] .
.MANPAGE=LI "OPTIONS"
Options are scanned by
.V= getopt (3).
.VL \n[Pi]
.LI "\f[CB]\-d\f[R]"
Output is printed in debug format with pointers in
.V= \[Dq][%p]\[Dq]
format.
.LE
.MANPAGE=LI "EXIT STATUS"
.VL \n[Pi]
.LI 0
No errors were detected.
.LI 1
Syntactically incorrect input numbers were detected.
.LE
.LE
.H 1 "Program \f[CB]lsort\f[B] specification"
As usual, the program is presented in the form of a Unix
.V= man
page specification.
.SH=BVL
.MANPAGE=LI "NAME"
lsort \- sort lines read from stdin
.MANPAGE=LI "SYNOPSIS"
\f[CB]lsort\f[R]
\|[\f[CB]\-d\f[R]]
.MANPAGE=LI "DESCRIPTION"
Reads in lines from
.V= stdin ,
stopping at end of file.
The lines are printed sorted in ascending order to
.V= stdout .
The output should be the same as that from
.V= sort (1).
.MANPAGE=LI "OPTIONS"
Options are scanned by
.V= getopt (3).
.VL \n[Pi]
.LI "\f[CB]\-d\f[R]"
Output is printed in debug format with pointers in
.V= \[Dq][%p]\[Dq]
format.
.LE
.MANPAGE=LI "EXIT STATUS"
.VL \n[Pi]
.LI 0
No errors were detected.
.LI 1
An unterminated line or a line longer than 80 characters
was detected.
.LE
.LE
.H 1 "Preparation"
Before you begin,
study the code provided.
.ALX 1 ()
.LI
The file
.V= code/Makefile
is complete, but no source code has been provided for the two C
programs.
.LI
Read the 
.V= man (1)
pages for
.V= malloc (3),
.V= free (3),
and
.V= strdup (3).
.LI
Study the code in the
.V= misc
subdirectory.
None of the code in this directory should be directly copied
into your programs,
but parts of it will be adapted for use.
.LI
Study the sample code
.V= sortlist.java ,
which shows you the exact algorithm you are to use for your program.
It is exactly equivalent to
.V= lsort
when you run without options.
It is similar to
.V= nsort .
Adapt its algorithm line by line.
.LE
.H 1 "Program \f[CB]nsort\f[B] implementation"
This program deals only with lists of numbers.
.ALX 1 ()
.LI
Study the file
.V= scanf.c
to see how to use
.V= scanf (3)
to read numbers from
.V= stdin .
.LI
Study the file
.V= numlist.c
to see how to declare a linked list of nodes containing numbers
and how to use
.V= malloc (3)
to allocate space and how to use
.V= free (3)
to free up the nodes when done.
C does not have a garbage collector.
.LI
Print out the numbers either in ordinary format or in debug format.
.LI
Instead of inserting the new node onto the front of the list,
put in the list in the proper position.
See the program
.V= sortlist.java
for the insertion algorithm.
.LI
Use the command
.V= "valgrind --leak-check=full"
to check for memory leak.
.LE
.H 1 "Program \f[CB]lsort\f[B] implementation"
This program deals with lists of strings, so that
each node uses two heap objects.
.ALX 1 ()
.LI
To begin work,
.V= "cp nsort.c lsort.c" .
Change the declaration of the item field from
.V= double
to
.V= char\~* .
.LI
Look at
.V= strlist.c
to see how strings are handled.
Create a character buffer of dimension 82
.=V ( "char buffer[82];" )
and read in lines.
Insert each line into the list.
Print an error message for any line that is not terminated by
a newline character
.=V ( "'\[rs]n'" ).
The buffer holds up to 80 characters read in from each line,
plus the newline character plus the null plug
.=V ( "'\[rs]0'" ).
.LI
When comparing strings in the insertion routine, use
.V= strcmp (3).
This works very much like
.V= compareTo
in Java.
.LI
Use the command
.V= "valgrind --leak-check=full"
to check for memory leak.
.LE
.H 1 "What to submit"
Submit the files
.V= nsort.c ,
.V= lsort.c ,
and
.V= Makefile .
Your
.V= Makefile
should build the executables
.V= nsort
and
.V= lsort
from the target
.V= all .
If you are doing pair programming, see
.V= /afs/cats.ucsc.edu/courses/cmps012b-wm/Syllabus/pair-programming/
and follow those instructions as well.
.FINISH
