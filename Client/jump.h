#ifndef JUMPS
#define JUMPS

#include "instruction.h"
#include "identifier.h"
#include "numeric.h"
#include "real.h"
#include "character.h"
#include "mis_string.h"

using namespace std;

class Jump : public Instruction {

	public:
	Jump(){};

	Jump(ErrorChecker* parser);
	Jump(ErrorChecker* parser, int lineNumber);

	virtual Instruction * clone(vector<char*> & argv, int lineNumber);

	virtual void initialize (vector<char*> & argv);
	virtual int execute();
	int jumpLookUp(string label);
	virtual ~Jump();
};

#endif