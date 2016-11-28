#ifndef THREADEND
#define THREADEND

#include "instruction.h"

using namespace std;

class ThreadEnd : public Instruction {
public:
	// constructor
	ThreadEnd(Machine * machine);
	ThreadEnd(Machine * machine, int lineNumber);

	// clone object
	Instruction * clone(vector<char*> & argv, int lineNumber);
	
	// initialize and parse with the provided parameters
	void initialize (vector<char*> & argv);

	// execute the instruction with the provided parameters
	int execute();
	
	// destructor
	virtual ~ThreadEnd();
};

#endif /* THREADEND */

