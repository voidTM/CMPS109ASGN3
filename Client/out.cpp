#include "out.h"

// Constructor
Out::Out (Parser* parser) {this->parser = parser;}

Out::Out (Parser* parser, int lineNumber) {
	this->parser = parser;
	this->lineNumber = lineNumber;
}

// Destructor
Out::~Out() {}

// Methods

Instruction * Out::clone(vector<char*> & argv, int lineNumber) {
	Out * printOut = new Out(this->parser, lineNumber);
	printOut->initialize(argv);
	return printOut;
}

void Out::initialize(std::vector<char*> & argv){
	// Check for size
	if (argv.size() < 1)
		reportError("The number of arguments for Out should be atleast 1", lineNumber);

	auto identifiers = parser->getidentifiers();
	int argsCount = argv.size();
	for(int i=0; i<argsCount; i++)
	{
		//auto identifiers = parser->getidentifiers();
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

	auto identifiers = parser->getidentifiers();
	//cout << "printing" << endl;

	for(string arg : args){
		Identifier * ident = (*identifiers)[arg];
		cout << ident->getStrValue() << "   ";
	}

	cout << endl;
	return -1;
	
}