#include "compjump.h"

// Constructor
ComparativeJump::ComparativeJump(Machine * machine, int opt){
	this->machine = machine;
	state = opt;
}

ComparativeJump::ComparativeJump(Machine* machine, int opt, int lineNumber){
	this->machine = machine;
	this->state = opt;
	this->lineNumber = lineNumber;
}

// Destructor

ComparativeJump::~ComparativeJump(){}

Instruction * ComparativeJump::clone(vector<char*> & argv, int lineNumber) {
	ComparativeJump * jmp = new ComparativeJump(this->machine, this->state, lineNumber);
	jmp->initialize(argv);
	return jmp;
}

void ComparativeJump::initialize(std::vector<char*> & argv){
	// Check for size
	if (argv.size() != 3)
		reportError("The number of arguments for Comparative Jumps should be 3", lineNumber);

	auto identifiers = machine->getidentifiers();
	int argsCount = argv.size();

	// Assume first is a label
	char* parA = argv[0];
	args.push_back(parA);

	for(int i=1; i<argsCount; i++)
	{
		char* token = argv[i];
	// check if it is a variable
		if (token[0] == '$'){
			if (identifiers->find(token) == identifiers->end()) //check if the variable name is not found in the variable list
				reportError("The variable " + string(token) + " not found.", lineNumber); // report error
		} else{
			//try to make constant into a typeable object
			Identifier* obj = identifyConstant(token);
			if(obj != NULL){
				(*identifiers)[token] = obj;
			}
			else
				reportError("Arguments is neither constant nor variable", lineNumber);
		}

	if((*identifiers)[token]->getType() != Numeric::type())
		reportError("Arguments to comparative jump not of valid type.", lineNumber);
	
	args.push_back(token);
	}

}

int ComparativeJump::execute(){
	bool jump = false;
	int jumpLine = -1;
	auto identifiers = machine->getidentifiers();
	auto lambdGT =  [](auto a, auto b) { return a > b; };
	auto lambdaGTE =  [](auto a, auto b) { return a >= b; };
	Numeric* objA = (Numeric*)(*identifiers)[args[1]];
	Numeric* objB = (Numeric*)(*identifiers)[args[2]];
	int parA = objA->getValue();
	int parB = objB->getValue();
	switch(state){
		case 1: jump = lambdGT(parA,parB); //For JMGT
					break;
		case 2: jump = lambdGT(parB, parA); //For JMPLT
					break;
		case 3: jump = lambdaGTE(parA,parB);
					break;
		case 4: jump = lambdaGTE(parB, parA);
					break;
	}
	if(jump)
		jumpLine = jumpLookUp(args[0]);
	return jumpLine;
}