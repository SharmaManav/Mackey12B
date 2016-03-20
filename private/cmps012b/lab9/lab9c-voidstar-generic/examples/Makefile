# $Id: Makefile,v 1.4 2015-02-26 18:26:03-08 - - $

GCC      = gcc -g -O0 -Wall -Wextra -std=gnu11
MKDEPS   = gcc -MM

EXECBINS = numberproc stringproc testswap
LIBSRC   = genericlib.h genericlib.c
OBJECTS  = ${EXECBINS:=.o} genericlib.o
SOURCES  = ${LIBSRC} ${EXECBINS:=.c} Makefile
DEPFILE  = Makefile.deps
LISFILES = ${SOURCES} ${DEPFILE}
LISTING  = Listing.ps

all: ${EXECBINS}

%: %.o genericlib.o
	${GCC} -o $@ $^ -lm

%.o: %.c
	${GCC} -c $<

ci: ${SOURCES}
	checksource ${SOURCES}
	cid + ${SOURCES}

lis: ${SOURCES} ${DEPFILE} ${EXECBINS:=.out}
	mkpspdf ${LISTING} $^

clean:
	- rm ${OBJECTS} ${EXECBINS:=.out}

spotless: clean
	- rm ${EXECBINS} ${LISTING} ${LISTING:.ps=.pdf} ${DEPFILE}

%.out: %
	$< >$@ 2>&1

${DEPFILE}:
	${MKDEPS} ${SOURCES} >${DEPFILE}

dep:
	- rm ${DEPFILE}
	make --no-print-directory ${DEPFILE}

include ${DEPFILE}

again:
	make --no-print-directory spotless dep ${EXECBINS} lis

