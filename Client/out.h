#ifndef PRINTOUT
#define PRINTOUT

#include "instruction.h"
#include "identifier.h"
#include "numeric.h"
#include "real.h"
#include "character.h"
#include "mis_string.h"

using namespace std;

class Out : public Instruction {

	public:
	//Add();

	Out(ErrorChecker* parser);
	Out(ErrorChecker* parser, int lineNumber);

	Instruction * clone(vector<char*> & argv, int lineNumber);

	void initialize (vector<char*> & argv);
	int execute();

	//Identifier* identifyConstant(char* constant);

	virtual ~Out();
};

#endif