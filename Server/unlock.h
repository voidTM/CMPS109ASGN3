#ifndef UNLOCK
#define UNLOCK

#include "instruction.h"

using namespace std;

class Unlock : public Instruction {
public:
	// constructor
	Unlock(Machine * machine);
	Unlock(Machine * machine, int lineNumber);

	// clone object
	Instruction * clone(vector<char*> & argv, int lineNumber);
	
	// initialize and parse with the provided parameters
	void initialize (vector<char*> & argv);

	// execute the instruction with the provided parameters
	int execute();
	
	// destructor
	virtual ~Unlock();
};

#endif /* UNLOCK */

