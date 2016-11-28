#include "unlock.h"

// constructor
Unlock::Unlock (Machine * machine) {this->machine = machine;}

// constructor
Unlock::Unlock (Machine * machine, int lineNumber) {
	this->machine = machine;
	this->lineNumber = lineNumber;
}

//destructor
Unlock::~Unlock() {}

// clone an object of the same type
Instruction * Unlock::clone(vector<char*> & argv, int lineNumber) {
	Unlock * unlock = new Unlock(this->machine, lineNumber);
	unlock->initialize(argv);
	return unlock;
}

// initialize and parse the instruction with the provided parameters
void Unlock::initialize(vector<char*> & argv) {

	// check the number of parameters
	int argsCount = argv.size();
	if (argsCount != 1)
	{
		reportError("UNLOCK should have one arguement.", lineNumber); // report error
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

int Unlock::execute() {
    auto identifiers = machine->getidentifiers();
    Identifier * ident = (*identifiers)[args[0]];
    
    pthread_mutex_unlock(&(ident->lock));

	return -1;   
}

