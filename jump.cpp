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

	char* parA = argv[0];
	// Assume first is a label
	args.push_back(parA);
}

// Given a Label name it will look it up and 
// return the line number to jump to if found.
int Jump::jumpLookUp(string label){
	auto labels = machine->getLabels();

	if (labels->find(label) == labels->end())
		reportError("The label " + string(label) + " not found.", lineNumber);
	
	return (*labels)[label];
}

int Jump::execute(){
	int jmpLine = jumpLookUp(args[0]);
	//cout << "Jumping to " << jmpLine << endl;
	return jmpLine;
}