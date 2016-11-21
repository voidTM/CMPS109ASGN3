#include <iostream>
#include <fstream>
#include <string>
#include "stdio.h"

#include "TCPSocket.h"
#include "parser.h"

using namespace std;

int main(int argc, char** argv){
	// Check to see proper number of arguments
	int port;	int filesize;
	string filename; char* serverAddr;
	string outfileBuffer; string errfileBuffer;
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
	string errorFileName = programFileName + ".err";
	string outputFileName = programFileName + ".out";

	ofstream out(outputFileName);
	ofstream err(errorFileName);
	// Redirect output to filess
	streambuf *coutbuf = cout.rdbuf();
	cout.rdbuf(out.rdbuf());
	streambuf *cerrbuf = cerr.rdbuf();
	cerr.rdbuf(err.rdbuf());

	Parser parser(filename);
	parser.parseFile();
	errors = parser.getErrorStatus();

	// if there is no error send data over.
	if(!errors){
		TCPSocket socket = TCPSocket(serverAddr, port);
		ifstream scriptFile(filename);

		string buffer;
		char* headerBuffer[1024];
		char* writeBuffer[1024];
		if(scriptFile.is_open()){
			while(getline(scriptFile,buffer))
				socket.writeToSocket(buffer.c_str(), buffer.size());
		}
	
		// Get Header
		socket.readFromSocket(headerBuffer, headerBuffer.size());
		//do something with header
		filesize = atoi(headerBuffer);
		//Reading data
		while(filesize > 0){
			// read until theoritical end of file
			filesize -= socket.readFromSocket(writeBuffer, writeBuffer.size());
			//outfilebuffer.append(writeBuffer);
			cout << writeBuffer;
		}

		socket.readFromSocket(headerBuffer, headerBuffer.size());
		//do something with header
		filesize = atoi(headerBuffer);
		//Reading data
		while(filesize > 0){
			// read until theoritical end of file
			filesize -= socket.readFromSocket(writeBuffer, writeBuffer.size());
			//errfileBuffer.append(writeBuffer);
			cout << writeBuffer;
		}
	}

	cout.rdbuf(coutbuf); //reset to standard output again
    cerr.rdbuf(cerrbuf);
}