#ifndef SETSTRCHAR
#define SETSTRCHAR

#include "instruction.h"
#include "mis_string.h"
#include "character.h"
#include "numeric.h"

using namespace std;

class SetStrChar : public Instruction {

public:
	// constructor
	SetStrChar(Parser* parser);
	SetStrChar(Parser* parser, int lineNumber);

	// clone an object of the same type
	Instruction * clone(vector<char*> & argv, int lineNumber);

	// initialize and parse the instruction with provided parameters
	void initialize (vector<char*> & argv);

	// execute the instruction
	int execute();

	// destructor
	virtual ~SetStrChar();
};

#endif /* SETSTRCHAR */
