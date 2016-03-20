.so Tmac.mm-etc
.if t .Newcentury-fonts
.INITR* \n[.F]
.SIZE 12 14
.TITLE CMPS-012M Winter\~2016 Lab\~5 "Debugging and memory leak"
.RCS "$Id: lab5c-gdb-valgrind.mm,v 1.55 2016-01-26 19:22:28-08 - - $"
.PWD
.URL
.GETST* MK_SHELL Figure_MK_SHELL
.GETST* UNINIT_C Figure_UNINIT_C
.GETST* MALLOC_C Figure_MALLOC_C
.GETST* LIST1_C Figure_LIST1_C
.nr submit-count 0 1
.de submit
.   P 
.   nr submit-count \\n+[submit-count]
.   nop Submit\(::
.   V= \\$1 
.   P
..   
.de submit-script
.   submit part\\n[part-count].typescript
..
.nr part-count 00 1
.af part-count 01
.de DS-part
.   P
.   DS
.   fi
.   BR "Part (\\n+[part-count])."
.   P
..
.EQ
delim $$
.EN
This lab will introduce you to
.V= gdb ,
the Gnu debugger associated with
.V= gcc ,
and
.V= valgrind ,
which can be used to track uninitialized variables,
memory leak, and dangling pointers.
Uninitialized variables are variables which are declared but whose
value is used before being assigned to.
Memory leak occurs when memory is not freed when no longer needed\(;;
C does not have a garbage collector.
A dangling pointer points at storage that has been freed and should no
longer be accessed.
.P
Before beginning this lab,
study some of the tutorials in
.V= Tutorials/gdb-tutorials .
There are links in this directory to
.V= gdb-tutorial-handout.pdf
and
.V= gdb-tutorial-ohio.html ,
which are fairly short, but also a link to
.V= gdb-tutorial-rms ,
which is much longer and more detailed.
.P
.ft CB
http://www2.ucsc.edu/courses/cmps012b-wm/:/Labs-cmps012m/
.br
lab5c-gdb-valgrind/gdb-tutorials/gdb-tutorial-ohio.html
.br
.ft P
.H 1 "Use of \f[CB]script\f[P]"
In this lab, you will follow some detailed steps.
For each step, submit the files listed.
After you have submitted the necessary files, 
verify that they are all in the submit directory by using
.V= ls .
As in a previous lab, the command
.VCODE* 1 "grep Submit: *.tt"
will summarize the files you need to submit.
Most of the commands will be interactive,
so make use of the
.V= script
command to capture command line output.
A terminal session can be captured with
.VICODE* 1 "script " "filename"
where
.IR filename
is the file into which you want your session captured.
Be sure not to use anything other than line mode commands in
this file, and examine it after to verify this.
Specifically, never use an editor inside a terminal running
.V= script.
.P
.H 1 "Detailed steps"
Following are the items for this lab.
Capture the output in the file specified at the end of each part.
.DS-part
A couple of uninitialized variables.
For convenience, a script
.V= mk
(Figure \*[Figure_MK_SHELL])
has been provided to avoid the need for a
.V= Makefile
in this lab.
It contains compilation instructions.
Start with the program
.V= uninit.c .
(Figure \*[Figure_UNINIT_C]).
Use the following commands.
.submit-script
.TS
allbox tab(|); lw(170p)fCB lw(268p).
mk uninit.c|T{
.fi
Run the script to compile.
T}
valgrind uninit|T{
.fi
Check for uninitialized variables.
T}
echo \[Do]?|T{
.fi
What is the exit status\(??
.V= bash
will capture the crash.
T}
pstatus 139|T{
.fi
Print the meaning of the crash.
T}
exit|T{
.fi
Get out of
.V= script .
T}
.TE
.DE
.DS-part
Now look into your program with
.V= gdb ,
capturing your session into
.V= part02.script
.submit-script
.TS
allbox tab(|); lw(170p)fCB lw(268p).
gdb uninit|T{
.fi
Start
.V= gdb .
T}
run|T{
.fi
Run the program.
T}
where|T{
.fi
Ask where in the program it crashed.
T}
list|T{
.fi
Look at a few lines around where it crashed.
T}
print foo|T{
.fi
Print the values of some variables.
T}
print pointer|T{
.fi
T}
print *pointer|T{
.fi
T}
print argv[0]|T{
.fi
T}
quit|T{
.fi
Quit
.V= gdb .
Answer yes to the subprocess question.
T}
.TE
.DE
.DS-part
Now step through the program a line at a time.
.submit-script
.TS
allbox tab(|); lw(170p)fCB lw(268p).
gdb uninit|T{
.fi
T}
break main|T{
.fi
Set a breakpoint at the beginning of the main function.
T}
run|T{
Note that it stops at the breakpoint.
.fi
T}
print foo|T{
.fi
Note that the value is some number,
but there is no way to figure out why it has this value.
T}
next|T{
.fi
Step one statement,
stepping over, not into, functions.
The command
.V= step
would step into the function instead of over it.
T}
print pointer|T{
.fi
T}
next|T{
.fi
Step one more statement.
Note that it crashes at this point.
T}
quit
.TE
.DE
.DS-part
Now let look at
.V= malloc 
(similar to Java's
.V= new )
and 
.V= free ,
which releases storage.
C does not have a garbage collector.
Start with the program
.V= malloc.c
(Figure \*[Figure_MALLOC_C]).
.submit-script
.br
.P
.TS
allbox tab(|); lw(170p)fCB lw(268p).
valgrind malloc|T{
.fi
Note that there are a couple of
.V= malloc 's
but only one
.V= free 
later.
So one block was leaked.
T}
gdb malloc|T{
.fi
T}
break main|T{
.fi
Set a breakpoint in the main function.
T}
run|T{
.fi
T}
print ptr|T{
.fi
T}
print *ptr|T{
.fi
Bad memory access because
.V= ptr 
is not initialized.
T}
next|T{
.fi
T}
print ptr|T{
.fi
Now
.V= ptr
has a value obtained from the heap.
T}
print *ptr|T{
.fi
But the value it points it is uninitialized.
If it is 0, that is just a coincidence.
T}
next|T{
.fi
T}
next|T{
.fi
T}
next|T{
.fi
T}
print ptr|T{
.fi
T}
print *ptr|T{
.fi
Now it points at initialized storage.
T}
next|T{
.fi
The storage is freed by the call to
.V= free .
T}
next|T{
.fi
T}
next|T{
.fi
T}
next|T{
.fi
The reference to
.V= __libc_start_main
is the startup function called by the operating system
to set up the environment and call main.
T}
quit
.TE
.DE
.DS-part
Examine
.V= list1.c
(Figure \*[Figure_LIST1_C]).
Compile it with
.V= "mk list1.c"
and look at the errors and warnings you see.
Capture the output from this compilation and submit it.
Read the man page
.V= malloc (3)
to see what header file was not included.
.submit-script
.DE
.DS-part
Copy
.V= list1.c
to
.V= list2.c
and fix the missing header file.
Capture the output.
.submit-script
.submit list2.c
.TS
allbox tab(|); lw(170p)fCB lw(268p).
mk list2.c|T{
T}
valgrind list2 foo bar|T{
.fi
Note the complaints from
.V= valgrind .
It complains about memory leak,
but also about invalid access to memory.
T}
gdb list2
break $n$|T{
Set a breakpoint at line $n$,
where $n$ is the line number of the
.V= return
statement.
T}
run foo bar|T{
.fi
Note how arguments are given to a program,
on the
.V= run
not on the invocation of
.V= gdb .
T}
where
list|T{
.fi
List the lines around the point of the crash.
T}
list list2.c:23|T{
We can select the particular set of lines to list.
T}
print head|T{
.fi
Not in the current stack frame.
Note that we have called several library functions,
as shown by 
.V= where .
T}
bt|T{
.fi
A backtrace is another way of looking at the stack.
T}
print head|T{
.fi
Now we are in the correct frame.
T}
print *head
print *(head->word)|T{
.fi
We can use more complicated C expressions.
T}
print head->link->link->link
print *(head->link->link->link)
.TE
.DE
.DS-part
Run
.V= list2
again, showing values in
.V= argv .
.submit-script
.TS
allbox tab(|); lw(170p)fCB lw(268p).
gdb list2
break main
run foo bar|T{
.fi
Run the program with two command line arguments, namely
.V= foo
and
.V= bar .
T}
print argc
print argv
print argv[0]|T{
.fi
.V= argv[0]
is always the name of the program being run.
T}
print argv[1]
print argv[2]
print argv[3]|T{
.fi
.V= argv[argc]
is always the null pointer, represented as
.V= 0x0
in C.
T}
print argv[4]|T{
.fi
After 
.V= argv
is the default environment which you can display using the
.V= env
or
.V= printenv
command.
T}
print argv[5]
print argv[6]
.TE
.DE
.DS-part
Copy
.V= list2.c
to
.V= list3.c
and use
.V= valgrind
and
.V= gdb
as appropriate so that you can track down and fix all of the memory
faults.
Ignore memory leak for now.
The backslash in the command below is just for typographical
reasons, to get the command within the box's width.
You may type the entire command on one line.
.submit-script
.submit list3.c
.TS
allbox tab(|); lw(170p)fCB lw(268p).
T{
.na
valgrind --leak-check=full \[rs]
list3 foo bar baz qux
T}|T{
.fi
Run 
.V= valgrind
with the option 
.V= --leak-check=full
to verify that your program in fact has no problems except leaks.
T}
.TE
.DE
.DS-part
Copy
.V= list3.c
to
.V= list4.c .
Eliminate memory leak by using
.V= free
to release all allocated storage.
.submit-script
.submit list4.c
.TS
allbox tab(|); lw(170p)fCB lw(268p).
T{
.na
valgrind --leak-check=full \[rs]
list4 foo bar baz qux
T}|T{
.fi
Verify that your program now works with no memory faults
and no memory leak.
T}
echo \[Do]?|T{
.fi
Make sure the exit status is
.V= EXIT_SUCCESS .
T}
.TE
.DE
.DS-part
Write a program called
.V= environ.c
which will declare the external variable
.VCODE* 1 "extern char **environ;"
and write a loop iterating over that array,
printing each element per line.
The stopping condition is meeting a null pointer,
as there is no variable indicating how large the array is.
.submit-script
.submit environ.c
.TS
allbox tab(|); lw(170p)fCB lw(268p).
\&./environ|T{
.fi
Print out all your environment variables.
T}
.TE
.DE
.H 1 "What to submit"
Submit the \n[submit-count] files mentioned above.
If you are doing pair programming,
submit the required files as well.
.H 1 "Debugging with \f[CB]ddd\f[P]"
An alternative to
.V= gdb
is
.V= ddd ,
which is a GUI wrapper around 
.V= gdb .
It is not part of this lab and there is nothing to submit from using
.V= ddd ,
but you might want to explore it.
For example\(::
.ALX 1 ()
.LI
Start with\(::
.V= "ddd uninit &" .
The ampersand
.=V ( & )
at the end of the line causes the program to be run in the background.
If you are using a terminal without X11 forwarding this will not work.
.LI
In the 
.V= gdb
window, type\(::
.V= "break main" .
Note that a stop sign appears in the code.
.LI
Then type\(::
.V= run .
An arrow shows the breakpoint.
.LI
Click on 
.E= Step
several times.
.LI
You may also use print statements in the 
.V= gdb
window to examine variables.
.LE
.H 1 "Debugging with \f[CB]gdbtui\f[P]"
There is also a program
.V= gdbtui
which is the text user interface to 
.V= gdb ,
which works in a terminal window in full screen mode.
You might like to try that as well.
.DS
\&
.B1
.SP
.ft CR
.nf
.eo
.pso cat -nv code/mk | expand
.ec
.fi
.ft R
.SP
.B2
.FG "\f[CB]code/mk\f[R]" "" 0 MK_SHELL
.DE
.DS
\&
.B1
.SP
.ft CR
.nf
.eo
.pso cat -nv code/uninit.c | expand
.ec
.fi
.ft R
.SP
.B2
.FG "\f[CB]code/uninit.c\f[R]" "" 0 UNINIT_C
.DE
.DS
\&
.B1
.SP
.ft CR
.nf
.eo
.pso cat -nv code/malloc.c | expand
.ec
.fi
.ft R
.SP
.B2
.FG "\f[CB]code/malloc.c\f[R]" "" 0 MALLOC_C
.DE
.DS
\&
.B1
.SP
.ft CR
.nf
.eo
.pso cat -nv code/list1.c | expand
.ec
.fi
.ft R
.SP
.B2
.FG "\f[CB]code/list1.c\f[R]" "" 0 LIST1_C
.DE
.FINISH
