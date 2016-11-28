#ifndef BARRIER
#define BARRIER

#include <pthread.h>
#include "instruction.h"

using namespace std;

class Barrier : public Instruction {
public:
	// constructor
	Barrier(Machine * machine);
	Barrier(Machine * machine, int lineNumber);

	// clone object
	Instruction * clone(vector<char*> & argv, int lineNumber);
	
	// initialize and parse with the provided parameters
	void initialize (vector<char*> & argv);

	// execute the instruction with the provided parameters
	int execute();
	
	// destructor
	virtual ~Barrier();
};

#endif /* BARRIER */

