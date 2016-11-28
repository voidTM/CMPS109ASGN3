#include "thread_begin.h"

// constructor
ThreadBegin::ThreadBegin (Machine * machine) {this->machine = machine;}

// constructor
ThreadBegin::ThreadBegin (Machine * machine, int lineNumber) {
	this->machine = machine;
	this->lineNumber = lineNumber;
}

//destructor
ThreadBegin::~ThreadBegin() {}

// clone an object of the same type
Instruction * ThreadBegin::clone(vector<char*> & argv, int lineNumber) {
	ThreadBegin * threadBegin = new ThreadBegin(this->machine, lineNumber);
	threadBegin->initialize(argv);
	return threadBegin;
}

// initialize and parse the instruction with the provided parameters
void ThreadBegin::initialize(vector<char*> & argv) {

	// check the number of parameters
	int argsCount = argv.size();
	if (argsCount > 0)
	{
		reportError("THREAD_BEGIN does not accept any arguements.", lineNumber); // report error
	}
}

void * ThreadBegin::runThread(void * threadBeginObject) {

    ThreadBegin * obj = (ThreadBegin *) threadBeginObject;
    obj->machine->executeInstructions(obj->getBeginInstIdx()+1);
}

int ThreadBegin::execute() {

	int return_code = pthread_create(&pthread, NULL, ThreadBegin::runThread, this);
	
	if (return_code) {
		reportError("Error Spawning thread. Program terminated.", lineNumber);
		return -2;
	}
	
	pthread_t * threadPtr = &pthread;
	machine->getRunningThreads()->push_back(threadPtr);
	
	return (endInstIdx+1);
}

void ThreadBegin::setBeginInstIdx(int val) {
	beginInstIdx = val;
}
	
void ThreadBegin::setEndInstIdx(int val) {
	endInstIdx = val;
}

int ThreadBegin::getBeginInstIdx() {
	return beginInstIdx;
}

