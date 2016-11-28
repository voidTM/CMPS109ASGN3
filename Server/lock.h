#ifndef LOCK
#define LOCK

#include "instruction.h"

using namespace std;

class Lock : public Instruction {
public:
	// constructor
	Lock(Machine * machine);
	Lock(Machine * machine, int lineNumber);

	// clone object
	Instruction * clone(vector<char*> & argv, int lineNumber);
	
	// initialize and parse with the provided parameters
	void initialize (vector<char*> & argv);

	// execute the instruction with the provided parameters
	int execute();
	
	// destructor
	virtual ~Lock();
};

#endif /* LOCK */

