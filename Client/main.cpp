#include <iostream>
#include <fstream>
#include <string>

#include "TCPSocket.h"

using namespace std;

int main(int argc, char** argv){

	// Check to see proper number of arguments
	if(argc != 4)
		cerr << "client_misvm <server IPaddress>"
				"<server port> file" << endl; 

	// Try to get and categorize things.
	char* serverAddr = argv[1];
	int port = atoi(argv[2]);
	char* filename = argv[2]; 

	// Establish Connection
	TCPSocket socket = TCPSocket(serverAddr, port);
	// Send connection to parser.

}