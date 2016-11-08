#ifndef GETSTRCHAR
#define GETSTRCHAR

#include "instruction.h"
#include "mis_string.h"
#include "character.h"
#include "numeric.h"

using namespace std;

class GetStrChar : public Instruction {

public:
	GetStrChar(Machine * machine);
	GetStrChar(Machine * machine, int lineNumber);

	Instruction * clone(vector<char*> & argv, int lineNumber);

	void initialize (vector<char*> & argv);

	int execute();

	virtual ~GetStrChar();
};

#endif /* GETSTRCHAR */
