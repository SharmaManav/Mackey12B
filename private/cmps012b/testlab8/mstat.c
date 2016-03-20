//Manav Sharma msharma7
//Christian Lam ctlam

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

int EXIT_STATUS = 0;

static void mstat(char *progname, char *filename){
  struct stat *buff = malloc(sizeof(struct stat));  
  char *linkpath = calloc(sizeof(char), 100);
  int printlink = readlink(filename, linkpath, 100);
  
  if(lstat(filename, buff) == -1) {
    fprintf(stderr, "%s: %s: %s\n", 
            progname, filename, strerror(errno));
    EXIT_STATUS = 1;
  } else {
    int md = buff->st_mode;
    int sz = buff->st_size;
    time_t filetime = buff->st_mtime;
    time_t raw;
    time(&raw);
    
    struct tm *date = localtime(&filetime);
    char calendar[30];
    
    if(abs(raw - filetime) < 15552000){
      strftime(calendar, 29, "%b %e %R", date);
    } else {
      strftime(calendar, 29, "%b %e  %Y", date);
    }
    
    printf("%06o %9d %s %s",md, sz, calendar, filename);
    
    if (printlink != -1) printf(" -> %s", linkpath);
    printf("\n");
  }
  free(buff);
  free(linkpath);

}

int main (int argc, char **argv) {
  if (argc == 1) {
    char *current_dir = ".";
    mstat(argv[0], current_dir);
  } else{
    for(int i = 1; i < argc; i++){
      mstat(argv[0], argv[i]);
    }
  }
  return EXIT_STATUS;
}
