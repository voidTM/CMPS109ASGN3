#include "out.h"

// Constructor
Out::Out (Machine * machine) {this->machine = machine;}

Out::Out (Machine * machine, int lineNumber) {
	this->machine = machine;
	this->lineNumber = lineNumber;
}

// Destructor
Out::~Out() {}

// Methods

Instruction * Out::clone(vector<char*> & argv, int lineNumber) {
	Out * printOut = new Out(this->machine, lineNumber);
	printOut->initialize(argv);
	return printOut;
}

void Out::initialize(std::vector<char*> & argv){
	// Check for size
	if (argv.size() < 1)
		reportError("The number of arguments for Out should be atleast 1", lineNumber);

	auto identifiers = machine->getidentifiers();
	int argsCount = argv.size();
	for(int i=0; i<argsCount; i++)
	{
		//auto identifiers = machine->getidentifiers();
		char* token = argv[i];

		if (token[0] == '$'){
			if (identifiers->find(token) == identifiers->end()){ //check if the variable name is not found in the variable list
				reportError("The variable " + string(token) + " not found.", lineNumber); // report error
				return;}
		} else{
			//try to make constant into a typeable object
			Identifier* obj = identifyConstant(token);
			if(obj != NULL)
				(*identifiers)[token] = obj;
			else{
				reportError("Arguments is neither constant nor variable", lineNumber);
				return;
			}
		}

		args.push_back(token);
	}

}


int Out::execute(){

	string out = "";
	auto identifiers = machine->getidentifiers();

	for(string arg : args){
		Identifier * ident = (*identifiers)[arg];
		out += ident->getStrValue() + "   ";
	}

	//out += "\n";
	machine->reportOutput(out);
	return -1;
	
}

