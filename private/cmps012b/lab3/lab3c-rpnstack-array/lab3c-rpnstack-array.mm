.so Tmac.mm-etc
.if t .Newcentury-fonts
.INITR* \n[.F]
.SIZE 12 14
.TITLE CMPS-012M Winter\~2016 Lab\~3 "RPN, Stacks, ANSI C"
.RCS "$Id: lab3c-rpnstack-array.mm,v 1.54 2016-01-11 21:47:45-08 - - $"
.PWD
.URL
.if dPSPIC \{
.sp -1v
.DS
.PSPIC hp-15c-image.eps 6.5i
.DE
.\}
In this lab,
you will be introduced to ANSI C11 and make use of a stack data
structure implemented as an array.
Input will be read using
.V= scanf (1)
and output printed with
.V= printf (1).
The program will implement a Reverse Polish notation calculator.
.H 1 "Reverse Polish notation"
Reverse Polish notation\*F (RPN)
.FS
.V= http://en.wikipedia.org/wiki/Reverse_Polish_notation
.FE
was invented by the Polish logician
Jan \[/L]ukasiewicz\*F
.FS
.V= http://en.wikipedia.org/wiki/Jan_%C5%81ukasiewicz
\[em]
The notation 
.V= %C5%81 ,
is a two-byte UTF-8 representation of the Unicode character
.V= U+0141 ,
Latin capital letter L with stroke (\[/L]).
.FE
and places all operators after their operands,
which makes it much easier to parse than infix notation,
and does not need parentheses to override operator precedence.
For example, the infix expression
.VTCODE* 1 "3 * 4 + 5 * 6"
is represented as
.VTCODE* 1 "3 4 * 5 6 * +"
in RPN.
.H 1 "HP-15C RPN Scientific Calculator"
A Free HP-15C RPN Scientific Calculator Simulator
is available in the directory
.V= HP15C-Calculator/ .\*F
.FS
.V= http:Labs-cmps012m/lab3c-rpnstack-array/HP15C-Calculator/
.FE
The Java Swing and Javascript versions have
been downloaded.
Other versions are available at the original site.\*F
.FS
.V= http://hp15c.com/
.FE
To run the locally stored Java version\(::
.VTCODE* 1 "cd Labs-cmps012m/lab3c-rpnstack-array/HP15C-Calculator/"
.VTCODE* 1 "HP15C.jar &"
If you prefer to use the web version,
starting with the URL for this lab,
click on
.V= http:HP15C-Calculator ,
then click on the image of the calculator,
which will then bring up a Javascript web emulator.
.H 1 "Program input"
Input to the program will consist of double precision IEEE-754\*F
.FS
.V= http://en.wikipedia.org/wiki/IEEE_floating_point
.FE
floating point numbers and calculator operators.
You have been provided with a reference implementation
.V= jrpn.java
which you are to translate into
.V= crpn.c ,
for which a skeleton outline has been provided.
.ALX i ()
.LI
Any word on input that looks like a number to the function
.V= strtod (3)
is pushed onto a stack.
.LI
If an input word consists of one of the operators
.V= '+' ,
.V= '-' ,
.V= '*' ,
or
.V= '/' ,
two numbers will be popped off the stack,
the right operand being popped first and the left operand next,
then the result is pushed back onto the stack.
.LI
The operator
.V= ';'
cause all numbers on the stack to be printed,
from bottom to top using the format
.V= \[Dq]%.15g\[rs]n\[Dq] .
.LI
The operator
.V= '@'
clears the stack.
.LI
Any input word beginning with the character
.V= '#'
causes the rest of the line to be ignored as a comment.
.LI
Anything else on input is an error.
.LE
.H 1 "Outline of the functions"
The following functions are to be implemented.
See the Java version for detailed implementation requirements.
.ALX i ()
.LI
.V= "void bad_operator (char *oper)"
.br
takes an invalid operator and prints an error message.
.LI
.V= "void push (struct stack *stack, double number)"
.br
pushes the number onto the stack if there is space but prints
an error message if not.
.LI
.V= "void do_binop (struct stack *stack, char operator)"
.br
accepts a binary operator,
pops the right operand then the left operand,
computes the answer then pushes the result on the stack.
An error message is printed if there are not at least two numbers
on the stack.
.LI
.V= "void do_print (struct stack *stack)"
.br
prints the stack bottom to top, one number per line,
or indicates that the stack is empty.
.LI
.V= "void do_clear (struct stack *stack)"
.br
causes the stack to be emptied.
.LI
.V= "void do_operator (struct stack *stack, char *operator)"
.br
accepts any operator and dispatches the appropriate function
to perform the operation.
.LI
.V= "int main (int argc, char **argv)"
.br
loops reading input and calls other functions to perform appropriate
operations.
.LE
.H 1 "The \f[CB]code/\f[P] and \f[CB]misc/\f[P] subdirectories"
The
.V= code/
subdirectory contains two programs\(::
.V= jrpn.java
contains the implementation of your lab in Java.
.V= crpn.c
contains a partial implementation of your lab in C.
The 
.V= main
function is complete,
and you have to fill in the bodies of the rest of the functions
to that they do exactly the same thing as the Java version.
The exact format of the numbers printed will be slighly different
because of the way the languages format numbers differently.
.P
The
.V= misc/
subdirectory contains various sample programs illustration some
facets of ANSI C11.
.H 1 "Compiling your code"
Do not type
.V= gcc
in at the terminal directly,
since it is properly used with multiple options,
which would normally be put in a 
.V= Makefile .
This time, you will write a simple shell script called
.V= mk
to perform the compilation.
The script should contain the following lines\(::
.DS
.VTCODE* 1 "#!/bin/sh"
.VTCODE* 1 "# \[Do]Id\[Do]"
.VTCODE* 1 "gcc -g -O0 -Wall -Wextra -std=gnu11 crpn.c -o crpn"
.DE
Add your name after the RCS Id comment line in another comment.
Use
.V= chmod\~+x
to make it executable.
When you have created the file,
check it into an RCS subdirectory using
.V= cid .
Also do this with your program
.V= crpn.c .
Note\(::
The hash-bang line (starting with
.V= #! )
may not have any spaces.
.H 1 "What to submit"
Submit the script
.V= mk
and the program
.V= crpn.c ,
and if you are doing pair programming, also the
.V= PARTNER
file.
.FINISH
