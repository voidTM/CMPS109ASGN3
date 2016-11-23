#ifndef GETSTRCHAR
#define GETSTRCHAR

#include "instruction.h"
#include "mis_string.h"
#include "character.h"
#include "numeric.h"

using namespace std;

class GetStrChar : public Instruction {

public:
	// constructor
	GetStrChar(ErrorChecker* parser);
	GetStrChar(ErrorChecker* parser, int lineNumber);

	// clone an object of the same type
	Instruction * clone(vector<char*> & argv, int lineNumber);

	// initialize and parse with the provided parameters
	void initialize (vector<char*> & argv);

	// execute the instruction with the provided parameters
	int execute();

	//destructor
	virtual ~GetStrChar();
};

#endif /* GETSTRCHAR */
