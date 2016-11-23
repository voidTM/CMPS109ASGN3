#ifndef CONDITIONALJUMPS
#define CONDITIONALJUMPS

#include "instruction.h"
#include "identifier.h"
#include "numeric.h"
#include "real.h"
#include "character.h"
#include "mis_string.h"
#include "jump.h"

using namespace std;

class ConditionalJump : public Jump {
	private:
		int state; // each state is for a different conditional jump instruction
		// State 1: JMPZ 	Stace 2: JMPNZ
	public:

	ConditionalJump(ErrorChecker* parser, int opt);
	ConditionalJump(ErrorChecker* parser, int opt, int lineNumber);

	Instruction * clone(vector<char*> & argv, int lineNumber);

	void initialize (vector<char*> & argv);
	int execute();
	virtual ~ConditionalJump();
};

#endif