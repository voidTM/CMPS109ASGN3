#include "barrier.h"

// constructor
Barrier::Barrier (Machine * machine) {this->machine = machine;}

// constructor
Barrier::Barrier (Machine * machine, int lineNumber) {
	this->machine = machine;
	this->lineNumber = lineNumber;
}

//destructor
Barrier::~Barrier() {}

// clone an object of the same type
Instruction * Barrier::clone(vector<char*> & argv, int lineNumber) {
	Barrier * barrier = new Barrier(this->machine, lineNumber);
	barrier->initialize(argv);
	return barrier;
}

// initialize and parse the instruction with the provided parameters
void Barrier::initialize(vector<char*> & argv) {

	// check the number of parameters
	int argsCount = argv.size();
	if (argsCount > 0)
	{
		reportError("BARRIER does not accept any arguements.", lineNumber); // report error
	}
}

int Barrier::execute() {

  auto runningThreads = machine->getRunningThreads();
  auto i = runningThreads->begin();

  while (i != runningThreads->end()) {
	if (*i != nullptr)
	{
		pthread_join(*(*i),NULL);
		i = runningThreads->erase(i);
	}
	else
	{
		i++;
	}
  }
  
  return -1;
}

