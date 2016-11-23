#include "assign.h"

// Construtor
Assign::Assign(ErrorChecker* parser){
	this->parser = parser;
}

Assign::Assign(ErrorChecker* parser, int lineNumber){
	this->parser = parser;
	this->lineNumber = lineNumber;
}

// Destructor
Assign::~Assign(){}

// Methods

Instruction * Assign::clone(vector<char*> & argv, int lineNumber) {
	Assign * assign = new Assign(this->parser, lineNumber);
	assign->initialize(argv);
	return assign;
}

void Assign::initialize(std::vector<char*> & argv){
	// Check for size
	if (argv.size() != 2){
		reportError("The number of arguments for Assign should be 2", lineNumber);
		return;
	}


	auto identifiers = parser->getidentifiers();
	char* parA = argv[0];
	char* parB = argv[1];

	//cout << "identifiers has " << identifiers->size() << endl;
	// check if it is a variable
	if (parA[0] == '$'){
		if (identifiers->find(parA) == identifiers->end()){ //check if the variable name is not found in the variable list
			reportError("The variable " + string(parA) + " not found.", lineNumber); // report error
			return;
		}
	}
	else{
		reportError(string(parA) + " is not a variable.", lineNumber);
		return; // report error
	}
	
	// Check second argument to see if it is a variable or constant
	if(parB[0] == '$'){
		if (identifiers->find(parA) == identifiers->end()) //check if the variable name is not found in the variable list
			reportError("The variable " + string(parB) + " not found.", lineNumber); // report error
			return;
	}
	else{
		//try to make constant into a typeable object
		Identifier* obj = identifyConstant(parB);
		if(obj != NULL){
			(*identifiers)[parB] = obj;
		}
		else
			reportError("Arguments is neither constant nor variable", lineNumber);
	}

	// Check to see the two parameters are of the same type
	if((*identifiers)[parA]->getType() != (*identifiers)[parB]->getType()){
		reportError("Arguments to Assign not of same type.", lineNumber);
		return;
	}
	
	args.push_back(parA);
	args.push_back(parB);
}

int Assign::execute() {

	auto identifiers = parser->getidentifiers();
	//out << (*identifiers)[args[0]]->getStrValue() << endl;

	(*identifiers)[args[0]] = (*identifiers)[args[1]];

	//cout << (*identifiers)[args[0]]->getStrValue() << endl;
	return -1;
}