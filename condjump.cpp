#include "condjump.h"

// Constructor
ConditionalJump::ConditionalJump(Machine * machine, int opt){
	this->machine = machine;
	state = opt;
}

ConditionalJump::ConditionalJump(Machine* machine, int opt, int lineNumber){
	this->machine = machine;
	this->state = opt;
	this->lineNumber = lineNumber;
}

// Destructor

ConditionalJump::~ConditionalJump(){}

Instruction * ConditionalJump::clone(vector<char*> & argv, int lineNumber) {
	ConditionalJump * jmp = new ConditionalJump(this->machine, this->state, lineNumber);
	jmp->initialize(argv);
	return jmp;
}

void ConditionalJump::initialize(std::vector<char*> & argv){
	// Check for size
	if (argv.size() != 2)
		reportError("The number of arguments for Conditional Jumps should be 2", lineNumber);

	auto identifiers = machine->getidentifiers();
	char* parA = argv[0];
	// check if it is a variable
	args.push_back(parA);

	char* parB = argv[1];
	// Assume first is a label

	// Check on conditional
	if (parB[0] == '$'){
		if (identifiers->find(parB) == identifiers->end()) //check if the variable name is not found in the variable list
			reportError("The variable " + string(parB) + " not found.", lineNumber); // report error
	}
	else{
		//try to make constant into a typeable object
		Identifier* obj = identifyConstant(parA);
		if(obj != NULL){
			(*identifiers)[parB] = obj;
		}
		else
			reportError("Arguments is neither constant nor variable", lineNumber);
	}

	// Check to see the two parameters are of the same type
	//cout << (*identifiers)[parB]->getType() << endl;
	//cout << Numeric::type() << endl;
	string type = (*identifiers)[parB]->getType();
	if(type != Numeric::type() && type != Real::type())
		reportError("Arguments to conditional jump not of valid type.", lineNumber);
	
	args.push_back(parB);
}

int ConditionalJump::execute(){
	bool jump = false;
	int jumpLine = -1;
	auto identifiers = machine->getidentifiers();

	Numeric* obj = (Numeric*)(*identifiers)[args[1]];
	switch(state){
		case 1: if(obj->getValue() == 0) //For JMPZ
					jump = true;
					break;
		case 2: if(obj->getValue() != 0) //For JMPNZ
					jump = true;
					break;
	}
	if(jump)
		jumpLine = jumpLookUp(args[0]);
	return jumpLine;
}