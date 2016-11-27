#include "server.h"

Server::Server(char * serverAddress, int serverPort, int backlog, int readBufferSize, int writeBufferSize)
		: serverAddress(serverAddress) , serverPort(serverPort) , backlog(backlog) , readBufferSize(readBufferSize) , writeBufferSize(writeBufferSize) {}

void Server::run() {

	TCPServerSocket tcpServerSocket = TCPServerSocket(serverAddress, serverPort, backlog);

	//

	if (tcpServerSocket.initializeSocket() == false)
	{
		cerr << "Error while initializing the server socket." << endl;
		return;
	}
	GarbageCollector garbageCollector;
	while (true)
	{
		TCPSocket * tcpClientSocket = tcpServerSocket.getConnection(0, 0, readBufferSize, writeBufferSize);

		if (tcpClientSocket == NULL)
			continue;

		garbageCollector.cleanup(); // Invoke the garbage collector cleaner in case of expired connections
		Machine * m = new Machine (tcpClientSocket); // Instantiate a new Connection object and pass the returned TCP socket to it
		m->start(); // Start the connection thread to communicate with the client
		garbageCollector.addConnection(m);
    }

	//delete(garbageCollector); // Delete the garbage collector
	//delete (tcpServerSocket); // Terminate and delete the TCP server socket
}
