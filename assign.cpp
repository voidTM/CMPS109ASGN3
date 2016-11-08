#include "assign.h"

// Construtor
Assign::Assign(Machine* machine){
	this->machine = machine;
}

Assign::Assign(Machine* machine, int lineNumber){
	this->machine = machine;
	this->lineNumber = lineNumber;
}

// Destructor
Assign::~Assign(){}

// Methods

Instruction * Assign::clone(vector<char*> & argv, int lineNumber) {
	Assign * assign = new Assign(this->machine, lineNumber);
	assign->initialize(argv);
	return assign;
}

void Assign::initialize(std::vector<char*> & argv){
	// Check for size
	if (argv.size() != 2)
		reportError("The number of arguments for Assign should be 2", lineNumber);

	auto identifiers = machine->getidentifiers();
	char* parA = argv[0];
	char* parB = argv[1];

	// check if it is a variable
	if (parA[0] == '$'){
		if (identifiers->find(parB) == identifiers->end()) //check if the variable name is not found in the variable list
			reportError("The variable " + string(parA) + " not found.", lineNumber); // report error
	}
	else
		reportError(string(parA) + " is not a variable.", lineNumber); // report error
	
	// Check second argument to see if it is a variable or constant
	if(parB[0] == '$'){
		if (identifiers->find(argv[1]) == identifiers->end()) //check if the variable name is not found in the variable list
			reportError("The variable " + string(parB) + " not found.", lineNumber); // report error
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
	if((*identifiers)[parA]->getType() != (*identifiers)[parB]->getType())
		reportError("Arguments to Assign not of same type.", lineNumber);
	
	args.push_back(parA);
	args.push_back(parB);
}

Identifier* Assign::identifyConstant(char* constant){
	int a;
	double b;
	char c;
	char* d;
	string type;
	Identifier* obj = NULL;


	sscanf(constant, " %d %lf %c \"%s\" ", &a, &b, &c, d);

	if(a != NULL)
		obj = new Numeric(a);
	if(b != NULL)
		obj = new Real(b);
	if(c != NULL)
		obj = new Character(c);
	if(d != NULL){
		int length = strlen(d);
		if(d[0] == '\"' && d[length - 1] == '\"')
		{
			// copy without first and last value
			// removes double quotes
			string val = d;
			val.erase(val.begin());
			val.erase(val.end());
			obj = new String(val);
		}
	}

	return obj;
}

int Assign::execute() {

	auto identifiers = machine->getidentifiers();

	(*identifiers)[args[0]] = (*identifiers)[args[1]];

	return 0;
}