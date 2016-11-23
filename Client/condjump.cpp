#include "condjump.h"

// Constructor
ConditionalJump::ConditionalJump(ErrorChecker* parser, int opt){
	this->parser = parser;
	state = opt;
}

ConditionalJump::ConditionalJump(ErrorChecker* parser, int opt, int lineNumber){
	this->parser = parser;
	this->state = opt;
	this->lineNumber = lineNumber;
}

// Destructor

ConditionalJump::~ConditionalJump(){}

// Creates clone of the ConditionalJump object
// Since each state points to a different
// comparasion the state for the ConditionalJump
// is inheirited during cloning.
Instruction * ConditionalJump::clone(vector<char*> & argv, int lineNumber) {
	ConditionalJump * jmp = new ConditionalJump(this->parser, this->state, lineNumber);
	jmp->initialize(argv);
	return jmp;
}

// Expects (Label name, conditional number)
void ConditionalJump::initialize(std::vector<char*> & argv){
	// Check for size
	if (argv.size() != 2)
		reportError("The number of arguments for Conditional Jumps should be 2", lineNumber);

	auto identifiers = parser->getidentifiers();

	// Assume first is a label
	char* parA = argv[0];
	args.push_back(parA);

	// check if it is a variable
	char* parB = argv[1];
	if (parB[0] == '$'){
		if (identifiers->find(parB) == identifiers->end()){ //check if the variable name is not found in the variable list
			reportError("The variable " + string(parB) + " not found.", lineNumber); // report error
			return;}
	}
	else{
		//try to make constant into a typeable object
		Identifier* obj = identifyConstant(parA);
		if(obj != NULL){
			(*identifiers)[parB] = obj;
		}
		else{
			reportError("Arguments is neither constant nor variable", lineNumber);
			return;
		}
	}

	// Check to see the parameter is numeric or real
	string type = (*identifiers)[parB]->getType();
	if(type != Numeric::type() && type != Real::type()){
		reportError("Arguments to conditional jump not of valid type.", lineNumber);
		return;
	}
	
	args.push_back(parB);
}

// execute compares to see the conditional value is equal to 
// zero or not. A decision is then made depending on if it is
// JMPZ or JMPNZ
int ConditionalJump::execute(){
	bool jump = false;
	int jumpLine = -1;
	auto identifiers = parser->getidentifiers();

	Numeric* obj = (Numeric*)(*identifiers)[args[1]];
	switch(state){
		case 1: if(obj->getValue() == 0) //For JMPZ
					jump = true;
				break;
		case 2: if(obj->getValue() != 0) //For JMPNZ
					jump = true;
				break;
	}

	// if decision is true then jump
	if(jump)
		jumpLine = jumpLookUp(args[0]);
	return jumpLine;
}