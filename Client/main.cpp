#include <iostream>
#include <fstream>
#include <string>

#include "TCPSocket.h"
#include "parser.h"

using namespace std;

int main(int argc, char** argv){
	// Check to see proper number of arguments
	Parser parser;
	int port;
	char* filename; char* serverAddr;
	//TCPSocket socket;
	if(argc != 4)
		cerr << "client_misvm <server IPaddress>"
				"<server port> file" << endl; 

	// Try to get and categorize things.
	serverAddr = argv[1];
	port = atoi(argv[2]);
	filename = argv[3]; 

	// Establish Connection
	TCPSocket socket = TCPSocket(serverAddr, port);
	
	// Send connection to parser.

}