#ifndef MISSERVERMACHINE
#define MISSERVERMACHINE

#include "machine.h"
#include "Thread.h"
#include "instruction.h"

class Instruction;

class ServerMachine : public Machine, public Thread{
	private:
		TCPSocket * tcpClientSocket; // TCP Socket for communication with client
		// client socket timeout
		int ClientTimeoutSec = 10, ClientTimeoutMilli = 0;

	public:

		ServerMachine(TCPSocket * tcpClientSocket, int readBufferSize = 10*1024*1024, int writeBufferSize = 10*1024*1024);
	    void runProgram();

	    //void parseFile();

	    void executeInstructions(int startInstIdx = 0);

	    void run();

	    void * threadMainBody (void * arg); // Main thread body that runs the MIS machine
	    
	    virtual ~ServerMachine();
};

#endif