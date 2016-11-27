#include "machine.h"
#include "add.h"
#include "sub.h"
#include "mul.h"
#include "div.h"
#include "set_str_char.h"
#include "get_str_char.h"
#include "assign.h"
#include "out.h"
#include "sleep.h"
#include <string>
#include "stdio.h"
#include "jump.h"
#include "condjump.h"
#include "compjump.h"

// constructor
Machine::Machine() {}

// constructor
Machine::Machine(TCPSocket * tcpClientSocket, int readBufferSize, int writeBufferSize) : Thread() {

    this->tcpClientSocket = tcpClientSocket;
    this->readBufferSize = readBufferSize;
    this->writeBufferSize = writeBufferSize;

	parseError = false;

	// Create a new object for each subclass of the identifier hierarchy and put them in the map. They will be used for cloning.
	typeSet["NUMERIC"] = new Numeric();
	typeSet["REAL"] = new Real();
	typeSet["CHAR"] = new Character();
	typeSet["STRING"] = new String();

   	// Create a new object for each subclass of the instruction hierarchy and put them in the map. They will be used for cloning.
	instSet["ADD"] = new Add(this);
	instSet["SUB"] = new Sub(this);
	instSet["MUL"] = new Mul(this);
	instSet["DIV"] = new Div(this);
	instSet["SET_STR_CHAR"] = new SetStrChar(this);
	instSet["GET_STR_CHAR"] = new GetStrChar(this);
	instSet["ASSIGN"] = new Assign(this);
	instSet["OUT"] = new Out(this);
	instSet["SLEEP"] = new Sleep(this);
	instSet["JMP"] = new Jump(this);
	instSet["JMPZ"] = new ConditionalJump(this, 1);
	instSet["JMPNZ"] = new ConditionalJump(this, 2);
	instSet["JMPGT"] = new ComparativeJump(this, 1);
    instSet["JMPLT"] = new ComparativeJump(this, 2);
    instSet["JMPGTE"] = new ComparativeJump(this, 3);
    instSet["JMPLTE"] = new ComparativeJump(this, 4);
}

//destructor
Machine::~Machine() {
	if (tcpClientSocket != NULL)
		delete tcpClientSocket;
}

// replaces all occurrences of a string inside of another string
// Replaces \n \t \r with the appropriate actual escape symbol
string Machine::ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

// Continuosly parse an mis file
void Machine::parseFile(){
	int lineNumber;
	int instNumber;
	parseError = false;
    istringstream f(inputBuffer.c_str());
	string line;
	string command;
	lineNumber = 1;
	instNumber = 0;
	while(getline(f,line))
	{
        	//cout << line << endl;
			line = ReplaceAll(line, "\\n", "\n");
			line = ReplaceAll(line, "\\t", "\t");
			line = ReplaceAll(line, "\\r", "\r");
         	stringstream iss(line);
        	iss >> command;

        	if(!command.compare("THREAD_BEGIN"))
        		makeThread(&istringstream, lineNumber);

         	// check to see if it is a variable, label, or instruction
   			if(!command.compare("LABEL")){
				vector <char*> arguments = parseLine(iss);
   				labels[arguments[0]] = instNumber;
   			} else if(!command.compare("VAR"))
            	parseVar(iss, lineNumber);
         	else{
            	//cout << "Instruction: " << command <<endl;
            	parseInst(command, iss, lineNumber);
            	instNumber++; // Ticks for every instruction read
        	}

			lineNumber++;
	}
}

