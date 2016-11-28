#include "thread_end.h"

// constructor
ThreadEnd::ThreadEnd (Machine * machine) {this->machine = machine;}

// constructor
ThreadEnd::ThreadEnd (Machine * machine, int lineNumber) {
	this->machine = machine;
	this->lineNumber = lineNumber;
}

//destructor
ThreadEnd::~ThreadEnd() {}

// clone an object of the same type
Instruction * ThreadEnd::clone(vector<char*> & argv, int lineNumber) {
	ThreadEnd * threadEnd = new ThreadEnd(this->machine, lineNumber);
	threadEnd->initialize(argv);
	return threadEnd;
}

// initialize and parse the instruction with the provided parameters
void ThreadEnd::initialize(vector<char*> & argv) {

	// check the number of parameters
	int argsCount = argv.size();
	if (argsCount > 0)
	{
		reportError("THREAD_END does not accept any arguements.", lineNumber); // report error
	}
}

int ThreadEnd::execute() {

    return -2;
}

