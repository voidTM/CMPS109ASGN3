#include "lock.h"

// constructor
Lock::Lock (Machine * machine) {this->machine = machine;}

// constructor
Lock::Lock (Machine * machine, int lineNumber) {
	this->machine = machine;
	this->lineNumber = lineNumber;
}

//destructor
Lock::~Lock() {}

// clone an object of the same type
Instruction * Lock::clone(vector<char*> & argv, int lineNumber) {
	Lock * lock = new Lock(this->machine, lineNumber);
	lock->initialize(argv);
	return lock;
}

// initialize and parse the instruction with the provided parameters
void Lock::initialize(vector<char*> & argv) {

	// check the number of parameters
	int argsCount = argv.size();
	if (argsCount != 1)
	{
		reportError("LOCK should have one arguement.", lineNumber); // report error
	}
	
	char* token;
	auto identifiers = machine->getidentifiers();
	token = argv[0];
	
	// check if it is a variable
	if (token[0] == '$')
	{
		if (identifiers->find(token) == identifiers->end()) //check if the variable name is not found in the variable list
		{
			reportError("The variable " + string(token) + " not found.", lineNumber); // report error
		}
	}
	else
	{
		reportError(string(token) + " is not a variable.", lineNumber); // report error
	}

	// push the parameter into a container
	args.push_back(token);
}

int Lock::execute() {
    auto identifiers = machine->getidentifiers();
    Identifier * ident = (*identifiers)[args[0]];
    
    pthread_mutex_lock(&(ident->lock));

	return -1;   
}

