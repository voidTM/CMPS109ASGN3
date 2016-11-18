#ifndef DIV
#define DIV

#include "instruction.h"
#include "numeric.h"
#include "real.h"

using namespace std;

class Div : public Instruction {

public:
	// constructor
	Div(Machine * machine);
	Div(Machine * machine, int lineNumber);

	// clone an object of the same type
	Instruction * clone(vector<char*> & argv, int lineNumber);

	// initialize and parse with the provided parameters
	void initialize (vector<char*> & argv);

	// execute the instruction with the provided parameters
	int execute();

	// destructor
	virtual ~Div();
};

#endif /* DIV */
