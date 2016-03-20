#Manav Sharma msharma7
#Christian Lam ctlam

GCC      = gcc -g -O0 -Wall -Wextra -std=gnu99

CSOURCES = numsort.c linesort.c inssort.c
SOURCES  = ${CSOURCES} Makefile PARTNER README  inssort.h
EXECBINS = numsort   linesort
SUBMIT   = submit cmps012b-wm.w16 lab9

all : numsort linesort

numsort: numsort.o inssort.o
	${GCC} numsort.o inssort.o -o numsort

linesort: linesort.o inssort.o
	${GCC} linesort.o inssort.o -o linesort

%.o : %.c
	- checksource $<
	${GCC} $< -c $<


ci :
	cid + ${SOURCES}

clean :
	- rm core

spotless : clean
	- rm ${EXECBINS}


submit : ${SOURCES}
	- checksource ${SOURCES}
	${SUBMIT} ${SOURCES}

again : ${SOURCES}
	gmake --no-print-directory spotless ci all lis

