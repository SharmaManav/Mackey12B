.so Tmac.mm-etc
.if t .Newcentury-fonts 11
.INITR* \n[.F]
.SIZE 12
.TITLE CMPS-012M Winter\~2016 Lab\~4 "stdio, getopt"
.RCS "$Id: lab4c-stdio-getopt.mm,v 1.16 2016-01-12 17:30:40-08 - - $"
.PWD
.URL
.tm .\\" @ps=\n[@ps]
.tm .\\" @vs=\n[@vs]
This lab will introduce you to the use of files in ANSI C,
and scanning options from the command line.
Use the command
.V= man (1)
to read about various commands and functions that are mentioned
in this document.
For each function,
the synopsis shows you what header needs to be included,
and also displays the prototypes for relevant library functions.
.H 1 "Program Specification"
The program specification is given in the format of a Unix
.V= man (1)
page.
.MANPAGE=BVL
.MANPAGE=LI "NAME"
cmatch \[em] print matching lines from files
.MANPAGE=LI "SYNOPSIS"
.V= cmatch
.=V \|[ -iln ]
.I \|string
.RI \|[ filename \|.\|.\|.]
.MANPAGE=LI "DESCRIPTION"
.V= cmatch
searches the named input files for lines containing the string.
By default the matching lines are printed.
If more than one file is specified,
lines of output are preceded by the filename.
.MANPAGE=LI "OPTIONS"
Options are scanned using
.V= getopt (3)
and are subject to its restrictions and conventions.
.MANOPT=VL
.MANOPT=LI -i
Ignore case distinctions between the string and the contents of files.
.MANOPT=LI -l
Suppress normal output.
Print only the names of files for which a match is found.
.MANOPT=LI -n
Prefix each line of output with the line number starting from 1
within each file.
.LE
.MANPAGE=LI "OPERANDS"
The first operand is required and is the string to be used to
search the files.
The rest of the operands are filenames to be processed in sequence.
If no filenames are specified, stdin is read.
If a file is specified as a single minus
.=V ( - )
stdin is read at that point.
.MANPAGE=LI "EXIT STATUS"
.VL \n[Pi]
.LI 0
No errors were detected.
.LI 1
Errors were detected and messages printed to stderr,
either for invalid options or inaccessible files.
.LE
.MANPAGE=LI "SEE ALSO"
.V= grep (1)
.H 1 "Implementation Sequence"
Following are suggestions as to implementation sequence,
which may be followed more or less,
but are not absolutely required if you find a better way.
.ALX a ()
.LI
Study the behavior of
.V= pmatch.perl ,
which is an implementation of your lab in Perl.
.LI
Create a build script called
.V= mk
as you did with the previous project.
This script uses
.VTCODE* 1 "gcc -g -O0 -Wall -Wextra -std=gnu99"
to compile
.V= cmatch.c
into the executable binary
.V= cmatch .
Note that an executable binary generally does not have a suffix.
.LI
Whenever you see a reference to a function in C,
read the man page for it.
For example,
the function
.V= strstr (3)
can be discovered with the command
.VTCODE* 1 "man -s 3 strstr"
Note that in this case,
the synopsis shows you what the arguments and results to the
function is,
and that you need to include the header
.V= <string.h> .
.LI
The example
.V= catbychar.c
shows how to read a file one character at a time.
.LI
The example
.V= catbyline.c
shows how to read a file one line at a time,
assuming the maximum line length is known.
.LI
A file is opened with
.V= fopen (3)
and closed with
.V= fclose (3),
unless it is
.V= stdin ,
which is already opened when the program begins.
.LI
Error messages are printed to
.V= stderr ,
and
.V= fflush (3)
should be called before and after printing a message
in order to ensure that the buffers are cleared.
.LI
The example
.V= getoptex.c
shows how to use
.V= getopt (3)
to scan options given to a program and record each as a
boolean flag in a struct.
Invalid options are handled.
.LI
For
.V= getopt (3),
the variable
.V= opterr
allows us to print messages our own way,
.V= optopt
is the option character actually found,
and
.V= optind
is the index into
.V= argv
which is the first operand.
.LI
Open a file called
.V= cmatch.c ,
which is mostly a copy of
.V= catbyline.c ,
and add the function from
.V= getoptex.c
to ensure that options are scanned.
.LI
For each line read,
instead of just printing it,
check it against the pattern string.
Use either
.V= strstr (3)
or
.V= strcasestr (3)
as required by the options.
.LI
Add in code to print filenames and line numbers as per 
the options,
and make sure the exit status is correct.
.LE
.H 1 "What to Submit"
Submit the file
.V= cmatch.c
as per the specifications,
and the build script
.V= mk .
Also submit
.V= PARTNER
if you do pair programming.
.FINISH
