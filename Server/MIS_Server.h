#ifndef MISSERVERMACHINE
#define MISSERVERMACHINE


class ServerMachine : public Machine{
	private:

	public:
	    void runProgram();

	    void executeInstructions(int startInstIdx = 0);

	    void * threadMainBody (void * arg); // Main thread body that runs the MIS machine

};

#endif