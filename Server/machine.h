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
 
using namespace std;

class Instruction;

class Machine {

protected:
	vector<Instruction*> instructions; // a list of all the existing instructions
	map<string,Identifier*> identifiers; // a map of all the existing identifiers (a.k.a variables)
	map<string,Identifier*> typeSet; // a map of identifiers' prototypes that are used for cloning
	map<string,Instruction*> instSet; // a map of instructions' prototypes that are used for cloning
	map<string,int> labels; // a map of defined labels
	vector<pthread_t*> runningThreads; // a list of threads currently running

	// read and write buffer size
    int readBufferSize;
    int writeBufferSize;
	

	// client socket timeout
	//int ClientTimeoutSec = 10, ClientTimeoutMilli = 0;

	string inputBuffer=""; // server input buffer
	
	OutputBuffer outputBuffer; // output returned to the client
	ErrorBuffer errorBuffer; // errors returned to the client 
	
	//TCPSocket * tcpClientSocket; // TCP Socket for communication with client

	// becomes true if error happens during parsing or executing
	// remains false if there is no error
	bool parseError;


	// Parses one line for an given variable
	void parseVar(stringstream &line, int lineNumber);

	// Parses one line for an given instruction
	void parseInst(string command, stringstream &argv, int lineNumber);

	//void makeThread(istringstream* f, int lineNumber);

    // parse and run a program file
    //void runProgram();

	string ReplaceAll(string str, const string& from, const string& to); // replaces all occurrences of a string inside of another string
  
public:
	// constructor
	Machine();
	//Machine(TCPSocket * tcpClientSocket, int readBufferSize = 10*1024*1024, int writeBufferSize = 10*1024*1024);

	// run the MIS server
	//void run();

	// add the error message to the error buffer
	void reportError(string errMsg , int lineNumber = -1);
	
	// add the output text to the output buffer
	void reportOutput(string out);
	// Continuously parse an mis file
	//virtual void parseFile() = 0;
	void parseFile();
	void trimWhitespace(string& str); // trims whitespace

	// parses line for every token/argument
	vector<char*> parseLine (stringstream &line);

	// set parseError member variable
	void setParseError(bool val);
	
	// execute the instructions one by one
	virtual void executeInstructions(int startInstIdx = 0) = 0;

	map<string,Identifier*> * getidentifiers(); // get a pointer to the map of existing identifiers
	map<string,Identifier*> * getTypes(); // get a pointer to the map of identifiers' prototypes (typeSet)
	map<string, int> *  getLabels(); // get a pointer to the map of existing labels
	vector<pthread_t*> * getRunningThreads(); // get a pointer to the vector of the currently running threads

	//void * threadMainBody (void * arg); // Main thread body that runs the MIS machine

    // destructor
	virtual ~Machine();
};

#endif /* MACHINE */
