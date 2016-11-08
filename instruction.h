#ifndef INSTRUCTION
#define INSTRUCTION

#include <vector>
#include "identifier.h"
#include "numeric.h"
#include "real.h"
#include "character.h"
#include "mis_string.h"
#include "machine.h"

using namespace std;

//class Machine;

class Instruction {

protected:
	vector<string> args; // a list of arguments provided for this instrction
	Machine * machine; // a pointer to the wrapper object
	int lineNumber; // used for error reporting

public:
	Instruction();
	Instruction(Machine * machine);
	Instruction(Machine * machine, int lineNumber);

	virtual Instruction * clone(vector<char*> & argv, int lineNumber) = 0;

	virtual void initialize (vector<char*> & argv) = 0;

	virtual int execute() = 0;

	int getLineNumber();

	Identifier* identifyConstant(char* constant);

	void reportError(string errMsg , int lineNumber = -1 , bool exit = false);

	virtual ~Instruction();
};

#endif /* INSTRUCTION */
