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
		int state;
	public:

	ConditionalJump(Machine * machine, int opt);
	ConditionalJump(Machine * machine, int opt, int lineNumber);

	Instruction * clone(vector<char*> & argv, int lineNumber);

	void initialize (vector<char*> & argv);
	int execute();
	virtual ~ConditionalJump();
};

#endif