// 
void makeThread(istringstream* f, int lineNumber){
	instNumber = 0;
	string line;
	string command;
	while(getline(f,line))
	{
        	//cout << line << endl;
			line = ReplaceAll(line, "\\n", "\n");
			line = ReplaceAll(line, "\\t", "\t");
			line = ReplaceAll(line, "\\r", "\r");
         	stringstream iss(line);
        	iss >> command;

        	if(!command.compare("THREAD_BEGIN"))
        		makeThread(&istringstream, lineNumber);

         	// check to see if it is a variable, label, or instruction
   			if(!command.compare("LABEL")){
				vector <char*> arguments = parseLine(iss);
   				labels[arguments[0]] = instNumber;
   			} else if(!command.compare("VAR"))
            	parseVar(iss, lineNumber);
         	else{
            	//cout << "Instruction: " << command <<endl;
            	parseInst(command, iss, lineNumber);
            	instNumber++; // Ticks for every instruction read
        	}

			lineNumber++;
}


// Parses one line for an given instruction
void Machine::parseInst(string command, stringstream &argv, int lineNumber){
	try
	{
		string token;
		vector<char*> arguments;

		arguments = parseLine(argv);
		Instruction* obj = instSet[command]; // look for appropriate command

		// Check to see object was created
		if(obj != NULL){
			obj = obj->clone(arguments, lineNumber);

			instructions.push_back(obj);
		}
		else{
			reportError("No such instruction.", lineNumber);
		}
	}
	catch (int e)
	{
		reportError("An error was generated while parsing the line.", lineNumber);
	}
}

// Parses one line for an given variable
void Machine::parseVar(stringstream &line, int lineNumber){
	try
	{
		string token;
		vector<char*> arguments;

		arguments = parseLine(line);

		// get the name and type of variable
		// after parsing
	   	string varName = arguments[0];
   		string varType = arguments[1];
   		// remove name and type from argument vector
   		arguments.erase(arguments.begin());
   		arguments.erase(arguments.begin());
   		//cout << "arguments length: " << arguments.size() << endl;
   		//call appropriate type object
   		Identifier* obj = typeSet[varType];
   		if(obj != NULL){
    	  //create clone
    	  obj = obj->clone(arguments);
    	  //store into variable map
    	  identifiers[varName] = obj;
    	  //return obj;
	   }
	   else
	      reportError("class not found", lineNumber );
	}

	catch (int e)
	{
		reportError("An error was generated while parsing the line.", lineNumber);
	}
}

// parses line for every token/argument after the initial
vector<char*> Machine::parseLine (stringstream &line) {
   string token;
   vector<char*> tokens;
   char* cstr;

   // tokens are created using . as the delimiter
   while(getline(line, token, ',')){
      trimWhitespace(token);
      //cout << "Token: " << token << endl;
      cstr = strdup(token.c_str()); // convert to c-string
      tokens.push_back(cstr);
   }
   return tokens;
}

// removes whitespace from both ends
void Machine::trimWhitespace(string& str){
    size_t first = str.find_first_not_of(" \t\n");
    size_t last = str.find_last_not_of(" \t\n");
    str = str.substr(first, (last-first+1));
}

// parses and runs a program file
void Machine::runProgram()
{
	// parse the entire program file
	parseFile();

	// if there was an error in parsing the file, terminate the execution
	if (parseError) return;

	// try to execute the program instruction by instruction
	int retval, currentInstIdx = 0;
	try
	{
		while (currentInstIdx < instructions.size())
		{
			// execute the current instruction
			retval = instructions[currentInstIdx]->execute();

			if (retval == -1)
				currentInstIdx++; // if it was a non-jump instructions, then go to the next instruction
			else
				currentInstIdx = retval; // if it was a jump instruction, then jump to that specified point
		}
	}

	catch (int e)
	{
		int lineNumber = instructions[currentInstIdx]->getLineNumber();
		reportError("An error was generated while executing the line. Execution of the program terminated." , lineNumber); //, true);
		exit(1);
	}
}

// add the error message to the error buffer
void Machine::reportError(string errMsg , int lineNumber /*= -1*/) { 
	errorBuffer.reportError(errMsg, lineNumber);
	setParseError(true);
}

// add the output text to the output buffer
void Machine::reportOutput(string out) {
    outputBuffer.reportOutput(out);
}

// set parseError
void Machine::setParseError(bool val) {
	parseError = val;
}

// get a pointer to the map of existing identifiers
map<string,Identifier*> * Machine::getidentifiers() {
	return & identifiers;
}

// get a pointer to the map of identifiers' prototypes (typeSet)
map<string,Identifier*> * Machine::getTypes(){
	return & typeSet;
}

// get a pointer to the map of existing labels
map<string, int>* Machine::getLabels(){
	return & labels;
}

// run the MIS server
void Machine::run() {
	    int read;

		//cout << "connection established"<<endl;
		char header[100];
		memset (header,0,100);
		read = tcpClientSocket->readFromSocketWithTimeout(header, 100, ClientTimeoutSec, ClientTimeoutMilli);
		//cout << "read=" << to_string(read) << endl;
		if (read < 1)
		{
			//delete tcpClientSocket;
			cout << "Error while reading data from client " << tcpClientSocket->getRemoteAddress() << ". Connection terminated." << endl;
			return;
		}
		long readSize = atol(header);
		//cout << "readSize=" << to_string(readSize) << endl;
		//cout << "header=\"" << header << "\"" << endl;

		long bytesRead = 0;
		char buffer[1024];
		memset(buffer, 0 , 1024);
		inputBuffer = "";
		while (bytesRead < readSize)
		{
			read = tcpClientSocket->readFromSocketWithTimeout(buffer, 1024, ClientTimeoutSec, ClientTimeoutMilli);
			if (read < 1)
				break;
			bytesRead += read;
			inputBuffer = inputBuffer + buffer;
		}

		//cout << "inputBuffer={" << inputBuffer << "}" << endl;
		if (bytesRead < 1)
		{
			//delete tcpClientSocket;
			cout << "Error while reading data from client " << tcpClientSocket->getRemoteAddress() << ". Connection terminated." << endl;
			return;
		}
<<<<<<< HEAD

		OutputBuffer::emptyBuffer();
		ErrorBuffer::emptyBuffer();

		cout << OutputBuffer::getOutputBuffer()<< endl;

		runProgram();

		//char header[100];
		memset (header ,0 , 100);
		string outputBuffer = OutputBuffer::getOutputBuffer();
		long outputBufferSize = outputBuffer.size();
		strcpy(header , to_string(outputBufferSize).c_str());
		tcpClientSocket->writeToSocket(header, 100);
		tcpClientSocket->writeToSocket(outputBuffer.c_str(), outputBufferSize);

=======
		
		outputBuffer.emptyBuffer();
		errorBuffer.emptyBuffer();
				
		runProgram();
		
		memset (header ,0 , 100);
		string outputText = outputBuffer.getOutputBuffer();
		long outputTextSize = outputText.size(); 
		strcpy(header , to_string(outputTextSize).c_str());
		tcpClientSocket->writeToSocket(header, 100);
		tcpClientSocket->writeToSocket(outputText.c_str(), outputTextSize);
		
>>>>>>> 7acafc1d907b99689c3dcb2f2e394ea3c3928ee7
		memset (header ,0 , 100);
		string errorText = errorBuffer.getErrorBuffer();
		long errorTextSize = errorText.size();
		strcpy(header , to_string(errorTextSize).c_str());
		tcpClientSocket->writeToSocket(header, 100);
<<<<<<< HEAD
		tcpClientSocket->writeToSocket(errorBuffer.c_str(), errorBufferSize);

=======
		tcpClientSocket->writeToSocket(errorText.c_str(), errorTextSize);
		
>>>>>>> 7acafc1d907b99689c3dcb2f2e394ea3c3928ee7
		tcpClientSocket->shutDown();
}

// the thread main body function
void * Machine::threadMainBody (void * arg) {
	run();
	return NULL;
}
