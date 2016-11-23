#ifndef INSTRUCTION
#define INSTRUCTION

#include <vector>
#include "identifier.h"
#include "numeric.h"
#include "real.h"
#include "character.h"
#include "mis_string.h"
#include "machine.h"
#include "error_buffer.h"

using namespace std;

class Instruction {

protected:
	vector<string> args; // a list of arguments provided for this instruction
	Machine * machine; // a pointer to the wrapper object
	int lineNumber; // line number, used for error reporting

public:
	// constructor
	Instruction();
	Instruction(Machine * machine);
	Instruction(Machine * machine, int lineNumber);

	// pure virtual function used by sub-classes for cloning an object of their own type
	virtual Instruction * clone(vector<char*> & argv, int lineNumber) = 0;

	// pure virtual function used by sub-classes for initializing and parsing with the provided parameters
	virtual void initialize (vector<char*> & argv) = 0;

	// pure virtual function used by sub-classes for executing their own instruction
	virtual int execute() = 0;

	// get the line number of this instruction in the program file
	int getLineNumber();

	// determines the class of the constant and return the object of the corresponding type
	Identifier* identifyConstant(char* constant);

	// report an error message
	void reportError(string errMsg , int lineNumber = -1); // , bool exit = false);

	// destructor
	virtual ~Instruction();
};

#endif /* INSTRUCTION */
