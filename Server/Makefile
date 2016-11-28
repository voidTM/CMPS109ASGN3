# $Id: Makefile,v 1.13 2016-08-18 13:01:32-07 - - $
# CR: classroom or problem 1 files
# INV: inventory or problem 2 files
# HEAP: maxheap or problem 3 files.
GCC       	= g++ -g -O0 -pthread -Wall -Wextra -std=gnu++14
MKDEP     	= g++ -MM -std=gnu++14
VALGRIND 	= valgrind --leak-check=full --show-reachable=yes

Makefile 	= Makefile
DEPFILE		= Makefile.dep
CLIENTSRC	= ${MODULES:=.cpp} clientmain.cpp
SERVERSRC	= ${MODULES:=.cpp} servermain.cpp
MODULES		= ${INSTMOD} ${TYPEMOD} ${THREAD} ${SOCKET} machine output_buffer error_buffer servermachine clientmachine
THREAD		= Thread 
SOCKET		= TCPServerSocket TCPSocket garbagecollector server
INSTMOD		= add instruction sub mul div set_str_char get_str_char assign out sleep jump condjump compjump thread_begin thread_end barrier
TYPEMOD 	= numeric real character mis_string identifier
HEADERS  	= ${MODULES:=.h} includes.h common.h
CLIENTBIN	= client_misvm
CLIENTOBJ	= ${CLIENTSRC:.cpp=.o}
SERVERBIN 	= server_misvm
SERVEROBJ	= ${SERVERSRC:.cpp=.o}
EXECBIN  	= ${CLIENTBIN} ${SERVERBIN}
SRCFILES	= ${SOURCE} ${MKFILE} ${HEADERS}
SMALLFILES	= ${DEPFILE}

all : ${CLIENTBIN} ${SERVERBIN}

${CLIENTBIN} : ${CLIENTOBJ}
	${GCC} -o${CLIENTBIN} ${CLIENTOBJ}

${SERVERBIN} : ${SERVEROBJ}
	${GCC} -o${SERVERBIN} ${SERVEROBJ}


%.o : %.cpp
	${GCC} -c $<

clean :
	- rm ${SERVEROBJ} ${CLIENTOBJ}

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
