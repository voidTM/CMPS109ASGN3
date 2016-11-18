#ifndef MUL
#define MUL

#include "instruction.h"
#include "numeric.h"
#include "real.h"

using namespace std;

class Mul : public Instruction {

public:
	// constructor
	Mul(Machine * machine);
	Mul(Machine * machine, int lineNumber);

	// clone an object of the same type
	Instruction * clone(vector<char*> & argv, int lineNumber);

	// initialize and parse the instruction with the provided parameters
	void initialize (vector<char*> & argv);

	// execute the instruction
	int execute();

	// destructor
	virtual ~Mul();
};

#endif /* MUL */
