#include "servermachine.h"


// constructor
ServerMachine::ServerMachine(TCPSocket * tcpClientSocket, int readBufferSize, int writeBufferSize) : Thread(), Machine() {

    this->tcpClientSocket = tcpClientSocket;
    this->readBufferSize = readBufferSize;
    this->writeBufferSize = writeBufferSize;
}


// parses and runs a program file
void ServerMachine::runProgram() {
	// parse the entire program file
	parseFile();

	// if there was an error in parsing the file, terminate the execution
	if (parseError) return;
	
	// execute the instructions one by one
	executeInstructions();
} 

// execute the instructions one by one
void ServerMachine::executeInstructions(int startInstIdx /* = 0 */)
{
	// try to execute the program instruction by instruction
	int retval;
	int currentInstIdx = startInstIdx;
	/*if (startInstIdx == NULL) 
	    currentInstIdx = 0;
	else
	    currentInstIdx = (long)startInstIdx;*/
	int endInstIdx = instructions.size();
	
	try
	{
		while (currentInstIdx < endInstIdx)
		{
			// execute the current instruction
			retval = instructions[currentInstIdx]->execute();

			if (retval == -2)
				return; // no more instructions will be executed
			else if (retval == -1)
				currentInstIdx++; // if it was a non-jump instructions, then go to the next instruction
			else
				currentInstIdx = retval; // if it was a jump instruction, then jump to that specified point
		}
	}

	catch (int e)
	{
		int lineNumber = instructions[currentInstIdx]->getLineNumber();
		reportError("An error was generated while executing the line. Execution of the program terminated." , lineNumber);
	}
}

// run the MIS server
void ServerMachine::run() {
	    int read;
	    bool reading = false;

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
/*
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

*/		
		outputBuffer.emptyBuffer();
		errorBuffer.emptyBuffer();
			

		runProgram(); 
		
		memset (header ,0 , 100);
		string outputText = outputBuffer.getOutputBuffer();
		long outputTextSize = outputText.size() + 1; 
		strcpy(header , to_string(outputTextSize).c_str());
		tcpClientSocket->writeToSocket(header, 100);
		tcpClientSocket->writeToSocket(outputText.c_str(), outputTextSize);
		
		memset (header ,0 , 100);
		string errorText = errorBuffer.getErrorBuffer();
		long errorTextSize = errorText.size() + 1;
		strcpy(header , to_string(errorTextSize).c_str());
		tcpClientSocket->writeToSocket(header, 100);
//		tcpClientSocket->writeToSocket(errorBuffer.c_str(), errorBufferSize);
		tcpClientSocket->writeToSocket(errorText.c_str(), errorTextSize);
		
		tcpClientSocket->shutDown();
}


// the thread main body function
void * ServerMachine::threadMainBody (void * arg) {
	run();
	return NULL;
}

ServerMachine::~ServerMachine(){
	if (tcpClientSocket != NULL)
		delete tcpClientSocket;
}
