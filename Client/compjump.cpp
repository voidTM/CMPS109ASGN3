#include "compjump.h"

// Constructor
ComparativeJump::ComparativeJump(Parser* parser, int opt){
	this->parser = parser;
	state = opt;
}

ComparativeJump::ComparativeJump(Parser* parser, int opt, int lineNumber){
	this->parser = parser;
	this->state = opt;
	this->lineNumber = lineNumber;
}

// Destructor

ComparativeJump::~ComparativeJump(){}

// Creates clone of the ComparativeJump object
// Since each state points to a different
// comparasion the state for the ComparativeJump
// is inheirited during cloning.
Instruction * ComparativeJump::clone(vector<char*> & argv, int lineNumber) {
	ComparativeJump * jmp = new ComparativeJump(this->parser, this->state, lineNumber);
	jmp->initialize(argv);
	return jmp;
}

// initialize a ComparativeJump instruction to hold three arguements
// of format (label name, comparative param1, comparative param2)
void ComparativeJump::initialize(vector<char*> & argv){
	// Check for size
	if (argv.size() != 3)
		reportError("The number of arguments for Comparative Jumps should be 3", lineNumber);

	auto identifiers = parser->getidentifiers();
	int argsCount = argv.size();

	// Assume first is a label
	char* parA = argv[0];
	args.push_back(parA);

	for(int i=1; i<argsCount; i++)
	{
		char* token = argv[i];
	// check if it is a variable
		if (token[0] == '$'){
			if (identifiers->find(token) == identifiers->end()){ //check if the variable name is not found in the variable list
				reportError("The variable " + string(token) + " not found.", lineNumber); // report error
				return;}
		} else{
			//try to make constant into a typeable object
			Identifier* obj = identifyConstant(token);
			if(obj != NULL){
				(*identifiers)[token] = obj;
			}
			else{
				reportError("Arguments is neither constant nor variable", lineNumber);
				return;
			}
		}

	string type = (*identifiers)[token]->getType();
	if(type != Numeric::type() && type != Real::type())
		reportError("Arguments to comparative jump not of valid type.", lineNumber);
	args.push_back(token);
	}

}

int ComparativeJump::execute(){
	bool jump = false;
	int jumpLine = -1;
	auto identifiers = parser->getidentifiers();
	
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