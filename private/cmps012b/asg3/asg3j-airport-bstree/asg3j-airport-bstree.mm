.so Tmac.mm-etc
.if t .Newcentury-fonts
.INITR* \n[.F]
.SIZE 12 14
.TITLE CMPS-012B Winter\~2016 Program\~3 "Binary Search Trees"
.RCS "$Id: asg3j-airport-bstree.mm,v 1.8 2016-02-09 13:16:58-08 - - $"
.PWD
.URL
.H 1 "Overview"
In this assignment you will implement a binary search tree data
structure that will support airport code queries.
Your program will not attempt to create a balanced tree,
since that is beyond the scope of this course,
but will rather depend on input being suitably ordered.
.H 1 "Program specification"
The program specification is presented in the form of a Unix
.V= man (1) 
page.
.SH=BVL
.MANPAGE=LI "NAME"
airport \(em look up airport name given airport code
.MANPAGE=LI "SYNOPSIS"
.V= airport
.=V \|[ -d ]
.RI \| database
.MANPAGE=LI "DESCRIPTION"
An airport database is read in from the filename specified on
the command line.
Then the standard input is read,
expecting one airport code per line.
For each code read, the name of the airport is printed.
.MANPAGE=LI "OPTIONS"
.VL \n[Pi]
.MANOPT=LI -d
If the
.V= -d
option is specified,
then the airport database is displayed in debug format and
the standard input is ignored.
.LE
.MANPAGE=LI "OPERANDS"
Exactly one operand, the airport database, is required.
Each line of the input database consists of an airport code,
followed by a colon, followed by the name of the airport.
Any line consisting only of white space or whose first non-white-space
character is a hash
.=V ( # )
is ignored as a comment.
Airport codes in the database are always stored in upper case.
If an input airport code is in lower case, it is converted to upper
case.
The standard input consists of one airport code per line.
Empty lines and lines beginning with a hash are ignored.
Lookups of the airport codes are case insensitive.
Thus, for example,
.V= sjc
will be looked up as
.V= SJC .
.MANPAGE=LI "EXIT STATUS"
.VL \n[Pi]
.LI 0
No errors were detected.
.LI 1
The database could not be opened or any lines from it were invalid.
.LE
.LE
.H 1 "Implementation strategy"
As usual, you need to implement your program one step at a time.
Following is a suggested implementation sequence\(::
.ALX 1 ()
.LI
Begin with the main program.
Handle options analysis, 
and for the database,
read and print each line as it is seen.
Print out each database line as two separate fields.
.LI
Look for and fix any remaining bugs in the main program.
Print a usage message if the arguments to the program are not correct.
.LI
Make use of the sample class
.V= treemap
in order to implement your insertion and lookup.
Before submitting your program,
you must remove all references to
.V= java.util.TreeMap
from your code.
The use of the standard library's 
.V= TreeMap
is just for you to implement your main program.
.LI
Remove
.V= TreeMap
from
.V= treemap.java
and implement 
.V= get
and
.V= put
properly.
.LI
For 
.V= get ,
perform a binary search on the tree.
Return
.V= null
for not found.
.LI
For 
.V= put ,
perform a binary search to find the tree node containing the
key.
If found, return the previous value,
and replace the new value in the tree.
.LI
If not found, create a new node as a new leaf node and insert the
key and value fields.
You are not expected to balance the tree.
The test data has been cooked to produce a reasonably balanced tree,
but balancing algorithms are beyond the scope of this course.
.br
.=V [ http://en.wikipedia.org/wiki/Red-black_tree ]
.LI
Add an inorder traversal function which prints the contents of
each tree node.
For each node found in the tree, print its depth, key, value,
left child, and right child.
.LI
If the
.V= -d 
option is specified, then
.V= stdin
is ignored and the database is printed in debug format,
using a depth-first in-order traversal.
.LI
The depth is the distance of a node from the root, 
with the root having depth 0.
When printing the left and right child pointers, 
the default
.V= toString
method will be used, which will print out the node's identity.
Use the format 
.VINDENT* \
"\[Dq]%3d \[rs]\[Dq]%s\[rs]\[Dq] \[rs]\[Dq]%s\[rs]\[Dq] %s %s%n\[Dq]"
which will produce output like
.VINDENT* \
"  3 \[Dq]sjc\[Dq] \[Dq]San Jose\[Dq] \
treemap$tree@1fdc96c treemap$tree@b2fd8f"
.H 1 "What to submit"
Submit the files
.V= README ,
.V= Makefile ,
and all necessary Java source files.
Make sure all of the necessary class files are put in the jar file.
Use
.V= "grep TreeMap *java"
to verify that you have eliminated all references to
.V= TreeMap .
Note that the name of the class you are writing is
.V= treemap ,
spelled in lower case.
If you are doing pair programming,
also submit the
.V= PARTNER
file.
.FINISH
