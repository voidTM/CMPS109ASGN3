# $Id: Makefile,v 1.13 2016-08-18 13:01:32-07 - - $
# CR: classroom or problem 1 files
# INV: inventory or problem 2 files
# HEAP: maxheap or problem 3 files.
GCC       	= g++ -g -O0 -Wall -Wextra -std=gnu++14
MKDEP     	= g++ -MM -std=gnu++14
VALGRIND 	= valgrind --leak-check=full --show-reachable=yes

Makefile 	= Makefile
DEPFILE		= Makefile.dep
SOURCE   	= ${MODULES:=.cpp} main.cpp
MODULES		= ${INSTMOD} ${TYPEMOD} parser machine
INSTMOD		= add instruction assign out
TYPEMOD 	= numeric real character mis_string
OBJECTS  	= ${SOURCE:.cpp=.o}
HEADERS  	= ${MODULES:=.h} identifier.h 
EXECBIN  	= misvm
SRCFILES	= ${SOURCE} ${MKFILE} ${HEADERS}
SMALLFILES	= ${DEPFILE}

all : ${EXECBIN} clean

${EXECBIN} : ${OBJECTS}
	${GCC} -o${EXECBIN} ${OBJECTS}

%.o : %.cpp
	${GCC} -c $<

clean :
	- rm ${OBJECTS}

spotless : clean
	- rm ${EXECBIN}

${DEPFILE} :
	${MKDEP} ${SOURCE} >${DEPFILE}

dep :
	- rm ${DEPFILE}
	${MAKE} --no-print-directory ${DEPFILE}

include Makefile.dep

again :
	${MAKE} spotless dep all

