// $Id: hello.c,v 1.1 2016-01-22 02:38:28-08 - - $
// Manav Sharma msharma7
//
// NAME
//    hello - print the "Hello, World!" message.
//
// SYNOPSIS
//    hello
//
// DESCRIPTION
//    Prints the "Hello, World!" message if no operands are
//    present.  Errors out with a Usage message otherwise.
//

#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
   basename (argv[0]);
   int exit_status = EXIT_SUCCESS;
        
        if (argc == 1) {
        printf ("Hello, World!\n");
        return EXIT_SUCCESS; 
        } else {
        fprintf(stderr, "Usage: hello");
        exit_status = EXIT_FAILURE;
        return exit_status;
        }
}

