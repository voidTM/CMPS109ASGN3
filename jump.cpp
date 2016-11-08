#include "jump.h"

// Construtor
Jump::Jump(Machine* machine){
	this->machine = machine;
}

Jump::Jump(Machine* machine, int lineNumber){
	this->machine = machine;
	this->lineNumber = lineNumber;
}

// Destructor
Jump::~Jump(){}

Instruction * Jump::clone(vector<char*> & argv, int lineNumber) {
	Jump * jmp = new Jump(this->machine, lineNumber);
	jmp->initialize(argv);
	return jmp;
}

void Jump::initialize(std::vector<char*> & argv){
	// Check for size
	if (argv.size() != 1)
		reportError("The number of arguments for JMP should be 1", lineNumber);

	auto labels = machine->getLabels();
	char* parA = argv[0];
	// check if it is a variable
	args.push_back(parA);
}

int Jump::execute(){
	auto labels = machine->getLabels();

	if (labels->find(args[0]) == labels->end())
		reportError("The label " + string(args[0]) + " not found.", lineNumber);
	int jmpLine = (*labels)[args[0]];
	cout << "Jumping to " << jmpLine << endl;
	return jmpLine;
}