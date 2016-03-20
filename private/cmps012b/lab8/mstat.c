//Manav Sharma msharma7

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>

int EXIT_STATUS = EXIT_SUCCESS;
char *progname = NULL;

static void mstat (char *filename){
    struct stat buffer;
    int check = lstat(filename, &buffer);
    if (check != 0) {
        printf("mstat: no such file or directory");
        fflush(NULL);
        fprintf(stderr, "%s: %s: %s\n", progname, filename,
                strerror (errno));
        fflush(NULL);
        EXIT_STATUS = EXIT_FAILURE;
    }else{
        int sz = (int)buffer.st_size;
        int md = (int)buffer.st_mode;

        printf("%06o\t%d ", md, sz);

        struct tm *tm = localtime(&buffer.st_mtime);
        time_t currtime;
        time(&currtime);
        double diff = difftime(buffer.st_mtime, currtime);
        char *fmt = NULL;

        if (diff < 0) diff = -diff;
        if (diff > 15552000) {
            fmt = "%b %e %y";
        }else{
            fmt = "%b %e %R";
        }
        
        char timebuff[1024];
        strftime(timebuff, sizeof(timebuff), fmt, tm);
        printf("%s %s", timebuff, filename);
        
        char *linker = NULL;
        linker = malloc(buffer.st_size +1);
        assert(linker !=NULL);
        int linkto = readlink(filename, linker, buffer.st_size+1);

        if (linkto != -1){
            linker[buffer.st_size] = '\0';
            printf(" %s", linker);
        }
        printf("\n");
    }
}

int main(int argc, char **argv) {
    EXIT_STATUS = EXIT_SUCCESS;
    progname = basename (argv[0]);

    if (argc == 1) {
        mstat(".");
    }else{
        for ( int i = 1; i<argc; i++){
            char *filename = argv[i];
            mstat(filename);
        }
    }
}
  
