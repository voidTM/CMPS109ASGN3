#include "jump.h"

// Construtor
Jump::Jump(Parser* parser){
	this->parser = parser;
}

Jump::Jump(Parser* parser, int lineNumber){
	this->parser = parser;
	this->lineNumber = lineNumber;
}

// Destructor
Jump::~Jump(){}

Instruction * Jump::clone(vector<char*> & argv, int lineNumber) {
	Jump * jmp = new Jump(this->parser, lineNumber);
	jmp->initialize(argv);
	return jmp;
}

// initialize the instruction to have 1 arguement 
// that is presumed to be a label name
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
// otherwise continue forward to next line
int Jump::jumpLookUp(string label){
	int line = -1;
	auto labels = parser->getLabels();

	if (labels->find(label) == labels->end()){
		reportError("The label " + string(label) + " not found.", lineNumber);	
	}
	else
		line = (*labels)[label];
	
	return line;
}

int Jump::execute(){
	int jmpLine = jumpLookUp(args[0]);
	//cout << "Jumping to " << jmpLine << endl;
	return jmpLine;
}