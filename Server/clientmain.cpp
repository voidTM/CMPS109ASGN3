#include <iostream>
#include <fstream>
#include <string>
#include "stdio.h"
#include <sstream>

#include "TCPSocket.h"
#include "clientmachine.h"

using namespace std;

int main(int argc, char** argv){
	// Check to see proper number of arguments
	int port;	int filesize;
	string filename; char* serverAddr;
	string outfileBuffer; string errfileBuffer;
	bool errors;
	//TCPSocket socket;
	if(argc != 4){
		cerr << "client_misvm <server IPaddress>"
				"<server port> file" << endl;
		exit(1);
	}
	// Try to get and categorize things.
	serverAddr = argv[1];
	port = atoi(argv[2]);
	filename = argv[3];
	errors = false;
	// Establish Connection
	string errorFileName = filename + ".err";
	string outputFileName = filename + ".out";

	//cout << errorFileName << endl;
	ofstream out(outputFileName);

	ofstream err(errorFileName);
	// Redirect output to filess
	streambuf *coutbuf = cout.rdbuf();
	cout.rdbuf(out.rdbuf());
	streambuf *cerrbuf = cerr.rdbuf();
	cerr.rdbuf(err.rdbuf());

	ClientMachine parser(filename);
	errors = parser.checkError();
 
	// if there is no error send data over.
	if(!errors)	{
		TCPSocket socket = TCPSocket(serverAddr, port);
		ifstream scriptFile(filename);

		string buffer;
		string scriptBuffer;
		char headerBuffer[100];
		char writeBuffer[1024];
		char readBuffer[1024];
		if(scriptFile.is_open()){
			/*
			ostringstream oss;
			oss << scriptFile.rdbuf();
			scriptBuffer = oss.str();
			*/
			while(getline(scriptFile,buffer))
				scriptBuffer.append(buffer + "\n");

			//printf("File Content: \n %s", scriptBuffer.c_str());
			filesize = scriptBuffer.size();
			string header = to_string(filesize);
			//printf( "file size %d \n", filesize);
			//cout << header << endl;
			// Send header data
			socket.writeToSocket(header.c_str(),100);
			while(filesize > 0){
				filesize -= socket.writeToSocket(scriptBuffer.c_str(), filesize);
			}
		}
		else{
			printf("errors!!\n");
			return 1;
		}
		// Get Header
		socket.readFromSocket(headerBuffer, 100);
		//do something with header
		filesize = atoi(headerBuffer);
		memset(readBuffer, 0 , 1024);

		//Reading data
		//printf("out file size %d\n", filesize);
		while(filesize > 0){
			// read until theoritical end of file
			filesize -= socket.readFromSocket(writeBuffer, filesize);
			//outfilebuffer.append(writeBuffer);
			cout << writeBuffer;
		}

		socket.readFromSocket(headerBuffer, 100);
		//do something with header
		filesize = atoi(headerBuffer);
		memset(readBuffer, 0 , 1024);
		//Reading data
		//printf("error file size %d\n", filesize);
		while(filesize > 0){
			// read until theoritical end of file
			filesize -= socket.readFromSocket(writeBuffer, 1024);
			//errfileBuffer.append(writeBuffer);
			cerr << writeBuffer;
		}
	}else{
		err << parser.getErrorMsg() << endl;
		out << parser.getOutputMsg() << endl;

	}

	cout.rdbuf(coutbuf); //reset to standard output again
    cerr.rdbuf(cerrbuf);

}
