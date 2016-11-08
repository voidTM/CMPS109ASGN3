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
	if (argv.size() != 1)
		reportError("The number of arguments for Assign should be 1", lineNumber);

	auto identifiers = machine->getidentifiers();
	char* param = argv[0];

	// check if it is a variable
	if (param[0] == '$'){
		if (identifiers->find(param) == identifiers->end()) //check if the variable name is not found in the variable list
			reportError("The variable " + string(param) + " not found.", lineNumber); // report error
	}
	else{
		//try to make constant into a typeable object
		Identifier* obj = identifyConstant(param);
		if(obj != NULL){
			(*identifiers)[param] = obj;
		}
		else
			reportError("Arguments is neither constant nor variable", lineNumber);
	}

	args.push_back(param);
}


int Out::execute(){

	auto identifiers = machine->getidentifiers();
	//cout << "printing" << endl;
	auto printLamba = [] ( auto a) { cout << a->getValue() << endl; };

	Identifier * ident = (*identifiers)[args[0]];
	string type = ident->getType();
	if(type == Real::type()){
		Real* obj = (Real*)ident;
		printLamba(obj);
	}else if (type == Numeric::type()){
		Numeric* obj = (Numeric*)ident;
		printLamba(obj);
	}else if (type == Character::type()){
		Character* obj = (Character*)ident;
		printLamba(obj);
	}else if (type == String::type()){
		String* obj = (String*)ident;
		printLamba(obj);
	}


	cout << type << endl;
	return -1;
	
}