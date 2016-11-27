#ifndef MACHINE
#define MACHINE

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include "identifier.h"
#include "numeric.h"
#include "real.h"
#include "character.h"
#include "mis_string.h"
//#include "TCPSocket.h"
#include "TCPServerSocket.h"
#include "output_buffer.h"
#include "error_buffer.h"
#include "Thread.h"
 
using namespace std;

class Instruction;

class Machine : public Thread {

private:
	vector<Instruction*> instructions; // a list of all the existing instructions
	map<string,Identifier*> identifiers; // a map of all the existing identifiers (a.k.a variables)
	map<string,Identifier*> typeSet; // a map of identifiers' prototypes that are used for cloning
	map<string,Instruction*> instSet; // a map of instructions' prototypes that are used for cloning
	map<string,int> labels; // a map of defined labels

<<<<<<< HEAD
	//string programFileName; // the filename for the MIS program
	//string errorFileName; // the filename for the error file
	//string outputFileName; // the filename for the output file

	// Server read and write buffer size (default = 10*1024*1024)
	int readBufferSize;
	int writeBufferSize;

=======
	// read and write buffer size
    int readBufferSize;
    int writeBufferSize;
	
>>>>>>> 7acafc1d907b99689c3dcb2f2e394ea3c3928ee7
	// client socket timeout
	int ClientTimeoutSec = 10, ClientTimeoutMilli = 0;

	string inputBuffer=""; // server input buffer
<<<<<<< HEAD
	//char* outputBuffer=0; // server output buffer
	//char* errorBuffer=0; // server error buffer

=======
	
	OutputBuffer outputBuffer; // output returned to the client
	ErrorBuffer errorBuffer; // errors returned to the client 
	
>>>>>>> 7acafc1d907b99689c3dcb2f2e394ea3c3928ee7
	TCPSocket * tcpClientSocket; // TCP Socket for communication with client

	// becomes true if error happens during parsing or executing
	// remains false if there is no error
	bool parseError;

	// Continuously parse an mis file
	void parseFile();

	// Parses one line for an given variable
	void parseVar(stringstream &line, int lineNumber);

	// Parses one line for an given instruction
	void parseInst(string command, stringstream &argv, int lineNumber);

	void makeThread(istringstream* f, );

    // parse and run a program file
    void runProgram();

	string ReplaceAll(string str, const string& from, const string& to); // replaces all occurrences of a string inside of another string

public:
	// constructor
	Machine();
	Machine(TCPSocket * tcpClientSocket, int readBufferSize = 10*1024*1024, int writeBufferSize = 10*1024*1024);

	// run the MIS server
	void run();

	// add the error message to the error buffer
	void reportError(string errMsg , int lineNumber = -1);
	
	// add the output text to the output buffer
	void reportOutput(string out);

	// set parseError member variable
	void setParseError(bool val);

	map<string,Identifier*> * getidentifiers(); // get a pointer to the map of existing identifiers
	map<string,Identifier*> * getTypes(); // get a pointer to the map of identifiers' prototypes (typeSet)
	map<string, int> *  getLabels(); // get a pointer to the map of existing labels

	// parses line for every token/argument
	vector<char*> parseLine (stringstream &line);
	void trimWhitespace(string& str); // trims whitespace

	void * threadMainBody (void * arg); // Main thread body that runs the MIS machine

    // destructor
	virtual ~Machine();
};

#endif /* MACHINE */
