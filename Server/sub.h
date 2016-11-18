#ifndef SUB
#define SUB

#include "instruction.h"
#include "numeric.h"
#include "real.h"

using namespace std;

class Sub : public Instruction{

public:
    // constructor
	Sub(Machine * machine);
	Sub(Machine * machine, int lineNumber);

	// clone an object of the same type
	Instruction * clone(vector<char*> & argv, int lineNumber);

	// initialize and parse the instruction with provided parameters
	void initialize (vector<char*> & argv);

	// execute the instruction
	int execute();

	// destructor
	virtual ~Sub();
};

#endif /* SUB */
