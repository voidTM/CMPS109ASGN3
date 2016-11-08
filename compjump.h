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
		int state;
	public:

	ComparativeJump(Machine * machine, int opt);
	ComparativeJump(Machine * machine, int opt, int lineNumber);

	Instruction * clone(vector<char*> & argv, int lineNumber);

	void initialize (vector<char*> & argv);
	int execute();
	virtual ~ComparativeJump();
};

#endif