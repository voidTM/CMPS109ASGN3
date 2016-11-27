# $Id: Makefile,v 1.13 2016-08-18 13:01:32-07 - - $
# CR: classroom or problem 1 files
# INV: inventory or problem 2 files
# HEAP: maxheap or problem 3 files.
GCC       	= g++ -g -O0 -pthread -Wall -Wextra -std=gnu++14
MKDEP     	= g++ -MM -std=gnu++14
VALGRIND 	= valgrind --leak-check=full --show-reachable=yes

Makefile 	= Makefile
DEPFILE		= Makefile.dep
SOURCE   	= ${MODULES:=.cpp} main.cpp
MODULES		= ${INSTMOD} ${TYPEMOD} machine output_buffer error_buffer TCPServerSocket TCPSocket garbagecollector server Thread

INSTMOD		= add instruction sub mul div set_str_char get_str_char assign out sleep jump condjump compjump
TYPEMOD 	= numeric real character mis_string identifier
OBJECTS  	= ${SOURCE:.cpp=.o}
HEADERS  	= ${MODULES:=.h} includes.h common.h
EXECBIN  	= server_misvm
SRCFILES	= ${SOURCE} ${MKFILE} ${HEADERS}
SMALLFILES	= ${DEPFILE}

all : ${EXECBIN}

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
