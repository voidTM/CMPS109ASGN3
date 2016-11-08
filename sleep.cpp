#include "sleep.h"

// Construtor
Sleep::Sleep(Machine* machine){
	this->machine = machine;
}

Sleep::Sleep(Machine* machine, int lineNumber){
	this->machine = machine;
	this->lineNumber = lineNumber;
}

// Destructor
Sleep::~Sleep(){}

Instruction * Sleep::clone(vector<char*> & argv, int lineNumber) {
	Sleep * snooze = new Sleep(this->machine, lineNumber);
	snooze->initialize(argv);
	return snooze;
}

void Sleep::initialize(std::vector<char*> & argv){
	// Check for size
	if (argv.size() != 1)
		reportError("The number of arguments for Sleep should be 1", lineNumber);

	auto identifiers = machine->getidentifiers();
	char* parA = argv[0];

	// check if it is a variable
	if (parA[0] == '$'){
		if (identifiers->find(parA) == identifiers->end()) //check if the variable name is not found in the variable list
			reportError("The variable " + string(parA) + " not found.", lineNumber); // report error
	}
	else{
		//try to make constant into a typeable object
		Identifier* obj = identifyConstant(parA);
		if(obj != NULL){
			(*identifiers)[parA] = obj;
		}
		else
			reportError("Arguments is neither constant nor variable", lineNumber);
	}

	// Check to see the two parameters are of the same type
	string type = (*identifiers)[parA]->getType();
	if(type != Numeric::type() && type != Real::type())
		reportError("Arguments to sleep not of valid type.", lineNumber);
	
	args.push_back(parA);
}

int Sleep::execute() {

	auto identifiers = machine->getidentifiers();
	cout << (*identifiers)[args[0]]->getStrValue() << endl;

	Numeric* obj = (Numeric*)(*identifiers)[args[0]];

	uint time = obj->getValue();
	sleep(time);
	return -1;
}