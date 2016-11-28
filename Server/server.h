#ifndef SERVER
#define SERVER

#include "machine.h"
#include "servermachine.h"
#include "garbagecollector.h"
#include "TCPSocket.h"
#include "TCPServerSocket.h"

using namespace std;

class Server {
	// Address and port of the server
	char * serverAddress;
	int serverPort;

	// Server's backlog
	int backlog;

	// Server read and write buffer size (default = 10*1024*1024)
	int readBufferSize;
	int writeBufferSize;

public:
    Server(char * serverAddress, int serverPort, int backlog = 50, int readBufferSize = 10*1024*1024, int writeBufferSize = 10*1024*1024);
    void run(); // run the server
};

#endif
