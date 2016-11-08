#ifndef SETSTRCHAR
#define SETSTRCHAR

#include "instruction.h"
#include "mis_string.h"
#include "character.h"
#include "numeric.h"

using namespace std;

class SetStrChar : public Instruction {

public:
	SetStrChar(Machine * machine);
	SetStrChar(Machine * machine, int lineNumber);

	Instruction * clone(vector<char*> & argv, int lineNumber);

	void initialize (vector<char*> & argv);

	int execute();

	virtual ~SetStrChar();
};

#endif /* SETSTRCHAR */
