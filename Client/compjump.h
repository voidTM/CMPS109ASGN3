#ifndef COMPARATIVEJUMPS
#define COMPARATIVEJUMPS

#include "instruction.h"
#include "identifier.h"
#include "numeric.h"
#include "real.h"
#include "character.h"
#include "mis_string.h"
#include "jump.h"

using namespace std;

class ComparativeJump : public Jump {
	private:
		int state; // each state is for a different comparative jump instruction
		// State 1: JMPGT		State 2: JMPLT
		// State 3: JMPGTE		State 4: JMPLTE
	public:

	ComparativeJump(Parser* parser, int opt);
	ComparativeJump(Parser* parser, int opt, int lineNumber);

	Instruction * clone(vector<char*> & argv, int lineNumber);

	void initialize (vector<char*> & argv);
	int execute();
	virtual ~ComparativeJump();
};

#endif