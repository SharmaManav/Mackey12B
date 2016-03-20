GCC      = gcc -g -O0 -Wall -Wextra -std=gnu99

CSOURCES = nsort.c lsort.c
SOURCES  = ${CSOURCES} Makefile
EXECBINS = nsort   lsort
LISTING  = ../lab6c.nsort-lsort.ps
SUBMIT   = submit cmps012b-wm.w16 lab6

all : ${EXECBINS}

% : %.c
	- checksource $<
	${GCC} $< -o $@

ci :
	cid + ${SOURCES}

clean :
	- rm core

spotless : clean
	- rm ${EXECBINS}

lis : ${CSOURCES} Makefile
	mkpspdf ${LISTING} ${SOURCES}

submit : ${SOURCES}
	${SUBMIT} ${SOURCES}

again : ${SOURCES}
	gmake --no-print-directory spotless ci all lis


