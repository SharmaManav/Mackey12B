#define _GNU_SOURCE
#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

char *program_name = NULL;
int exit_status = EXIT_SUCCESS;
#define STDIN_NAME "-"
const char *haystack = NULL;
const char *needle = NULL;

typedef struct options {
    bool ignore_case;
    bool filenames_only;
    bool number_lines;
}  options;

void catbyline (FILE *input, char *filename, char *needle,
                options *opts, int x) {
   char buffer[1024];
   char *inp = NULL;
   for (int linenr = 1;; ++linenr) {
      char *buf = fgets (buffer, sizeof buffer, input);
      if (buf == NULL) break;
      if (opts->ignore_case){
         inp = strcasestr(buf, needle);
      }else{
         inp = strstr(buf, needle);
      }
      if (inp != NULL){
         if (opts->filenames_only){
            printf("%s\n", filename); break;
        }else{
            if (opts->number_lines){
               if (x>1){
                  printf("%s:%d:%s", filename, linenr, buf);
               }else{
                  printf("%d:%s", linenr, buf);
               }
        }else{
            if (x>1) {
                  printf("%s:%s", filename, buf);
        }else{
            printf("%s", buf);
        }
       }
     }
    }
  }
}

void scan_options (int argc, char **argv, options *opts) {
   opts->ignore_case = false;
   opts->filenames_only = false;
   opts->number_lines = false;
   opterr = false;
   for (;;) {
      int opt = getopt (argc, argv, "iln");
      if (opt == EOF) break;
      switch (opt) {
         case 'i':
            opts->ignore_case = true;
            break;
         case 'l':
            opts->filenames_only = true;
            break;
         case 'n':
            opts->number_lines = true;
            break;
         default:
            exit_status = EXIT_FAILURE;
            fflush (NULL);
            fprintf (stderr, "%s: -%c: invalid option\n",
                             program_name, optopt);
            break;
        }
    }
}

const char *strbool (bool value) {
   return value ? "true" : "false";
}


int main (int argc, char **argv) {
   options opts;
   int argst = 1;
   scan_options (argc, argv, &opts);
   program_name = basename (argv[0]);
   if (argc == 1) {
   fprintf(stderr, "Usage: %s [-iln] string [filename...]\n",
   program_name);
   }else {
     if (strstr(argv[1], STDIN_NAME) != NULL) {
        ++argst;
     }
      char *needle = argv[argst];
      ++argst;
      if (argst == argc) {
         catbyline(stdin, STDIN_NAME, needle, &opts, 0);
      }else{
         int fileck = argc - argst;
      for (int argi = argst; argi < argc; ++argi) {
         char *filename = argv[argi];
         if (strcmp (filename, STDIN_NAME) == 0) {
            catbyline (stdin, STDIN_NAME, needle, &opts, 0);
         }else {
            FILE *input = fopen (filename, "r");
            if (input != NULL) {
               catbyline (input, filename, needle, &opts, fileck);
               fclose (input);
            }else {
               exit_status = EXIT_FAILURE;
               fflush (NULL);
               fprintf (stderr, "%s: %s: %s\n", program_name,
                        filename, strerror (errno));
               fflush (NULL);
            }
         }
      }
   }
 }
   return exit_status;
}

//TEST// cal 9 1752 >cal.1752.09; cal 4 2013 >cal.2013.04
//TEST// catbyline cal.1752.09 cal.2013.04 >catbyline.out
//TEST// mkpspdf catbyline.ps catbyline.c* catbyline.out*

