#include <iostream>
#include <fstream>
#include <string>
#include "stdio.h"

#include "TCPSocket.h"
#include "parser.h"

using namespace std;

int main(int argc, char** argv){
	// Check to see proper number of arguments
	int port;
	string filename; char* serverAddr;
	bool errors;
	//TCPSocket socket;
	if(argc != 4)
		cerr << "client_misvm <server IPaddress>"
				"<server port> file" << endl; 

	// Try to get and categorize things.
	serverAddr = argv[1];
	port = atoi(argv[2]);
	filename = argv[3]; 
	errors = false;
	// Establish Connection
	Parser parser(filename);
	parser.parseFile();
	errors = parser.getErrorStatus();

	// if there is no error send data over.
	if(!errors){
		TCPSocket socket = TCPSocket(serverAddr, port);
		ifstream scriptFile(filename);
		string buffer;
		if(scriptFile.is_open()){
			while(getline(scriptFile,buffer))
				socket.writeToSocket(buffer.c_str(), buffer.size());
		}
	}
}